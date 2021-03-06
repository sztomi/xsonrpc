add_library(xsonrpc STATIC
  ${TINYXML2_SOURCE}

  client.cpp
  dispatcher.cpp
  jsonformathandler.cpp
  jsonreader.cpp
  jsonwriter.cpp
  request.cpp
  response.cpp
  server.cpp
  util.cpp
  value.cpp
  xmlformathandler.cpp
  xmlreader.cpp
  xmlrpcsystemmethods.cpp
  xmlwriter.cpp
)

install(TARGETS xsonrpc ARCHIVE DESTINATION "lib")

target_include_directories(xsonrpc BEFORE PRIVATE
  "${PROJECT_SOURCE_DIR}/include/xsonrpc")

# TinyXML-2
target_include_directories(xsonrpc PRIVATE ${TINYXML2_INCLUDE_DIR})
if (TINYXML2_FOUND)
  target_link_libraries(xsonrpc ${TINYXML2_LIBRARY})
endif()

# RapidJSON
target_include_directories(xsonrpc PRIVATE
  "${PROJECT_SOURCE_DIR}/3pp/rapidjson/include")

# libmicrohttpd
target_include_directories(xsonrpc PRIVATE ${MICROHTTPD_INCLUDE_DIR})
target_link_libraries(xsonrpc ${MICROHTTPD_LIBRARY})

# cURL
target_include_directories(xsonrpc PRIVATE ${CURL_INCLUDE_DIR})
target_link_libraries(xsonrpc ${CURL_LIBRARY})

# Version
target_compile_definitions(xsonrpc PRIVATE
  -DXSONRPC_VERSION="${XSONRPC_VERSION}")
set_target_properties(xsonrpc PROPERTIES VERSION ${XSONRPC_VERSION})
