#include "linesegment.hpp"
#include "vector.hpp"
#include <set>
#include <iostream>

namespace samurai {
  vector::vector() {
  }
  vector::vector(std::array<float, 3> pnt) {
    point = std::array<float, 3>(pnt);
  }
  std::array<float, 3> vector::get_point() {
    return point;
  }
  std::set<std::shared_ptr<linesegment>> vector::get_linesegments() {
    return linesegments;
  }
  std::set<std::shared_ptr<triangle>> vector::get_triangles() {
    return triangles;
  }
  bool vector::insert_linesegment(std::shared_ptr<linesegment> ls) {
    linesegments.insert(ls);
    return true;
  }
  bool vector::insert_triangle(std::shared_ptr<triangle> tri) {
    triangles.insert(tri);
    return true;
  }
  void vector::print() {
    std::cout << "{" << point[0] << "," << point[1] << "," << point[2] << "}" << std::endl;
  }
}