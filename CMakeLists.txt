cmake_minimum_required(VERSION 3.8.2)
project(samurai_c++)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        src/config/config.cpp
        src/config/config.hpp
        src/config/json.hpp
        src/geometry/layer/layer.cpp
        src/geometry/layer/layer.hpp
        src/geometry/loop/loop.hpp
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
        src/marshall.cpp
        src/marshall.hpp
        src/samurai-c++.cpp
        src/utils.hpp
        src/geometry/loop/loop.cpp)
set(UNIT_SOURCE_FILES
        src/config/config.cpp
        src/config/config.hpp
        src/config/json.hpp
        src/geometry/layer/layer.cpp
        src/geometry/layer/layer.hpp
        src/geometry/loop/loop.hpp
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
        src/marshall.cpp
        src/marshall.hpp
        src/unittest.cpp
        src/utils.hpp
        src/geometry/linesegment/test_linesegment.cpp
        src/geometry/model/test_model.cpp
        src/geometry/triangle/test_triangle.cpp
        src/geometry/vector/test_vector.cpp
        src/ring/test_ring.cpp
        src/geometry/loop/test_loop.cpp
        src/geometry/loop/loop.cpp)
set(BENCH_SOURCE_FILES
        src/benchmark.cpp
        src/config/config.cpp
        src/config/config.hpp
        src/config/json.hpp
        src/geometry/layer/layer.cpp
        src/geometry/layer/layer.hpp
        src/geometry/loop/loop.hpp
        src/geometry/loop/loop.cpp
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
        src/marshall.cpp
        src/marshall.hpp
        src/utils.hpp
        src/geometry/linesegment/bench_linesegment.cpp
        src/geometry/model/bench_model.cpp
        src/geometry/triangle/bench_triangle.cpp
        src/geometry/vector/bench_vector.cpp
        src/geometry/loop/bench_loop.cpp
        src/ring/bench_ring.cpp)
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
        src/geometry/loop
        )

#add_subdirectory(src/Celero)
add_subdirectory(src/Catch2)
add_subdirectory(src/args)


add_executable(samurai_c++ ${SOURCE_FILES})
target_include_directories(samurai_c++ PRIVATE ${INCLUDE_DIRS})
add_dependencies(samurai_c++ args)
target_link_libraries(samurai_c++ args)

add_executable(unittest ${UNIT_SOURCE_FILES})
target_include_directories(unittest PRIVATE ${INCLUDE_DIRS})
add_dependencies(unittest Catch2)
target_link_libraries(unittest Catch2)

#add_executable(benchmark ${BENCH_SOURCE_FILES})
#target_include_directories(benchmark PRIVATE ${INCLUDE_DIRS})
#add_dependencies(benchmark celero)
#target_link_libraries(benchmark celero)