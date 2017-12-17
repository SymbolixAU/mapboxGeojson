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

#include <Rcpp.h>
using namespace Rcpp;

#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace mapbox::geojson;

geojson readGeoJSON(const char* json) {

//  std::ifstream t(path.c_str());

//  Rcpp::Rcout << path.c_str() << std::endl;

//  std::stringstream buffer;
//  buffer << t.rdbuf();

//  if (use_convert) {
//    rapidjson_document d;

//    std::string s = d["hello"].GetString();
//    Rcpp::Rcout << s << std::endl;

//    d.Parse<0>(buffer.str().c_str());
//    return convert(d);
//  } else {
    return parse(json);
//  }
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


}


// [[Rcpp::export]]
void rcppParseGeometry(const char* js) {

//  const auto &data = readGeoJSON("https://raw.githubusercontent.com/mapbox/geojson-cpp/master/test/fixtures/line-string.json", true);
//  const auto &data = readGeoJSON("file://Users/dave/Documents/github/mapboxGeojson/data/fixtures/line-string.json", true);
//  geojson g = parse(js);

//  const char* json = "{\"type\": \"LineString\",\"coordinates\": [[30.5, 50.5], [30.6, 50.6], [25.0, 23.3]]}";
  const auto &data = readGeoJSON(js);
  //mapbox::geojson g;
  //mapbox::geojson::parse(js);

  const auto &geom = data.get<geometry>();
//  const auto &points = geom.get<line_string>();


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

//  Rcpp::Rcout << "points size: " << points.size() << std::endl;

//  Rcpp::NumericVector lst = points;

  Rcpp::String geoString = stringify(geom);
//  Rcpp::String pointString = stringify(points);

//  Rcpp::Rcout << points << std::endl;
  Rcpp::Rcout << geoString.get_cstring() << std::endl;
//  Rcpp::Rcout << pointString.get_cstring() << std::endl;

}



