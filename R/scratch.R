#
# js <- "{\"type\": \"LineString\",\"coordinates\": [[30.5, 50.5], [30.6, 50.6], [25.0, 23.3]]}"
# mapboxGeojson:::rcppParseGeometry(js)

# url <- "https://raw.githubusercontent.com/mapbox/geojson-cpp/master/test/fixtures/line-string.json"
# js <- paste0(readLines(url), collapse = "")
# mapboxGeojson:::rcppParseGeometry(js)


# url <- "https://raw.githubusercontent.com/mapbox/geojson-cpp/master/test/fixtures/point.json"
# js <- paste0(readLines(url), collapse = "")
# mapboxGeojson:::rcppParseGeometry(js)


# url <- "https://raw.githubusercontent.com/mapbox/geojson-cpp/master/test/fixtures/polygon.json"
# js <- paste0(readLines(url), collapse = "")
# mapboxGeojson:::rcppParseGeometry(js)


# url <- "https://raw.githubusercontent.com/mapbox/geojson-cpp/master/test/fixtures/multi-polygon.json"
# js <- paste0(readLines(url), collapse = "")
# mapboxGeojson:::rcppParseGeometry(js)
#
# mapboxGeojson:::MultiPolygonCoordinates(js)



### Errors: not a geometry??
# url <- "https://raw.githubusercontent.com/mapbox/geojson-cpp/master/test/fixtures/feature.json"
# js <- paste0(readLines(url), collapse = "")
# mapboxGeojson:::rcppParseGeometry(js)
#
# mapboxGeojson:::rcppParseFeature(js)

# url <- "https://raw.githubusercontent.com/mapbox/geojson-cpp/master/test/fixtures/geometry-collection.json"
# js <- paste0(readLines(url), collapse = "")
# mapboxGeojson:::rcppParseGeometry(js)

# js <- '{
#     "type": "GeometryCollection",
#     "geometries": [
#         {"type": "Point", "coordinates": [100.0, 0.0]},
#         {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]},
#         {"type" : "MultiPoint", "coordinates" : [[0,0], [1,1], [2,2]]}
#     ]
# }'
#
# mapboxGeojson:::rcppParseGeometry(js)

## Need to work out what 'types' there are, then can loop over those
## (as we'll then have the size())
## once we have the types, we can construct the 'sf' object?

# mp <- '
# {
#   "type" : "MultiPolygon",
#   "coordinates" : [ [ [ [0.0, 3.0], [1.0, 1.0], [2.0, 7.0], [0.0, 0.0] ] ] ]
# }'

# mapboxGeojson:::MultiPolygonCoordinates(mp)
# mapboxGeojson:::MultiPolygonCoordinates(js)

# pol = st_sfc(st_polygon(list(cbind(c(0,3,3,0,0),c(0,0,3,3,0)))))
# pol

# js <- '{
#     "type": "FeatureCollection",
# "features": [{
# "type": "Feature",
# "properties": null,
# "geometry": {"type": "Point", "coordinates": [100.0, 0.0]}
# }, {
# "type": "Feature",
# "properties": null,
# "geometry": {"type": "LineString", "coordinates": [[101.0, 0.0], [102.0, 1.0]]}
# }]
# }'
#
# mapboxGeojson:::rcppParseFeature(js)

# mapboxGeojson:::rcppParse("https://raw.githubusercontent.com/mapbox/geojson-cpp/master/test/fixtures/line-string.json")
# mapboxGeojson:::rcppParse("~/Documents/github/mapboxGeojson/data/fixtures/line-string.json")


# js <- "{\"type\": \"Point\",\"coordinates\": [30.5, 50.5]}"

