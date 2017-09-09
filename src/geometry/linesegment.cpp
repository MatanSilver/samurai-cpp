#include "linesegment.hpp"
#include "vector.hpp"
#include "triangle.hpp"
#include "model.hpp"
#include <iostream>
#include <algorithm>
namespace samurai {
  linesegment::linesegment(std::vector<std::shared_ptr<vector>> vectors) {
    this->vectors = vectors;
    //this->triangles = triangles;
  }
  std::vector<std::shared_ptr<vector>> linesegment::get_vectors() {
    return this->vectors;
  }
  std::set<std::shared_ptr<triangle>> linesegment::get_triangles() {
    return this->triangles;
  }
  bool linesegment::insert_triangle(std::shared_ptr<triangle>tri) {
    for (auto t : this->triangles) { //check if triangle exists
      if (t == tri) {
        return false;
      }
    }
    this->triangles.insert(tri);
    return true;
  }
  bool linesegment::is_flipped() {
    return this->flipped;
  }
  void linesegment::flip() {
    std::reverse(this->vectors.begin(), this->vectors.end());
    return;
  }
}
