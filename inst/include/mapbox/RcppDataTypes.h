
// http://gallery.rcpp.org/articles/custom-templated-wrap-and-as-for-seamingless-interfaces/

#include <RcppCommon.h>

// [[Rcpp::depends(mapboxGeometry)]]
// [[Rcpp::depends(mapboxVariant)]]
// [[Rcpp::depends(rapidjsonr)]]


//#include <mapbox/geometry.hpp>
//#include <mapbox/variant.hpp>

#include "mapbox/geojson.hpp"

namespace Rcpp {

    namespace traits{

    // Support for wrap
    template <typename T> SEXP wrap(const mapbox::geometry::line_string<T> &obj);

  }
}

#include <Rcpp.h>

namespace Rcpp {
  namespace traits {

    template <typename T> SEXP wrap(const mapbox::geometry::line_string<T> &obj){
      const int RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype;

      return Rcpp::Vector< RTYPE >(obj.begin(), obj.end());
    };

  }
}


