CMAKE_MINIMUM_REQUIRED (VERSION 3.0)
PROJECT (item6)

IF (CMAKE_VERSION VERSION_LESS "3.1")
  SET(CMAKE_CXX_FLAGS "-std=gnu++11 ${CMAKE_CXX_FLAGS}")
ELSE ()
  SET(CMAKE_CXX_STANDARD 14)
ENDIF ()

SET(CMAKE_CXX_FLAGS "-g ${CMAKE_CXX_FLAGS}")

ADD_EXECUTABLE(
  item6 item6.cpp)
