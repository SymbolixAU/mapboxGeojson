
#ifndef R_MAPBOXGEOJSON_H
#define R_MAPBOXGEOJSON_H

#include <RcppCommon.h>
#include <mapbox/geometry.hpp>
#include <mapbox/variant.hpp>

// http://gallery.rcpp.org/articles/custom-templated-wrap-and-as-for-seamingless-interfaces/
// http://gallery.rcpp.org/articles/custom-as-and-wrap-example/

// TODO(define a mapbox::variant of all the mapbox types?)



typedef mapbox::util::variant<
  mapbox::geometry::point<double>,
  mapbox::geometry::multi_point<double>,
  mapbox::geometry::line_string<double>,
  mapbox::geometry::multi_line_string<double>,
  mapbox::geometry::linear_ring<double>,
  mapbox::geometry::polygon<double>,
  mapbox::geometry::multi_polygon<double>
> mb_variant;



namespace Rcpp {

    template <typename T> SEXP wrap(const mapbox::geometry::point<T>& );
    template <typename T> SEXP wrap(const mapbox::geometry::multi_point<T> &obj);
    template <typename T> SEXP wrap(const mapbox::geometry::line_string<T>& obj);
    template <typename T> SEXP wrap(const mapbox::geometry::multi_line_string<T>& obj);
    template <typename T> SEXP wrap(const mapbox::geometry::linear_ring<T>& obj);
    template <typename T> SEXP wrap(const mapbox::geometry::polygon<T>& obj);
    template <typename T> SEXP wrap(const mapbox::geometry::multi_polygon<T>& obj);

    // template <typename T> SEXP wrap(const mb_variant& obj);
}

#include <Rcpp.h>

namespace Rcpp {

    // template <typename T>
    // SEXP wrap(const mb_variant& obj) {
    //
    // }

    template <typename T>
    SEXP wrap(const mapbox::geometry::point<T> &obj) {

      Rcpp::NumericVector nv(2);
      nv[0] = obj.x;
      nv[1] = obj.y;

      return nv;
    };

    template <typename T>
    SEXP wrap(const mapbox::geometry::multi_point<T> &obj) {

      std::vector< mapbox::geometry::point<T> > vec(obj.begin(), obj.end());
      size_t n = obj.size();
      Rcpp::NumericMatrix nm(n,  2);

      for (int i = 0; i < n; i++ ) {
        nm(i, 0) = vec[i].x;
        nm(i, 1) = vec[i].y;
      }
      nm.attr("class") = Rcpp::CharacterVector::create("XY", "MULTIPOINT", "sfg");
      return nm;
    }

    template <typename T>
    SEXP wrap(const mapbox::geometry::line_string<T> &obj) {

      std::vector< mapbox::geometry::point<T> > vec(obj.begin(), obj.end());
      size_t n = obj.size();
      Rcpp::NumericMatrix nm(n,  2);

      for (int i = 0; i < n; i++ ) {
        nm(i, 0) = vec[i].x;
        nm(i, 1) = vec[i].y;
      }
      nm.attr("class") = Rcpp::CharacterVector::create("XY", "LINESTRING", "sfg");
      return nm;
    }

    template <typename T>
    SEXP wrap(const mapbox::geometry::multi_line_string<T> &obj) {

      size_t n = obj.size();
      Rcpp::List lst(n);

      for (int i = 0; i < n; i++) {
        mapbox::geometry::line_string<T> ls(obj[i]);
        lst[i] = Rcpp::wrap(ls);
      }
      lst.attr("class") = Rcpp::CharacterVector::create("XY", "MULTILINESTRING", "sfg");
      return lst;
    }

    template <typename T>
    SEXP wrap(const mapbox::geometry::linear_ring<T> &obj) {

      size_t n = obj.size();
      std::vector< mapbox::geometry::point<T> > vec(obj.begin(), obj.end());

      Rcpp::NumericMatrix nm(n,  2);
      for (int i = 0; i < n; i++ ) {
        nm(i, 0) = vec[i].x;
        nm(i, 1) = vec[i].y;
      }
      return nm;
    }

    template <typename T>
    SEXP wrap(const mapbox::geometry::polygon<T> &obj) {

      size_t n = obj.size();
      Rcpp::List lst(n);

      for (int i = 0; i < n; i++) {
        mapbox::geometry::linear_ring<T> ls(obj[i]);
        lst[i] = Rcpp::wrap(ls);
      }
      lst.attr("class") = Rcpp::CharacterVector::create("XY", "POLYGON", "sfg");
      return lst;
    }

    template <typename T>
    SEXP wrap(const mapbox::geometry::multi_polygon<T> &obj) {

      size_t n = obj.size();
      Rcpp::List lst(n);

      for (int i = 0; i < n; i++) {
        mapbox::geometry::polygon<T> pl(obj[i]);
        lst[i] = Rcpp::wrap(pl);
      }
      lst.attr("class") = Rcpp::CharacterVector::create("XY", "MULTIPOLYGON", "sfg");
      return lst;
    }
}


#endif

