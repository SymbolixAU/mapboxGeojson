
#ifndef R_MAPBOXGEOJSON_H
#define R_MAPBOXGEOJSON_H

#include <RcppCommon.h>
#include <mapbox/geometry.hpp>
//#include <mapbox/geometry/point.hpp>

// http://gallery.rcpp.org/articles/custom-templated-wrap-and-as-for-seamingless-interfaces/
// http://gallery.rcpp.org/articles/custom-as-and-wrap-example/

namespace Rcpp {

  //namespace traits {
    template <typename T> SEXP wrap(const mapbox::geometry::point<T>& );
    template <typename T> SEXP wrap(const mapbox::geometry::multi_point<T> &obj);
    template <typename T> SEXP wrap(const mapbox::geometry::line_string<T>& obj);
    template <typename T> SEXP wrap(const mapbox::geometry::multi_line_string<T>& obj);
    template <typename T> SEXP wrap(const mapbox::geometry::linear_ring<T>& obj);
    template <typename T> SEXP wrap(const mapbox::geometry::polygon<T>& obj);
    template <typename T> SEXP wrap(const mapbox::geometry::multi_polygon<T>& obj);
  //}
}

#include <Rcpp.h>


namespace Rcpp {

    template <typename T>
    SEXP wrap(const mapbox::geometry::point<T> &obj) {

      Rcpp::NumericMatrix nm(1, 2);
      nm(0,0) = obj.x;
      nm(0,1) = obj.y;

      return nm;
    };


    template <typename T>
    SEXP wrap(const mapbox::geometry::multi_point<T> &obj) {

      std::vector< mapbox::geometry::point<double> > vec(obj.begin(), obj.end());

      size_t n = obj.size();
      Rcpp::NumericMatrix np(n, 2);

      Rcpp::NumericMatrix nm(n,  2);
      for (int i = 0; i < n; i++ ) {
        nm(i, 0) = vec[i].x;
        nm(i, 1) = vec[i].y;
      }

      return nm;
    }

    template <typename T>
    SEXP wrap(const mapbox::geometry::line_string<T> &obj) {

      std::vector< mapbox::geometry::point<double> > vec(obj.begin(), obj.end());

      size_t n = obj.size();

      Rcpp::NumericMatrix nm(n,  2);
      for (int i = 0; i < n; i++ ) {
        nm(i, 0) = vec[i].x;
        nm(i, 1) = vec[i].y;
      }

      return nm;
    }

    template <typename T>
    SEXP wrap(const mapbox::geometry::multi_line_string<T> &obj) {

      size_t n = obj.size();
      Rcpp::List lst(n);
      for (int i = 0; i < n; i++) {
        mapbox::geometry::line_string<double> ls(obj[i]);
        lst[i] = Rcpp::wrap(ls);
      }
      return lst;
    }

    template <typename T>
    SEXP wrap(const mapbox::geometry::linear_ring<T> &obj) {

      size_t n = obj.size();
      std::vector< mapbox::geometry::point<double> > vec(obj.begin(), obj.end());

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
        mapbox::geometry::linear_ring<double> ls(obj[i]);
        lst[i] = Rcpp::wrap(ls);
      }
      return lst;
    }

    template <typename T>
    SEXP wrap(const mapbox::geometry::multi_polygon<T> &obj) {

      size_t n = obj.size();
      Rcpp::List lst(1);

      for (int i = 0; i < n; i++) {
        mapbox::geometry::polygon<double> pl(obj[i]);

        size_t m = pl.size();
        Rcpp::List polys(m);
        for (int j = 0; j < m; j++) {
          polys[i] = Rcpp::wrap(pl);
        }
        lst[0] = polys;
      }
      return lst;

    }

}


#endif

