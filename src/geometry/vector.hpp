#pragma once
#include <array>
#include <vector>
#include <set>


namespace samurai {
  class linesegment;
  class triangle;
  class model;
  class vector : public std::enable_shared_from_this<vector>{
  private:
    std::array<float, 3> point;
    std::set<std::shared_ptr<linesegment>> linesegments;
    std::set<std::shared_ptr<triangle>> triangles;
    std::shared_ptr<model> mdl;
  public:
    vector();
    vector(std::array<float, 3>);
    std::array<float, 3> get_point();
    std::set<std::shared_ptr<linesegment>> get_linesegments();
    std::set<std::shared_ptr<triangle>> get_triangles();
    bool insert_linesegment(std::shared_ptr<linesegment>);
    bool insert_triangle(std::shared_ptr<triangle>);
  };
}