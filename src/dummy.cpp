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


// [[Rcpp::depends(mapboxGeometry)]]
// [[Rcpp::depends(mapboxVariant)]]
// [[Rcpp::depends(rapidjsonr)]]

#include <mapbox/geojson.hpp>
#include <mapbox/geojson/rapidjson.hpp>
#include <mapbox/geometry.hpp>

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

//#include "mapbox/RcppDataTypes.h"

using namespace mapbox::geojson;

#include <Rcpp.h>

using namespace Rcpp;

#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>

geojson readGeoJSON(const char* json) {

    return parse(json);
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

  // if there is a collection, get the size
//  const auto &collection = geom.get<geometry_collection>();
//  Rcpp::Rcout << "Collection size: " << collection.size() << std::endl;

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
Rcpp::List MultiPolygonCoordinates(const char* js) {

  const auto &data = readGeoJSON(js);
  const auto &geom = data.get<geometry>();
  const auto &polygons = geom.get<multi_polygon>();

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

  lst.attr("class") = CharacterVector::create("XY", "POLYGON", "sfg");
  res.attr("sfc") = CharacterVector::create("sfc_POLYGON", "sfc");

  lst[0] = coords;
  res[0] = lst;
  //lst.attr("class") = "sfc_POLYGON";
  return res;

}

