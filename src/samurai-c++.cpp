#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include "binary_stl.hpp"
#include "vector.hpp"
#include "linesegment.hpp"
#include "triangle.hpp"
#include "model.hpp"
#include "marshall.hpp"
#include "config.hpp"
#include "layer.hpp"
#include "args.hpp"

int main(int argc, char **argv) {
    std::string stl_file_name = "/Users/Matan/experimental/samurai-c++/40mmcube.stl";
    //std::string stl_file_name = "/Users/Matan/experimental/samurai-c++/40mmcube.stl";
    auto config_obj = samurai::config("config.json");
    //std::cout << config_obj.get_layer_height();

    if (argc == 2) {
        stl_file_name = argv[1];
    } else if (argc > 2) {
        std::cout << "ERROR: Too many command line arguments" << std::endl;
    }

    auto info = bin_stl::parse_stl(stl_file_name); //stl_data

    auto brep_model = samurai::stl_data_to_model(&info);
#ifdef DEBUG
    brep_model->print();
#endif

    std::vector<samurai::layer> layers = brep_model->slice(0.03);
    try {
        layers = brep_model->slice(0.01);
    } catch (std::exception &ex) {
        std::cout << ex.what();
    }
    auto gcode = samurai::layers_to_gcode(layers);
    std::ofstream gcode_file("output.gcode", std::ofstream::out);
    gcode_file << gcode;
    gcode_file.close();
}
