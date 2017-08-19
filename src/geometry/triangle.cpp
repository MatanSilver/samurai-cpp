#include <vector>
#include <set>
#include "triangle.hpp"
#include "vector.hpp"
#include "linesegment.hpp"
namespace samurai {
  triangle::triangle() {

  }
  triangle::triangle(std::set<std::shared_ptr<vector>> vectors, std::set<std::shared_ptr<linesegment>> linesegments, std::array<float, 3> normal) {
    this->vectors = vectors;
    this->linesegments = linesegments;
    this->normal = normal;
  }
  std::set<std::shared_ptr<vector>> triangle::get_vectors() {
    return this->vectors;
  }
  std::set<std::shared_ptr<linesegment>> triangle::get_linesegments() {
    return this->linesegments;
  }
  std::array<float, 3> triangle::get_normal() {
    return this->normal;
  }
  bool triangle::insert_linesegment(std::shared_ptr<linesegment> ls) {
    //ls->insert_triangle(shared_from_this());
    this->linesegments.insert(ls);
    return true;
  }
  bool triangle::insert_vector(std::shared_ptr<vector> vec) {
    this->vectors.insert(vec);
    return true;
  }
}