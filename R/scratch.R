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


### Errors: not a geometry??
# url <- "https://raw.githubusercontent.com/mapbox/geojson-cpp/master/test/fixtures/feature.json"
# js <- paste0(readLines(url), collapse = "")
# mapboxGeojson:::rcppParseGeometry(js)
#
# mapboxGeojson:::rcppParseFeature(js)
