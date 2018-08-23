//
// Created by Matan Silver on 8/22/18.
//

#include "catch.hpp"
#include "ring.hpp"
#include <fstream>
#include <iostream>
#include <vector>

TEST_CASE("Testing ring functionality", "[ring]") {

    samurai::ring<int> r(std::vector<int>{1, 2, 3, 4});
    /*
    r.push(1);
    r.push(2);
    r.push(3);
    r.push(4);
     */

    SECTION("Ring Node Acquisition") {
        REQUIRE(r.get_node()->get_val() == 4);
        REQUIRE(r.proceed() != NULL);
        REQUIRE(r.get_node()->get_val() == 1);
        REQUIRE(r.proceed() != NULL);
        REQUIRE(r.get_node()->get_val() == 2);
        REQUIRE(r.proceed() != NULL);
        REQUIRE(r.get_node()->get_val() == 3);
        REQUIRE(r.proceed() != NULL);
        REQUIRE(r.get_node()->get_val() == 4);
    }
    SECTION("Ring Node Deletion") {
        REQUIRE(r.pop() != NULL);
        REQUIRE(r.get_node()->get_val() == 1);
        REQUIRE(r.proceed() != NULL);
        REQUIRE(r.get_node()->get_val() == 2);
        REQUIRE(r.proceed() != NULL);
        REQUIRE(r.get_node()->get_val() == 3);
        REQUIRE(r.proceed() != NULL);
        REQUIRE(r.get_node()->get_val() == 1);

        REQUIRE(r.pop() != NULL);
        REQUIRE(r.get_node()->get_val() == 2);
        REQUIRE(r.proceed() != NULL);
        REQUIRE(r.get_node()->get_val() == 3);
        REQUIRE(r.proceed() != NULL);
        REQUIRE(r.get_node()->get_val() == 2);

        REQUIRE(r.pop() != NULL);
        REQUIRE(r.get_node()->get_val() == 3);
        REQUIRE(r.proceed() != NULL);
        REQUIRE(r.get_node()->get_val() == 3);

        REQUIRE(r.pop() == NULL); //fine to here
        REQUIRE(r.pop() == NULL);

        REQUIRE(r.proceed() == NULL);
    }
}
