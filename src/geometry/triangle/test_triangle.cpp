//
// Created by Matan Silver on 8/21/18.
//

#include "catch.hpp"
#include "vector.hpp"
#include "triangle.hpp"
#include "linesegment.hpp"
#include <fstream>
#include <array>
#include <iostream>

TEST_CASE("Testing triangle functionality", "[triangle]") {
    SECTION("Triangle Translation") {
        auto vec1 = std::make_shared<samurai::vector>(samurai::vector({0, 0, 0}));
        auto vec2 = std::make_shared<samurai::vector>(samurai::vector({1, 0, 0}));
        auto vec3 = std::make_shared<samurai::vector>(samurai::vector({0.5, 0, 2}));

        auto vec4 = std::make_shared<samurai::vector>(samurai::vector({1, 1, 1}));
        auto vec5 = std::make_shared<samurai::vector>(samurai::vector({2, 1, 1}));
        auto vec6 = std::make_shared<samurai::vector>(samurai::vector({1.5, 1, 3}));

        //triangle should pass through z=0, z=0.5, but not through z>=1
        std::array<std::shared_ptr<samurai::vector>, 2> ar1 = {vec1, vec2};
        std::array<std::shared_ptr<samurai::vector>, 2> ar2 = {vec2, vec3};
        std::array<std::shared_ptr<samurai::vector>, 2> ar3 = {vec3, vec1};
        auto ls1 = std::make_shared<samurai::linesegment>(ar1);
        auto ls2 = std::make_shared<samurai::linesegment>(ar2);
        auto ls3 = std::make_shared<samurai::linesegment>(ar3);

        std::vector<std::shared_ptr<samurai::vector>> ar4 = {vec1, vec2, vec3};
        std::vector<std::shared_ptr<samurai::linesegment>> ar5 = {ls1, ls2, ls3};
        std::array<float, 3> ar6 = {0, 0, 0};

        auto tri = std::make_shared<samurai::triangle>(ar4, ar5, ar6);

        tri->translate({1, 1, 1});
        REQUIRE(tri->contains_vector(vec4));
        REQUIRE(tri->contains_vector(vec5));
        REQUIRE(tri->contains_vector(vec6));
    }
    SECTION("Triangle Rotation") {
        auto vec1 = std::make_shared<samurai::vector>(samurai::vector({0, 0, 0}));
        auto vec2 = std::make_shared<samurai::vector>(samurai::vector({1, 0, 0}));
        auto vec3 = std::make_shared<samurai::vector>(samurai::vector({0.5, 0, 2}));

        auto vec4 = std::make_shared<samurai::vector>(samurai::vector({0, 0, 0}));
        auto vec5 = std::make_shared<samurai::vector>(samurai::vector({1, 0, 0}));
        auto vec6 = std::make_shared<samurai::vector>(samurai::vector({0.5, -2, 0}));

        //triangle should pass through z=0, z=0.5, but not through z>=1
        std::array<std::shared_ptr<samurai::vector>, 2> ar1 = {vec1, vec2};
        std::array<std::shared_ptr<samurai::vector>, 2> ar2 = {vec2, vec3};
        std::array<std::shared_ptr<samurai::vector>, 2> ar3 = {vec3, vec1};
        auto ls1 = std::make_shared<samurai::linesegment>(ar1);
        auto ls2 = std::make_shared<samurai::linesegment>(ar2);
        auto ls3 = std::make_shared<samurai::linesegment>(ar3);

        std::vector<std::shared_ptr<samurai::vector>> ar4 = {vec1, vec2, vec3};
        std::vector<std::shared_ptr<samurai::linesegment>> ar5 = {ls1, ls2, ls3};
        std::array<float, 3> ar6 = {0, 0, 0};

        auto tri = std::make_shared<samurai::triangle>(ar4, ar5, ar6);

        tri->rotate(90.0, {1, 0, 0});
        REQUIRE(tri->contains_vector(vec4));
        REQUIRE(tri->contains_vector(vec5));
        REQUIRE(tri->contains_vector(vec6));
    }
    SECTION("Linesegment Insertion") {
        samurai::triangle tri;

        auto vec1 = std::make_shared<samurai::vector>(samurai::vector({0, 0, 0}));
        auto vec2 = std::make_shared<samurai::vector>(samurai::vector({1, 0, 0}));
        auto vec3 = std::make_shared<samurai::vector>(samurai::vector({0.5, 0, 2}));

        //triangle should pass through z=0, z=0.5, but not through z>=1
        std::array<std::shared_ptr<samurai::vector>, 2> ar1 = {vec1, vec2};
        std::array<std::shared_ptr<samurai::vector>, 2> ar2 = {vec2, vec3};
        std::array<std::shared_ptr<samurai::vector>, 2> ar3 = {vec3, vec1};
        auto ls1 = std::make_shared<samurai::linesegment>(ar1);
        auto ls2 = std::make_shared<samurai::linesegment>(ar2);
        auto ls3 = std::make_shared<samurai::linesegment>(ar3);

        REQUIRE(tri.insert_linesegment(ls1));
        REQUIRE(tri.insert_linesegment(ls2));
        REQUIRE(tri.insert_linesegment(ls3));
        REQUIRE(!tri.insert_linesegment(ls3));

    }
    SECTION("Vector Insertion") {
        samurai::triangle tri;
        auto vec1 = std::make_shared<samurai::vector>(samurai::vector({0, 0, 0}));
        auto vec2 = std::make_shared<samurai::vector>(samurai::vector({1, 0, 0}));
        auto vec3 = std::make_shared<samurai::vector>(samurai::vector({0.5, 0, 2}));
        REQUIRE(tri.insert_vector(vec1));
        REQUIRE(tri.insert_vector(vec2));
        REQUIRE(tri.insert_vector(vec3));
        REQUIRE(!tri.insert_vector(vec3));
    }
    SECTION("Plane Intersection") {

    }
    SECTION("Z Intersection") {
        auto vec1 = std::make_shared<samurai::vector>(samurai::vector({0, 0, 0}));
        auto vec2 = std::make_shared<samurai::vector>(samurai::vector({1, 0, 0}));
        auto vec3 = std::make_shared<samurai::vector>(samurai::vector({0.5, 0, 2}));

        //triangle should pass through z=0, z=0.5, but not through z>=1
        std::array<std::shared_ptr<samurai::vector>, 2> ar1 = {vec1, vec2};
        std::array<std::shared_ptr<samurai::vector>, 2> ar2 = {vec2, vec3};
        std::array<std::shared_ptr<samurai::vector>, 2> ar3 = {vec3, vec1};
        auto ls1 = std::make_shared<samurai::linesegment>(ar1);
        auto ls2 = std::make_shared<samurai::linesegment>(ar2);
        auto ls3 = std::make_shared<samurai::linesegment>(ar3);

        std::vector<std::shared_ptr<samurai::vector>> ar4 = {vec1, vec2, vec3};
        std::vector<std::shared_ptr<samurai::linesegment>> ar5 = {ls1, ls2, ls3};
        std::array<float, 3> ar6 = {0, 0, 0};

        auto tri = std::make_shared<samurai::triangle>(ar4, ar5, ar6);

        REQUIRE(tri->intersects_z(0.0));
        REQUIRE(tri->intersects_z(0.5));
        REQUIRE(!tri->intersects_z(2.0));
        REQUIRE(!tri->intersects_z(3.0));
        REQUIRE(!tri->intersects_z(-1.0));
    }
    SECTION("Container") {

    }
}