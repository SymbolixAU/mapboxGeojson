#include <mapbox/geojson.hpp>
#include <mapbox/geojson/rapidjson.hpp>
#include <mapbox/geometry.hpp>

// [[Rcpp::depends(mapboxGeometry)]]
// [[Rcpp::depends(mapboxVariant)]]
// [[Rcpp::depends(rapidjsonr)]]

#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>

#include <Rcpp.h>

using namespace mapbox::geojson;

geojson readGeoJSON(const char* json) {
  return parse(json);
}

// geojson readGeoJSON(const std::string &path, bool use_convert) {
//   std::ifstream t(path.c_str());
//   std::stringstream buffer;
//   buffer << t.rdbuf();
//
//   if (use_convert) {
//     rapidjson_document d;
//     d.Parse<0>(buffer.str().c_str());
//     return convert(d);
//   } else {
//     return parse(buffer.str());
//   }
// }

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
void testFeature(const char* geojson) {

  const auto &data = readGeoJSON(geojson);

  //assert(data.is<feature>());

  const auto &f = data.get<feature>();



 // assert(f.geometry.is<point>());

}






