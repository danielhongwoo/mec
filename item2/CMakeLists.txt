CMAKE_MINIMUM_REQUIRED (VERSION 3.0)
PROJECT (item2)

IF (CMAKE_VERSION VERSION_LESS "3.1")
  SET(CMAKE_CXX_FLAGS "-std=gnu++11 ${CMAKE_CXX_FLAGS}")
ELSE ()
  SET(CMAKE_CXX_STANDARD 14)
ENDIF ()

OPTION(DEBUG "Debug Flag" OFF)
IF (${DEBUG} STREQUAL ON)
  SET(CMAKE_CXX_FLAGS "-g ${CMAKE_CXX_FLAGS}")
ENDIF ()
MESSAGE("Debug is ${DEBUG}")

ADD_EXECUTABLE(
  item2 item2.cpp)
