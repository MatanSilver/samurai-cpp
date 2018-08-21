//
// Created by Matan Silver on 8/21/18.
//

#include "catch.hpp"
#include "vector.hpp"
#include "linesegment.hpp"
#include "triangle.hpp"

TEST_CASE("Testing vector functionality", "[vector]") {
    SECTION("Vector Translation") {
        std::shared_ptr<samurai::vector> vec1 = std::make_shared<samurai::vector>(samurai::vector({1, 1, 1}));
        std::shared_ptr<samurai::vector> vec2 = std::make_shared<samurai::vector>(samurai::vector({2, 1, 1}));
        vec1->translate({1, 0, 0});
        REQUIRE(vec1->equivalent(vec2));
    }
    SECTION("Vector Rotation") {

    }
    SECTION("Line Segment Insertion") {

    }
    SECTION("Triangle Insertion") {

    }
}
