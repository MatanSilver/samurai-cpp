#include "linesegment.hpp"
#include "vector.hpp"
#include <set>

namespace samurai {
  vector::vector() {
  }
  vector::vector(std::array<float, 3> point) {
    this->point = point;
  }
  std::array<float, 3> vector::get_point() {
    return this->point;
  }
  std::set<std::shared_ptr<linesegment>> vector::get_linesegments() {
    return this->linesegments;
  }
  std::set<std::shared_ptr<triangle>> vector::get_triangles() {
    return this->triangles;
  }
  bool vector::insert_linesegment(std::shared_ptr<linesegment> ls) {
    this->linesegments.insert(ls);
    return true;
  }
  bool vector::insert_triangle(std::shared_ptr<triangle> tri) {
    this->triangles.insert(tri);
    return true;
  }
}