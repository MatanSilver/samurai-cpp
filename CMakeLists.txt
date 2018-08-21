cmake_minimum_required(VERSION 3.12)
project(samurai_c++)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        src/config/config.cpp
        src/config/config.hpp
        src/config/json.hpp
        src/geometry/layer/layer.cpp
        src/geometry/layer/layer.hpp
        src/geometry/layer/loop.hpp
        src/geometry/linesegment/linesegment.cpp
        src/geometry/linesegment/linesegment.hpp
        src/geometry/model/model.cpp
        src/geometry/model/model.hpp
        src/geometry/triangle/triangle.cpp
        src/geometry/triangle/triangle.hpp
        src/geometry/vector/vector.cpp
        src/geometry/vector/vector.hpp
        src/geometry/artifact.hpp
        src/parser/binary_stl.cpp
        src/parser/binary_stl.hpp
        src/ring/ring.hpp
        src/catch.hpp
        src/marshall.cpp
        src/marshall.hpp
        src/samurai-c++.cpp
        src/utils.hpp)
set(UNIT_SOURCE_FILES
        src/config/config.cpp
        src/config/config.hpp
        src/config/json.hpp
        src/geometry/layer/layer.cpp
        src/geometry/layer/layer.hpp
        src/geometry/layer/loop.hpp
        src/geometry/linesegment/linesegment.cpp
        src/geometry/linesegment/linesegment.hpp
        src/geometry/model/model.cpp
        src/geometry/model/model.hpp
        src/geometry/triangle/triangle.cpp
        src/geometry/triangle/triangle.hpp
        src/geometry/vector/vector.cpp
        src/geometry/vector/vector.hpp
        src/geometry/artifact.hpp
        src/parser/binary_stl.cpp
        src/parser/binary_stl.hpp
        src/ring/ring.hpp
        src/catch.hpp
        src/marshall.cpp
        src/marshall.hpp
        src/unittest.cpp
        src/utils.hpp)
set(INCLUDE_DIRS
        src
        src/ring
        src/parser
        src/config
        src/geometry
        src/geometry/layer
        src/geometry/linesegment
        src/geometry/model
        src/geometry/triangle
        src/geometry/vector
        )
include_directories(${INCLUDE_DIRS})

add_executable(samurai_c++ ${SOURCE_FILES})
add_executable(unittest ${UNIT_SOURCE_FILES})