# js <- '[
# {
#   "type": "Feature",
#   "geometry": {
#     "type": "Polygon",
#     "coordinates": [
#       [
#         [-10.0, -10.0],
#         [10.0, -10.0],
#         [10.0, 10.0],
#         [-10.0, -10.0]
#       ]
#     ]
#   }
# },
# {
#   "type": "Feature",
#   "geometry": {
#     "type": "MultiPolygon",
#     "coordinates": [
#       [
#         [
#           [180.0, 40.0], [180.0, 50.0], [170.0, 50.0],
#           [170.0, 40.0], [180.0, 40.0]
#         ]
#       ],
#       [
#         [
#           [-170.0, 40.0], [-170.0, 50.0], [-180.0, 50.0],
#           [-180.0, 40.0], [-170.0, 40.0]
#         ]
#       ]
#     ]
#   }
# },
# {
# "type": "Polygon",
#     "coordinates": [
#       [
#         [-10.0, -10.0],
#         [10.0, -10.0],
#         [10.0, 10.0],
#         [-10.0, -10.0]
#       ]
#     ]
# },
# {
#   "type": "FeatureCollection",
#   "features": [
#     {
#       "type": "Feature",
#       "properties": null,
#       "geometry": {
#         "type": "Point",
#         "coordinates": [100.0, 0.0]
#       }
#     },
#     {
#       "type": "Feature",
#       "properties": null,
#       "geometry": {
#         "type": "LineString",
#         "coordinates": [
#           [101.0, 0.0],
#           [102.0, 1.0]
#         ]
#       }
#     }
#   ]
# },
# {
#   "type": "GeometryCollection",
#   "geometries": [
#     {
#       "type": "Point",
#       "coordinates": [100.0, 0.0]
#     },
#     {
#       "type": "LineString",
#       "coordinates": [
#         [101.0, 0.0],
#         [102.0, 1.0]
#       ]
#     },
#     {
#       "type" : "MultiPoint",
#       "coordinates" : [
#         [0,0],
#         [1,1],
#         [2,2]
#       ]
#     }
#   ]
# }
# ]'
# mapboxGeojson:::parseSomething(js)
#
# js <- '{
#   "type": "Feature",
#   "geometry": {
#     "type": "MultiPolygon",
#     "coordinates": [
#       [
#         [
#           [180.0, 40.0], [180.0, 50.0], [170.0, 50.0],
#           [170.0, 40.0], [180.0, 40.0]
#         ]
#       ],
#       [
#         [
#           [-170.0, 40.0], [-170.0, 50.0], [-180.0, 50.0],
#           [-180.0, 40.0], [-170.0, 40.0]
#         ]
#       ]
#     ]
#   }
# }'
# mapboxGeojson:::parseSomething(js)


# js <- c("{\"geodesic\":true,\"type\":\"Point\",\"coordinates\":[-118.68152563269095,36.43764870908927]}",
#          "{\"geodesic\":true,\"type\":\"Point\",\"coordinates\":[-118.67408758213843,36.43366018922779]}",
#          "{\"geodesic\":true,\"type\":\"Point\",\"coordinates\":[-118.67708346361097,36.44208638659282]}",
#          "{\"geodesic\":true,\"type\":\"Point\",\"coordinates\":[-118.67886661944996,36.44110273135671]}",
#          "{\"geodesic\":true,\"type\":\"Point\",\"coordinates\":[-118.68089232041565,36.44173155205561]}")
#
# mapboxGeojson:::rcpp_geojson_to_sf(js)

# library(geojsonio)
# library(microbenchmark)
#
# file <- system.file("examples", "california.geojson", package = "geojsonio")
#
# microbenchmark(
#   geojsonio = {
#     ## doesn't output as SF
#     out <- geojson_read(file)
#   },
#   mapbox = {
#     geo <- paste0(readLines(file), collapse = "")
#     mapboxGeojson:::rcpp_geojson_to_sf(geo)
#   },
#   sf = {
#     ## can sf handle a vector of geoJSON?
#     ## or non-Collections? (i.e., array of objects?), or character vector?
#     sf::st_read(file, quiet = T)
#   },
#   times = 2
# )

# Unit: milliseconds
#      expr         min          lq       mean     median         uq        max neval
# geojsonio 1050.364307 1050.364307 1061.61524 1061.61524 1072.86617 1072.86617     2
#    mapbox   16.654561   16.654561   17.12597   17.12597   17.59737   17.59737     2
#        sf    9.815147    9.815147   10.46490   10.46490   11.11466   11.11466     2

