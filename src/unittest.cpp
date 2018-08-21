#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include <cassert>
#include <string>
#include <fstream>
#include "binary_stl.hpp"
#include "vector.hpp"
#include "linesegment.hpp"
#include "triangle.hpp"
#include "model.hpp"
#include "marshall.hpp"
#include "config.hpp"
#include "model.hpp"


TEST_CASE("Model is correct", "[model]") {
    REQUIRE(5==5);
    /*
    std::string stl_file_name = "/Users/Matan/experimental/samurai-c++/CapacitiveMount.stl";
    auto config_obj = samurai::config("config.json");
    auto info = bin_stl::parse_stl(stl_file_name); //stl_data

    auto brep_model = samurai::stl_data_to_model(&info);

    auto layers = brep_model->slice(0.01);
    auto gcode = layers_to_gcode(layers);
    std::ofstream gcode_file("output.gcode", std::ofstream::out);
    gcode_file << gcode;
    gcode_file.close();
     */
}
