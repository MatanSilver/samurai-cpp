#include "linesegment.hpp"
#include "vector.hpp"
#include "triangle.hpp"
#include "model.hpp"
#include <iostream>
#include <algorithm>
namespace samurai {
  linesegment::linesegment() {
    //this->vectors.reserve(2);
    //this->triangles.reserve(2);
  }
  linesegment::linesegment(std::set<std::shared_ptr<vector>> vectors) {
    this->vectors = vectors;
    //this->triangles = triangles;
  }
  bool linesegment::add_vector(std::shared_ptr<vector> vec) {
    //check if filled
    if (this->vectors.size() < 2) {
      //check if vector exists in model
      //TODO change to get_or_create_vector()
      auto vecs = this->mdl->get_vectors();
      auto pnt = vec->get_point();
      for (auto v : vecs) {
        if (v->get_point() == pnt) {
          this->vectors.insert(v);
          return true;
        }
      }
    }
    return false;
  }
  std::vector<std::shared_ptr<vector>> linesegment::get_vectors() {
    return this->vectors;
  }
  std::list<std::shared_ptr<triangle>> linesegment::get_triangles() {
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
}