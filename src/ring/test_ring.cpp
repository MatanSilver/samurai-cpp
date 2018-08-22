//
// Created by Matan Silver on 8/22/18.
//

#include "catch.hpp"
#include "ring.hpp"
#include <fstream>
#include <iostream>
#include <vector>

TEST_CASE("Testing ring functionality", "[ring]") {
    samurai::ring<int> r;
    r.add(1);
    r.add(4);
    r.add(3);
    r.add(2);

    SECTION("Ring Node Acquisition") {
        REQUIRE(r.get_node()->get_val() == 1);
        REQUIRE(r.proceed() != NULL);
        REQUIRE(r.get_node()->get_val() == 2);
        REQUIRE(r.proceed() != NULL);
        REQUIRE(r.get_node()->get_val() == 3);
        REQUIRE(r.proceed() != NULL);
        REQUIRE(r.get_node()->get_val() == 4);
        REQUIRE(r.proceed() != NULL);
        REQUIRE(r.get_node()->get_val() == 1);
    }
    SECTION("Ring Node Deletion") {
        REQUIRE(r.remove() != NULL);
        REQUIRE(r.get_node()->get_val() == 2);
        REQUIRE(r.proceed() != NULL);
        REQUIRE(r.get_node()->get_val() == 3);
        REQUIRE(r.proceed() != NULL);
        REQUIRE(r.get_node()->get_val() == 4);
        REQUIRE(r.proceed() != NULL);
        REQUIRE(r.get_node()->get_val() == 2);

        REQUIRE(r.remove() != NULL);
        REQUIRE(r.get_node()->get_val() == 3);
        REQUIRE(r.proceed() != NULL);
        REQUIRE(r.get_node()->get_val() == 4);
        REQUIRE(r.proceed() != NULL);
        REQUIRE(r.get_node()->get_val() == 3);

        REQUIRE(r.remove() != NULL);
        REQUIRE(r.get_node()->get_val() == 4);
        REQUIRE(r.proceed() != NULL);
        REQUIRE(r.get_node()->get_val() == 4);

        REQUIRE(r.remove() == NULL); //fine to here
        REQUIRE(r.remove() == NULL);

        REQUIRE(r.proceed() == NULL);
    }
}
