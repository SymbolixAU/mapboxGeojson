/*
#include "rmapboxgeojson.h"

namespace Rcpp {

//  namespace traits {

  template <typename T> SEXP wrap(const mapbox::geometry::point<T> & obj){
    //return Rcpp::wrap( pt );

    mapbox::geometry::point<T> pt = obj;
    return Rcpp::wrap( pt );

    //const int RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype ;
    //return Rcpp::Vector< RTYPE >(pt.x, pt.y);
  };

//    template<typename T>
//    SEXP wrap(const mapbox::geometry::point<T>& pt) {
//      mapbox::geometry::point<T> p = pt;
//      return Rcpp::wrap( p );
////      const int RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype ;
////      return Rcpp::Vector< RTYPE >(pt.begin(), pt.end());
//    }

//  }
}
*/
