//
// Created by Matan Silver on 8/21/18.
//

#include "catch.hpp"
#include "vector.hpp"
#include "triangle.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <streambuf>

TEST_CASE("Testing triangle functionality", "[triangle]") {
    SECTION("Triangle Translation") {
        auto vec1 = std::make_shared<samurai::vector>(samurai::vector({1, 1, 1}));
        auto vec2 = std::make_shared<samurai::vector>(samurai::vector({2, 1, 1}));
        vec1->translate({1, 0, 0});
        REQUIRE(vec1->equal(vec2));
    }
    SECTION("Triangle Rotation") {
        auto vec1 = std::make_shared<samurai::vector>(samurai::vector({0, 1, 0}));
        auto vec2 = std::make_shared<samurai::vector>(samurai::vector({0, 0, 1}));
        vec1->rotate(90, {1, 0, 0});
        REQUIRE(vec1->approx_equal(vec2));
    }
    SECTION("Linesegment Insertion") {

    }
    SECTION("Vector Insertion") {

    }
    SECTION("Plane Intersection") {

    }
    SECTION("Z Intersection") {

    }
    SECTION("Container") {

    }
}