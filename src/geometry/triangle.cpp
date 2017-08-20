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
  std::set<std::shared_ptr<vector>> triangle::intersect_plane(float z) {
    if (this->vectors[0].get_point()[2] == z && this->vectors[1].get_point()[2] == z) {
      return {this->vectors[0], this->vectors[1]};
    } else if (this->vectors[1].get_point()[2] == z && this->vectors[2].get_point()[2] == z) {
      return {this->vectors[1], this->vectors[2]};
    } else if (this->vectors[0].get_point()[2] == z && this->vectors[2].get_point()[2] == z) {
      return {this->vectors[0], this->vectors[2]};
    } else {
      std::shared_ptr<vector> va, vb, origin;
      if (this->vectors[0].get_point()[2] <= z && this->vectors[1].get_point()[2] <= z && this->vectors[2].get_point()[2] > z) {
        va = this->vectors[0];
        vb = this->vectors[1];
        origin = this->vectors[2];
      } else if (this->vectors[1].get_point()[2] <= z && this->vectors[2].get_point()[2] <= z && this->vectors[0].get_point()[2] > z) {
        va = this->vectors[1];
        vb = this->vectors[2];
        origin = this->vectors[0];
      } else if (this->vectors[0].get_point()[2] <= z && this->vectors[2].get_point()[2] <= z && this->vectors[1].get_point()[2] > z) {
        va = this->vectors[0];
        vb = this->vectors[2];
        origin = this->vectors[1];
      }
      float t1 = (z - va.get_point()[2]) / (origin.get_point()[2] - va.get_point()[2])
      float t2 = (z - vb.get_point()[2]) / (origin.get_point()[2] - vb.get_point()[2])
      float x1 = va.get_point()[0] + t1*(origin.get_point()[0]-va.get_point()[0])
      float x2 = vb.get_point()[0] + t2*(origin.get_point()[0]-vb.get_point()[0])
      float = va.get_point()[1] + t1*(origin.get_point()[1]-va.get_point()[1])
      float = vb.get_point()[1] + t2*(origin.get_point()[1]-vb.get_point()[1])
      std::array<float, 3> a1(x1, y1, z);
      std::array<float, 3> a2(x2, y2, z);
      std::shared_ptr<vector> v1 = std::make_shared<vector>(a1);
      std::shared_ptr<vector> v2 = std::make_shared<vector>(a2);
      return {v1, v2};
    }

  }
}