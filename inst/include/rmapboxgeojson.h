
#ifndef R_MAPBOXGEOJSON_H
#define R_MAPBOXGEOJSON_H

#include <RcppCommon.h>
#include <mapbox/geometry.hpp>
//#include <mapbox/geometry/point.hpp>

// http://gallery.rcpp.org/articles/custom-templated-wrap-and-as-for-seamingless-interfaces/
// http://gallery.rcpp.org/articles/custom-as-and-wrap-example/

namespace Rcpp {

  //namespace traits {
    template <typename T> SEXP wrap(const mapbox::geometry::point<T>& obj);

    template <typename T> SEXP wrap(const mapbox::geometry::line_string<T>& obj);
  //}
}

#include <Rcpp.h>

/*
template <typename T> SEXP Rcpp::wrap(const mapbox::geometry::point<T>& pt) {
  return Rcpp::wrap( pt );
}
*/


namespace Rcpp {

  //namespace traits {
    // Defined wrap case
    template <typename T> SEXP wrap(const mapbox::geometry::point<T> &obj) {
      //return Rcpp::wrap( pt );
      Rcpp::NumericVector nv(2);
      nv[0] = obj.x;
      nv[1] = obj.y;
      return nv;
      //mapbox::geometry::point<T> pt = obj;
      //return Rcpp::wrap( pt );

      //const int RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype ;
      //return Rcpp::Vector< RTYPE >(pt);
    };
  //}

    template <typename T> SEXP wrap(const mapbox::geometry::line_string<T> &obj) {
      //const int RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype ;
      //return Rcpp::Vector< RTYPE >(obj.begin(), obj.end());
      // TODO:
      // linestring is a NumericMatrix of points
    }

}


#endif

