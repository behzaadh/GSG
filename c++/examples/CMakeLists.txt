### tests
project(EaxmpleGSGfile CXX C)


# copy the original file to the executable path
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/HAE2D_GASIMPURITIES_PRO_POROSITY.GSG"
   "${CMAKE_CURRENT_BINARY_DIR}/HAE2D_GASIMPURITIES_PRO_POROSITY.GSG" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/reservoir.GSG"
   "${CMAKE_CURRENT_BINARY_DIR}/reservoir.GSG" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/reservoir2.GSG"
   "${CMAKE_CURRENT_BINARY_DIR}/reservoir2.GSG" COPYONLY)


message("Examples:" ${CMAKE_CURRENT_BINARY_DIR})
message("Examples:" ${CMAKE_CURRENT_SOURCE_DIR})


