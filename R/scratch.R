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

