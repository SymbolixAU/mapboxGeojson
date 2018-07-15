// // NOTES:
// /*
//  * mapboxGeojson: https://github.com/mapbox/geojson-cpp
//  * - a c++ library for converting GeoJSON into geometry.hpp representation
//  *
//  */
//
// // sf
// // - a geometry is an 'sfg'
// // - a feature is an 'sfc'
// // - a collection of 'sfg's is an 'sfc' (with extra attributes)
// // - an 'sfc' with properties is an 'sf'
//
// // - how does it compare to what
// // https://github.com/r-spatial/sf/issues/185
// // does?
// // - can ^^ handle an array of geojson?
//
//
// // [[Rcpp::depends(mapboxGeometry)]]
// // [[Rcpp::depends(mapboxVariant)]]
// // [[Rcpp::depends(rapidjsonr)]]
//
// #include <mapbox/geojson.hpp>
// #include <mapbox/geojson/rapidjson.hpp>
// #include <mapbox/geometry.hpp>
// #include <mapbox/geometry/point.hpp>
// #include <mapbox/geometry/multi_point.hpp>
// #include <mapbox/geometry/line_string.hpp>
// //#include <mapbox/variant.hpp>
//
// #include "rapidjson/writer.h"
// #include "rapidjson/stringbuffer.h"
//
// //#include "mapbox/RcppDataTypes.h"
//
// //#include "rmapboxgeojson.h"
// #include "r_mapboxgeometry.hpp"
// //#include "sfg.h"
// #include <Rcpp.h>
//
// using namespace mapbox::geojson;
// //using namespace mapbox::geometry;
//
// using namespace Rcpp;
// //using namespace rapidjson;
//
// #include <cassert>
// #include <fstream>
// #include <sstream>
// #include <iostream>
//
// // TODO:
// // - error checking - invalid GeoJSON
//
// geojson readGeoJSON(const char* json) {
//   return parse(json);
// }
//
// Rcpp::CharacterVector sfg_attributes(std::string geom_type) {
//   return Rcpp::CharacterVector::create("XY", geom_type, "sfg");
// }
//
// template <typename T>
// Rcpp::NumericVector get_point(const mapbox::geometry::point<T>& pt) {
//   Rcpp::NumericVector nv = Rcpp::wrap(pt);
//   nv.attr("class") = sfg_attributes("POINT");
//   return nv;
// }
//
// template <typename T>
// Rcpp::NumericMatrix get_multi_point(const mapbox::geometry::multi_point<T>& mpt) {
//   Rcpp::NumericMatrix nm = Rcpp::wrap(mpt);
//   nm.attr("class") = sfg_attributes("MULTIPOINT");
//   return nm;
// }
//
// template <typename T>
// Rcpp::NumericMatrix get_line_string(const mapbox::geometry::line_string<T>& ls) {
//   Rcpp::NumericMatrix nm = Rcpp::wrap(ls);
//   nm.attr("class") = sfg_attributes("LINESTRING");
//   return nm;
// }
//
// template <typename T>
// Rcpp::List get_multi_line_string(const mapbox::geometry::multi_line_string<T>& mls) {
//   Rcpp::List lst = Rcpp::wrap(mls);
//   lst.attr("class") = sfg_attributes("MULTILINESTRING");
//   return lst;
// }
//
// template <typename T>
// Rcpp::List get_polygon(const mapbox::geometry::polygon<T> &pl) {
//   Rcpp::List lst = Rcpp::wrap(pl);
//   lst.attr("class") = sfg_attributes("POLYGON");
//   return lst;
// }
//
// template <typename T>
// Rcpp::List get_multi_polygon(const mapbox::geometry::multi_polygon<T> &pl) {
//   Rcpp::List lst = Rcpp::wrap(pl);
//   lst.attr("class") = sfg_attributes("MULTIPOLYGON");
//   return lst;
// }
//
// /*
//  * GeoJSON to SFG
//  *
//  * @param sfc Rcpp::List storing the objects
//  * @param i index of sfc object
//  * @param js returns an `sfg` object from the GeoJSON geometry
//  */
// void get_geometry_object(Rcpp::List& sfc, int i, geojson geo, std::string& g_type) {
//
//   const auto &geom = geo.get<geometry>();
//   //std::cout << "debug: geojson which: " << geom.which() << std::endl;
//
//   if (g_type == "Point") {
//     sfc[i] = get_point(geom.get<point>());
//
//   } else if (g_type == "MultiPoint") {
//     sfc[i] = get_multi_point(geom.get<multi_point>());
//
//   } else if (g_type == "LineString") {
//     sfc[i] = get_line_string(geom.get<line_string>());
//
//   } else if (g_type == "MultiLinestring") {
//     sfc[i] = get_multi_line_string(geom.get<multi_line_string>());
//
//   } else if (g_type == "Polygon") {
//     sfc[i] = get_polygon(geom.get<polygon>());
//
//   } else if (g_type == "MultiPolygon") {
//     sfc[i] = get_multi_polygon(geom.get<multi_polygon>());
//
//   } else {
//     Rcpp::stop("unknown sfg type");
//   }
//
// }
//
//
// /*
//  * Parse Geometry Object
//  *
//  * Parses each JSON object ('{}')
//  *
//  */
// void parse_geometry_object(Rcpp::List& sfc, int i, const Value &val) {
//
//   std::string geom_type = val["type"].GetString();
//
//   StringBuffer sb;
//   Writer<StringBuffer> writer(sb);
//   val.Accept(writer);
//   std::string s = sb.GetString();
//
//   const char* myjs = sb.GetString();
//   const auto& data = readGeoJSON(myjs);
//
//   get_geometry_object(sfc, i, data, geom_type);
// }
//
// Rcpp::List parse_geometry_collection_object(const Value &val) {
//
//   Rcpp::List geom_collection(val.Size());
//   std::string geom_type;
//
//   for (int i = 0; i < val.Size(); i++) {
//     const Value& gcval = val[i];
//     geom_type = gcval["type"].GetString();
//     parse_geometry_object(geom_collection, i, gcval);
//   }
//   geom_collection.attr("class") = sfg_attributes("GEOMETRYCOLLECTION");
//
//   return geom_collection;
// }
//
// Rcpp::List parse_feature_collection_object(const Value &feat) {
//
//   Rcpp::List feature_collection(feat.Size());
//   std::string geom_type;
//
//   for (int i = 0; i < feat.Size(); i++) {
//     const Value& fcval = feat[i];
//
//     // need to switch on 'type'
//
//   }
//
// }
//
// void parse_geojson(rapidjson::Document& d, const Value& v, Rcpp::List& sfc, int i) {
//
//   std::string geom_type;
//
//   if( v.HasMember("type") == FALSE )  Rcpp::stop("No 'type' member - invalid GeoJSON");
//
//   geom_type = v["type"].GetString();
//
//   if (geom_type == "Feature") {
//
//     // get the geometry from the feature
//     const Value& geom = v["geometry"];
//
//     // TODO: implement check geometry exists
//     //bool b = geom.HasMember("geometry");
//     parse_geometry_object(sfc, i, geom);
//
//   } else if (geom_type == "FeatureCollection") {
//
//     // TODO:
//     // implement a check for 'feature' array
//     //const Value& feat = v["features"];
//
//     // iterate through feature[] array
//
//   } else if (geom_type == "GeometryCollection") {
//
//     const Value& gc = v["geometries"];
//     sfc[i] = parse_geometry_collection_object(gc);
//
//   } else {  // geometry
//     parse_geometry_object(sfc, i, v);
//   }
// }
//
// void parse_geojson_object(rapidjson::Document& d, Rcpp::List& sfg) {
//   const Value& v = d;
//   parse_geojson(d, v, sfg, 0);
//
// }
//
// void parse_geojson_array(rapidjson::Document& d, Rcpp::List& sfc, int i) {
//   const Value& v = d[i];
//   parse_geojson(d, v, sfc, i);
// }
//
//
// Rcpp::List geojson_to_sf(const char* js) {
//
//   rapidjson::Document d;
//   d.Parse(js);
//   Rcpp::List sfg(1);
//
//   if( d.IsObject() ) {
//
//     parse_geojson_object(d, sfg);
//     return sfg;
//
//   } else if (d.IsArray()) {
//
//     Rcpp::List sfc(d.Size());
//     for (int i = 0; i < d.Size(); i++) {
//       parse_geojson_array(d, sfc, i);
//     }
//     return sfc;
//   }
//   return sfg;
// }
//
// // Needs to accept a vector of GeoJSON
// // [[Rcpp::export]]
// Rcpp::List rcpp_geojson_to_sf(Rcpp::StringVector geojson) {
//
//   // iterate over the geojson
//   int n = geojson.size();
//   Rcpp::List lst(n);
//
//   for (int i = 0; i < n; i++ ){
//
//     // can be a vector of individual geoJSON,
//     // or a single large geoJSON object
//     //
//     // VECTOR:
//     // - each vector item wil be a row of an 'sf' / 'sfc' ?
//     // switch on type
//     //
//     lst[i] = geojson_to_sf(geojson[i]);
//   }
//
//   return lst;
// }
//
//
// template <class T>
// std::string writeGeoJSON(const T& t, bool use_convert) {
//   if (use_convert) {
//     rapidjson_allocator allocator;
//     rapidjson::StringBuffer buffer;
//     rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
//     convert(t, allocator).Accept(writer);
//     return buffer.GetString();
//   } else {
//     return stringify(t);
//   }
// }
//
//
//
// // [[Rcpp::export]]
// void rcppParseFeature(const char* js) {
//
//   const auto &data = readGeoJSON(js);
//   const auto &feat = data.get<feature>();
//
//   Rcpp::Rcout << "data is feature: " <<  data.is<feature>() << std::endl;
//   Rcpp::Rcout << "data is feature collection: " << data.is<feature_collection>() << std::endl;
//
//   const auto &prop = feat.properties;
//   Rcpp::Rcout << "feature size: " << prop.size() << std::endl;
//
// }
//
//
//
// // [[Rcpp::export]]
// void rcppParseGeometry(const char* js) {
//
//   // TODO:
//   // switch on type, then, convert type to sfg
//
//   const auto &data = readGeoJSON(js);
//   const auto &geom = data.get<geometry>();
//
//   Rcpp::Rcout << "data is feature: " <<  data.is<feature>() << std::endl;
//   Rcpp::Rcout << "data is feature collection: " << data.is<feature_collection>() << std::endl;
//   Rcpp::Rcout << "data is geometry: " << data.is<geometry>() << std::endl;
// //  Rcpp::Rcout << "data is geometry collection: " << data.is<geometry_collection>() << std::endl;
//
//   Rcpp::Rcout << "geom is point: " << geom.is<point>() << std::endl;
//   Rcpp::Rcout << "geom is multi point: " << geom.is<multi_point>() << std::endl;
//   Rcpp::Rcout << "geom is line string: " << geom.is<line_string>() << std::endl;
//   Rcpp::Rcout << "geom is multi line string; " << geom.is<multi_line_string>() << std::endl;
//   Rcpp::Rcout << "geom is polygon: " << geom.is<polygon>() << std::endl;
//   Rcpp::Rcout << "geom is multi polygon: " << geom.is<multi_polygon>() << std::endl;
//   Rcpp::Rcout << "geom is collection: " << geom.is<geometry_collection>() << std::endl;
//
//
// //  Rcpp::NumericMatrix mat = Rcpp::wrap(line);
// //  Rcpp::Rcout << "polygonvector: " << mapt << std::endl;
//
//   Rcpp::String geoString = stringify(geom);
//
//   Rcpp::Rcout << geoString.get_cstring() << std::endl;
//
// }
//
// // [[Rcpp::export]]
// Rcpp::NumericMatrix rcppParseLineString(const char* js) {
//
//   const auto &data = readGeoJSON(js);
//   const auto &geom = data.get<geometry>();
// //  line_string line = geom.get<line_string>();
//
// //  const auto &line = geom.get<line_string>();
//   Rcpp::NumericMatrix vec;
//   return vec;
// }
//
//
// // [[Rcpp::export]]
// Rcpp::NumericVector template_point() {
//   mapbox::geometry::point<double> pt(0,0);
//   return Rcpp::wrap( pt );
// }
//
// // [[Rcpp::export]]
// Rcpp::NumericMatrix template_multi_point() {
//   mapbox::geometry::multi_point<double> mp({{0,1}, {2,3}, {3,3}, {4,4}});
//   return Rcpp::wrap( mp );
// }
//
//
// // [[Rcpp::export]]
// Rcpp::NumericMatrix template_linestring() {
//   mapbox::geometry::line_string<double> ls({{0, 1}, {2, 3}});
//   return Rcpp::wrap( ls );
// }
//
// // [[Rcpp::export]]
// Rcpp::List template_multilinestring() {
//   mapbox::geometry::multi_line_string<double> ml({{{0,1},{0,2}}, {{1,1},{2,2},{3,3}}});
//   return Rcpp::wrap( ml );
// }
//
// // [[Rcpp::export]]
// Rcpp::List template_polygon() {
//   mapbox::geometry::polygon<double> pl({{{0,1},{0,2}}, {{1,1},{2,2},{3,3}}});
//   return Rcpp::wrap( pl );
// }
//
//
//
// // [[Rcpp::export]]
// Rcpp::List template_multipolygon() {
//   mapbox::geometry::multi_polygon<double> mp({
//     {
//       {
//         {0,1},{0,2}
//       },
//       {
//         {1,1},{2,2},{3,3}
//       }
//     },
//     {
//       {
//         {100, 200},{200 ,300},{300,100}
//       },
//       {
//         {50, 40},{32,30},{23,29}
//       }
//     }
//
//   });
//
//   return Rcpp::wrap( mp );
//
// }
//
// /*
// // [[Rcpp::export]]
// mapbox::geometry::point<double> automagic_point(mapbox::geometry::point<double> pt) {
//   return pt;
// }
// */
//
// /*
// // [[Rcpp::export]]
// void call_template_point() {
//   mapbox::geometry::point pt = template_point();
//   Rcpp::NumericVector nv = Rcpp::wrap( pt );
//   //return nv;
// }
// */
//
// // [[Rcpp::export]]
// Rcpp::List MultiPolygonCoordinates(const char* js) {
//
//   const auto& data = readGeoJSON(js);
//   const auto& geom = data.get<geometry>();
//   const auto& polygons = geom.get<multi_polygon>();
//
//   //polygons == the outer-brackets
//   //polygons[0] == the second set of brackets
//   //polygons[0][0] == the inner-most brackets
//
//
//   int n = polygons[0][0].size();
//   Rcpp::Rcout << "size: " << n << std::endl;
//   Rcpp::NumericMatrix coords(n, 2);
//   for(int i = 0; i < n; i++) {
//     coords(i,0) = polygons[0][0][i].x;
//     coords(i,1) = polygons[0][0][i].y;
//   }
//
//   Rcpp::List lst(1);
//   Rcpp::List res(1);
//
//   lst.attr("class") = CharacterVector::create("XY", "MULTIPOLYGON", "sfg");
//   //res.attr("sfc") = CharacterVector::create("sfc_POLYGON", "sfc");
//
//   lst[0] = coords;
//   res[0] = lst;
//   //lst.attr("class") = "sfc_POLYGON";
//   return res;
//
// }
//
