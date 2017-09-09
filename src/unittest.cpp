#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <cassert>
#include <iostream>
#include "binary_stl.hpp"
#include "vector.hpp"
#include "linesegment.hpp"
#include "triangle.hpp"
#include "model.hpp"
#include "marshall.hpp"
#include "config.hpp"

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

TEST_CASE( "Model is correct", "[model]" ) {
  std::string stl_file_name = "/Users/Matan/experimental/samurai-c++/CapacitiveMount.stl";
  auto config_obj = samurai::config("config.json");
  auto info = bin_stl::parse_stl(stl_file_name); //stl_data

  auto brep_model = samurai::stl_data_to_model(&info);

  auto layers = brep_model->slice(0.01);
}
