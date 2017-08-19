#include <cassert>
#include <iostream>
#include "binary_stl.hpp"
#include "vector.hpp"
#include "linesegment.hpp"
#include "triangle.hpp"
#include "model.hpp"
#include "marshall.hpp"
#include "config.hpp"

int main(int argc, char **argv) {
  std::string stl_file_name = "/Users/Matan/experimental/samurai-c++/CapacitiveMount.stl";
  auto config_obj = samurai::config("config.json");
  //std::cout << config_obj.get_layer_height();

  if (argc == 2) {
    stl_file_name = argv[1];
  } else if (argc > 2) {
    std::cout << "ERROR: Too many command line arguments" << std::endl;
  }

  auto info = bin_stl::parse_stl(stl_file_name); //stl_data
  /*
  std::vector<bin_stl::triangle> triangles = info.triangles;
  std::cout << "STL HEADER = " << info.name << std::endl;
  std::cout << "# triangles = " << triangles.size() << std::endl;
  for (auto t : info.triangles) {
    std::cout << t << std::endl;
  }*/

  auto brep_model = samurai::stl_data_to_model(&info);
  #ifdef DEBUG
  brep_model->print();
  #endif
  auto layers = brep_model->slice(0.01);
}