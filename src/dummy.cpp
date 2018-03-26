// TODO:
/*
 * - Encode geoJSON to polygoines
 * - convert geoJSON to sf
 * - convert sf to geoJSON
 * - read/write mongodb
 *
 * 1. convert geoJSON into geometry.hpp
 * 2. convert into R data types?
 * 3.
 *
 * Can use
 *
 */

// NOTES:
/*
 * mapboxGeojson: https://github.com/mapbox/geojson-cpp
 * - a c++ library for converting GeoJSON into geometry.hpp representation
 *
 */

// sf
// - a geometry is an 'sfg'
// - a feature is an 'sfc'
// - a collection of 'sfg's is an 'sfc' (with extra attributes)
// - an 'sfc' with properties is an 'sf'

// - how does it compare to what
// https://github.com/r-spatial/sf/issues/185
// does?
// - can ^^ handle an array of geojson?


// [[Rcpp::depends(mapboxGeometry)]]
// [[Rcpp::depends(mapboxVariant)]]
// [[Rcpp::depends(rapidjsonr)]]

#include <mapbox/geojson.hpp>
#include <mapbox/geojson/rapidjson.hpp>
#include <mapbox/geometry.hpp>
#include <mapbox/geometry/point.hpp>
#include <mapbox/geometry/multi_point.hpp>
#include <mapbox/geometry/line_string.hpp>
//#include <mapbox/variant.hpp>

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

//#include "mapbox/RcppDataTypes.h"

#include "rmapboxgeojson.h"
#include <Rcpp.h>

using namespace mapbox::geojson;
//using namespace mapbox::geometry;

using namespace Rcpp;
using namespace rapidjson;

#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>

// TODO:
// - error checking - invalid GeoJSON

geojson readGeoJSON(const char* json) {
  return parse(json);
}


/*
 * GeoJSON to SFG
 *
 * @param js returns an `sfg` object from the GeoJSON geometry
 */
void geojson_to_sfg(geojson geo) {

  // switch on the geom.type
  std::cout << "debug: geojson which: " << geo.which() << std::endl;
  // geometry: 0
  // GeometryCollection: 0
  // Feature: 1
  // FeatureCollection: 2

  // if geometry, which type of geometry is it?
  if (geo.which() == 0) {
    // geometry / geometryCollection
    const auto &geom = geo.get<geometry>();
    std::cout << "debug: geom which: " << geom.which() << std::endl;
    std::cout << "debug: is geometry_collection: " << geom.is<geometry_collection>() << std::endl;
    // point: 0
    // multipoint: 1
    // linestring: 2
    // multilinestring: 3
    // polygon: 4
    // multipolygon: 5
    // geometrycollection: 6
  }

}


// use rapidJSON to parse a JSON document
// [[Rcpp::export]]
Rcpp::List parseSomething(const char* js) {

  rapidjson::Document d;
  d.Parse(js);
  Rcpp::List lst(d.Size());

  //mapbox::geojson::rapidjson_document rd = d;

  // if the GeoJSON is an array of objects, need to loop array
  // otherwise, just parse what's there
  for (rapidjson::SizeType i = 0; i < d.Size(); i++) {
    const Value& v = d[i];
    //Rcpp::Rcout << "debug: in loop" << std::endl;
    //std::cout << v["type"].GetString() << std::endl;
    //std::cout << "debug: isObject " << v.IsObject() << std::endl;

    StringBuffer sb;
    Writer<StringBuffer> writer(sb);
    v.Accept(writer);
    std::string s = sb.GetString();
    std::cout << s << std::endl;

    const char* myjs = sb.GetString();
    const auto &data = readGeoJSON(myjs);

    geojson_to_sfg(data);

    //const auto &feat = data.get<feature>();

    //Rcpp::Rcout << "debug feature: " << feat.geometry.is<multi_polygon>() << std::endl;

    //const auto &geom = feat.geometry.get<multi_polygon>();

    //lst[i] = Rcpp::wrap(geom);

//    const auto &geom = data.get<geometry>();

    //Rcpp::Rcout << "geom is multi polygon: " << geom.is<multi_polygon>() << std::endl;

    // switch on 'type'

    //const auto& polygons = geom.get<multi_polygon>();

    //mapbox::geometry::multi_polygon<double> poly = geom.get<multi_polygon>();

    //mapbox::geometry::multi_polygon<double> mp(geom.get<multi_polygon>);
    //lst[i] = Rcpp::wrap(geom);

  }
  return lst;

}


template <class T>
std::string writeGeoJSON(const T& t, bool use_convert) {
  if (use_convert) {
    rapidjson_allocator allocator;
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    convert(t, allocator).Accept(writer);
    return buffer.GetString();
  } else {
    return stringify(t);
  }
}



// [[Rcpp::export]]
void rcppParseFeature(const char* js) {

  const auto &data = readGeoJSON(js);
  const auto &feat = data.get<feature>();

  Rcpp::Rcout << "data is feature: " <<  data.is<feature>() << std::endl;
  Rcpp::Rcout << "data is feature collection: " << data.is<feature_collection>() << std::endl;

  const auto &prop = feat.properties;
  Rcpp::Rcout << "feature size: " << prop.size() << std::endl;

}



