#include <Rcpp.h>
using namespace Rcpp;

#include "mapbox/geojson.hpp"

// [[Rcpp::depends(mapboxGeometry)]]
// [[Rcpp::depends(mapboxVariant)]]
// [[Rcpp::depends(rapidjsonr)]]

//! Assertion.
/*! \ingroup RAPIDJSON_CONFIG
By default, rapidjson uses C \c assert() for internal assertions.
User can override it by defining RAPIDJSON_ASSERT(x) macro.
*/
#ifndef RAPIDJSON_ASSERT
#define RAPIDJSON_ASSERT(x) ((void)0)
#endif // RAPIDJSON_ASSERT

// don't call #include "rapidjson/allocators.h" directly
#include "rapidjson/error/en.h"
#include "rapidjson/filereadstream.h"
//#include "rapidjson/schema.h"
//#include "rapidjson/stringbuffer.h"
//#include "rapidjson/prettywriter.h"


// [[Rcpp::export]]
void rcppParse(std::string js) {

//  geojson g = parse(js);

  //mapbox::geojson g;
  //mapbox::geojson::parse(js);



}
