#include <vector>
#include <set>
#include <array>
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
  bool triangle::intersects_z(float z) {
    std::vector<std::shared_ptr<vector>> vector_array(vectors.size());
    float z1 = vector_array[0]->get_point()[2];
    float z2 = vector_array[1]->get_point()[2];
    float z3 = vector_array[2]->get_point()[2];
    if (z1 > z && z2 > z && z3 > z) {
      return false;
    } else if (z1 < z && z2 < z && z3 < z) {
      return false;
    } else if (z1 == z && z2 == z && z3 == z) {
      return false;
    } else if ((z1 == z && z2 > z && z3 > z) ||
    (z1 == z && z2 < z && z3 < z) ||
    (z2 == z && z1 > z && z3 > z) ||
    (z2 == z && z1 < z && z3 < z) ||
    (z3 == z && z1 > z && z3 > z) ||
    (z3 == z && z1 < z && z3 < z)) {
      return false;
    }
    return true;
  }
}