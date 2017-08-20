#include <unordered_set>
#include <list>
#include <set>
#include <utility>
#include "model.hpp"
#include "linesegment.hpp"
#include "triangle.hpp"
#include "vector.hpp"
namespace samurai {
  model::model() {

  }
  std::list<std::shared_ptr<linesegment>> model::slice_at_z(float z) {
    std::list<std::shared_ptr<linesegment>> linelist;
    return linelist;
  }
  std::list<std::list<std::shared_ptr<linesegment>>> model::slice(float layer_height) {
    std::list<std::list<std::shared_ptr<linesegment>>> linelists;
    for (float z = this->lowest_z(); z < this->highest_z(); z++) {
      linelists.push_back(this->slice_at_z(z));
    }
    return linelists;
  }
  float model::highest_z() {
    float z = 0.0;
    for (auto v : this->vectors) {
      if (v->get_point()[2] > z) z = v->get_point()[2];
    }
    return z;
  }
  float model::lowest_z() {
    float z = 1000.0;
    for (auto v : this->vectors) {
      if (v->get_point()[2] < z) z = v->get_point()[2];
    }
    return z;
  }
  bool model::rotate_x(float angle) {

  }
  bool model::rotate_y(float angle) {

  }
  bool model::rotate_z(float angle) {

  }
  bool model::add_triangle(std::shared_ptr<triangle> tri) {
    this->triangles.push_back(tri);
    return true;
  }
  std::list<std::shared_ptr<triangle>> model::get_triangles() {
    return this->triangles;
  }
  std::set<std::shared_ptr<linesegment>> model::get_linesegments() {
    return this->linesegments;
  }
  std::set<std::shared_ptr<vector>> model::get_vectors() {
    return this->vectors;
  }
  bool model::insert_vector(std::shared_ptr<vector> vec) {
    this->vectors.insert(vec);
    return true;
  }
  std::shared_ptr<vector> model::get_or_create_vector(std::array<float, 3> pnt) {
    // TODO this is SUPER slow
    //for (auto vec : this->get_vectors()) {
    for (auto vec : this->vectors) {
      if (pnt == vec->get_point()) {
        return vec; //true for found
      }
    }
    std::shared_ptr<vector> vec = std::make_shared<vector>(pnt);
    return vec;
  }
  std::shared_ptr<linesegment> model::get_or_create_linesegment(std::set<std::shared_ptr<vector>> vectors) {
    auto lss = this->get_linesegments();
    for (auto ls : lss) {
      if (vectors == ls->get_vectors()) {
        return ls; //true for found
      }
    }
    auto ls = std::make_shared<linesegment>(vectors);
    return ls; //false for not found
  }
  void model::print() {
    for (auto t : this->get_triangles()) {
      std::cout << std::endl << "___TRIANGLE___" << std::endl;
      for (auto v : t->get_vectors()) {
        auto pnt = v->get_point();
        std::cout << "{" << pnt[0] << " " << pnt[1] << " " << pnt[2] << "}" << std::endl;
      }
    }
  }


}