//
// Created by Matan Silver on 8/21/18.
//

#include "catch2/catch.hpp"
#include "vector.hpp"
#include "triangle.hpp"
#include "linesegment.hpp"

TEST_CASE("Testing linesegment functionality", "[linesegment]") {
    auto vec1 = std::make_shared<samurai::vector>(samurai::vector({0, 0, 0}));
    auto vec2 = std::make_shared<samurai::vector>(samurai::vector({1, 0, 1}));
    std::array<std::shared_ptr<samurai::vector>, 2> vecs = {vec1, vec2};
    auto ls = std::make_shared<samurai::linesegment>(samurai::linesegment(vecs));

    SECTION("Linesegment Flipping") {
        ls->flip();
        REQUIRE(ls->is_flipped());
        REQUIRE(ls->get_vectors()[0] == vec2);
        REQUIRE(ls->get_vectors()[1] == vec1);
    }
    SECTION("Linesegment Rotation") {
        auto vec3 = std::make_shared<samurai::vector>(samurai::vector({0, 0, 0}));
        auto vec4 = std::make_shared<samurai::vector>(samurai::vector({1, -1, 0}));
        ls->rotate(90, {1, 0, 0});
        REQUIRE(ls->contains_vector(vec3));
        REQUIRE(ls->contains_vector(vec4));

    }
    SECTION("Linesegment Translation") {
        auto vec3 = std::make_shared<samurai::vector>(samurai::vector({1, 1, 1}));
        auto vec4 = std::make_shared<samurai::vector>(samurai::vector({2, 1, 2}));
        ls->translate({1, 1, 1});
        REQUIRE(ls->contains_vector(vec3));
        REQUIRE(ls->contains_vector(vec4));
    }
    SECTION("Linesegment Equality/Equivalence") {
        auto vec4 = std::make_shared<samurai::vector>(samurai::vector({0, 0, 0.00000001}));
        auto vec3 = std::make_shared<samurai::vector>(samurai::vector({1, 0, 1.00000001}));
        std::array<std::shared_ptr<samurai::vector>, 2> vecs = {vec3, vec4};
        auto ls2 = std::make_shared<samurai::linesegment>(samurai::linesegment(vecs));
        REQUIRE(!ls->approx_equal(ls2));
        REQUIRE(ls->approx_equivalent(ls2));
    }
}