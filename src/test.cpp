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


// streams:
// https://github.com/mapbox/geometry.hpp/issues/56
template <class T>
std::ostream& operator<<(std::ostream& os, const mapbox::geometry::point<T>& point) {
  return os << "[" << point.x << "," << point.y << "]";
}

template <class T>
std::ostream& operator<<(std::ostream& os, const mapbox::geometry::line_string<T>& line_string) {
  os << "[";
  bool first = true;
  for (const auto& point : line_string) {
    if (first) first = false; else os << ",";
    os << point;
  }
  os << "]";
  return os;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const mapbox::geometry::linear_ring<T>& linear_ring) {
  os << "[";
  bool first = true;
  for (const auto& point : linear_ring) {
    if (first) first = false; else os << ",";
    os << point;
  }
  os << "]";
  return os;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const mapbox::geometry::polygon<T>& polygon) {
  os << "[";
  bool first = true;
  for (const auto& ring : polygon) {
    if (first) first = false; else os << ",";
    os << ring;
  }
  os << "]";
  return os;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const mapbox::geometry::multi_point<T>& multi_point) {
  os << "[";
  bool first = true;
  for (const auto& point : multi_point) {
    if (first) first = false; else os << ",";
    os << point;
  }
  os << "]";
  return os;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const mapbox::geometry::multi_line_string<T>& multi_line_string) {
  os << "[";
  bool first = true;
  for (const auto& line_string : multi_line_string) {
    if (first) first = false; else os << ",";
    os << line_string;
  }
  os << "]";
  return os;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const mapbox::geometry::multi_polygon<T>& multi_polygon) {
  os << "[";
  bool first = true;
  for (const auto& polygon : multi_polygon) {
    if (first) first = false; else os << ",";
    os << polygon;
  }
  os << "]";
  return os;
}

template <class T>
std::ostream& operator<<(std::ostream&, const mapbox::geometry::geometry_collection<T>&);

template <class T>
std::ostream& operator<<(std::ostream& os, const mapbox::geometry::geometry<T>& geometry) {
  geometry.match(
    [&os] (const mapbox::geometry::point<T>& point) {
      os << "Point" << point;
    },
    [&os] (const mapbox::geometry::line_string<T>& line_string) {
      os << "LineString" << line_string;
    },
    [&os] (const mapbox::geometry::polygon<T>& polygon) {
      os << "Polygon" << polygon;
    },
    [&os] (const mapbox::geometry::multi_point<T>& multi_point) {
      os << "MultiPoint" << multi_point;
    },
    [&os] (const mapbox::geometry::multi_line_string<T>& multi_line_string) {
      os << "MultiLineString" << multi_line_string;
    },
    [&os] (const mapbox::geometry::multi_polygon<T>& multi_polygon) {
      os << "MultiPolygon" << multi_polygon;
    },
    [&os] (const mapbox::geometry::geometry_collection<T>& geometry_collection) {
      os << "GeometryCollection" << geometry_collection;
    }
  );
  return os;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const mapbox::geometry::geometry_collection<T>& geometry_collection) {
  os << "[";
  bool first = true;
  for (const auto& geometry : geometry_collection) {
    if (first) first = false; else os << ",";
    os << geometry;
  }
  os << "]";
  return os;
}

std::ostream& operator<<(std::ostream& os, const mapbox::geometry::null_value_t&) {
  return os << "<null>";
}

std::ostream& operator<<(std::ostream& os, const mapbox::geometry::value&);

std::ostream& operator<<(std::ostream& os, const mapbox::geometry::property_map& map) {
  for (const auto& kv : map) {
    os << "  - " << kv.first << ":" << kv.second << std::endl;
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const mapbox::geometry::value& value) {
  value.match(
    [&os] (const std::vector<mapbox::geometry::value>& array) {
      os << "[";
      bool first = true;
      for (const auto& v : array) {
        if (first) first = false; else os << ",";
        os << v;
      }
      os << "]";
    },
    [&os] (const mapbox::geometry::property_map& map) {
      for (const auto& kv : map) {
        os << "  - " << kv.first << ":" << kv.second << std::endl;
      }
    },
    [&os] (const auto& other) {
      os << other;
    }
  );
  return os;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const mapbox::geometry::feature<T>& feature) {
  os << "Feature";
  if (feature.id) {
    os << " (ID: ";
    feature.id->match([&os] (const auto& id) { os << id; });
    os << ")";
  }
  os << std::endl;
  os << feature.properties;
  os << feature.geometry;
  os << std::endl;
  return os;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const mapbox::geometry::feature_collection<T>& feature_collection) {
  os << "FeatureCollection" << std::endl;
  for (const auto& feature : feature_collection) {
    os << feature;
  }
  return os;
}


// [[Rcpp::export]]
void testFeature(const char* geojson) {
  const auto &data = readGeoJSON(geojson);
  const auto &f = data.get<feature>();
  std::cout << f << std::endl;
}


// [[Rcpp::export]]
void testFeatureCollection(const char* geojson) {
  const auto &data = readGeoJSON(geojson);
  const auto &f = data.get<feature_collection>();
  std::cout << f << std::endl;
}