// [[Rcpp::export]]
void rcppParseGeometry(const char* js) {

  // TODO:
  // switch on type, then, convert type to sfg

  const auto &data = readGeoJSON(js);
  const auto &geom = data.get<geometry>();

  Rcpp::Rcout << "data is feature: " <<  data.is<feature>() << std::endl;
  Rcpp::Rcout << "data is feature collection: " << data.is<feature_collection>() << std::endl;
  Rcpp::Rcout << "data is geometry: " << data.is<geometry>() << std::endl;
//  Rcpp::Rcout << "data is geometry collection: " << data.is<geometry_collection>() << std::endl;

  Rcpp::Rcout << "geom is point: " << geom.is<point>() << std::endl;
  Rcpp::Rcout << "geom is multi point: " << geom.is<multi_point>() << std::endl;
  Rcpp::Rcout << "geom is line string: " << geom.is<line_string>() << std::endl;
  Rcpp::Rcout << "geom is multi line string; " << geom.is<multi_line_string>() << std::endl;
  Rcpp::Rcout << "geom is polygon: " << geom.is<polygon>() << std::endl;
  Rcpp::Rcout << "geom is multi polygon: " << geom.is<multi_polygon>() << std::endl;
  Rcpp::Rcout << "geom is collection: " << geom.is<geometry_collection>() << std::endl;


//  Rcpp::NumericMatrix mat = Rcpp::wrap(line);
//  Rcpp::Rcout << "polygonvector: " << mapt << std::endl;

  Rcpp::String geoString = stringify(geom);

  Rcpp::Rcout << geoString.get_cstring() << std::endl;

}

// [[Rcpp::export]]
Rcpp::NumericMatrix rcppParseLineString(const char* js) {

  const auto &data = readGeoJSON(js);
  const auto &geom = data.get<geometry>();
//  line_string line = geom.get<line_string>();

//  const auto &line = geom.get<line_string>();
  Rcpp::NumericMatrix vec;
  return vec;
}


// [[Rcpp::export]]
Rcpp::NumericVector template_point() {
  mapbox::geometry::point<double> pt(0,0);
  return Rcpp::wrap( pt );
}

// [[Rcpp::export]]
Rcpp::NumericMatrix template_multi_point() {
  mapbox::geometry::multi_point<double> mp({{0,1}, {2,3}, {3,3}, {4,4}});
  return Rcpp::wrap( mp );
}


// [[Rcpp::export]]
Rcpp::NumericMatrix template_linestring() {
  mapbox::geometry::line_string<double> ls({{0, 1}, {2, 3}});
  return Rcpp::wrap( ls );
}

// [[Rcpp::export]]
Rcpp::List template_multilinestring() {
  mapbox::geometry::multi_line_string<double> ml({{{0,1},{0,2}}, {{1,1},{2,2},{3,3}}});
  return Rcpp::wrap( ml );
}

// [[Rcpp::export]]
Rcpp::List template_polygon() {
  mapbox::geometry::polygon<double> pl({{{0,1},{0,2}}, {{1,1},{2,2},{3,3}}});
  return Rcpp::wrap( pl );
}

// [[Rcpp::export]]
Rcpp::List template_multipolygon() {
  mapbox::geometry::multi_polygon<double> mp({
    {
      {
        {0,1},{0,2}
      },
      {
        {1,1},{2,2},{3,3}
      }
    },
    {
      {
        {100, 200},{200 ,300},{300,100}
      },
      {
        {50, 40},{32,30},{23,29}
      }
    }

  });

  return Rcpp::wrap( mp );

}

/*
// [[Rcpp::export]]
mapbox::geometry::point<double> automagic_point(mapbox::geometry::point<double> pt) {
  return pt;
}
*/

/*
// [[Rcpp::export]]
void call_template_point() {
  mapbox::geometry::point pt = template_point();
  Rcpp::NumericVector nv = Rcpp::wrap( pt );
  //return nv;
}
*/

// [[Rcpp::export]]
Rcpp::List MultiPolygonCoordinates(const char* js) {

  const auto& data = readGeoJSON(js);
  const auto& geom = data.get<geometry>();
  const auto& polygons = geom.get<multi_polygon>();

  //polygons == the outer-brackets
  //polygons[0] == the second set of brackets
  //polygons[0][0] == the inner-most brackets


  int n = polygons[0][0].size();
  Rcpp::Rcout << "size: " << n << std::endl;
  Rcpp::NumericMatrix coords(n, 2);
  for(int i = 0; i < n; i++) {
    coords(i,0) = polygons[0][0][i].x;
    coords(i,1) = polygons[0][0][i].y;
  }

  Rcpp::List lst(1);
  Rcpp::List res(1);

  lst.attr("class") = CharacterVector::create("XY", "MULTIPOLYGON", "sfg");
  //res.attr("sfc") = CharacterVector::create("sfc_POLYGON", "sfc");

  lst[0] = coords;
  res[0] = lst;
  //lst.attr("class") = "sfc_POLYGON";
  return res;

}

