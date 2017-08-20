#pragma once
#include <vector>
#include <iostream>
#include <set>
#include <array>

namespace samurai {
  class vector; //forward declarations (notice no include)
  class triangle;
  class model;
  struct vector_compare;
  class linesegment : public std::enable_shared_from_this<linesegment>{
  private:
    std::set<std::shared_ptr<vector>> vectors;
    std::set<std::shared_ptr<triangle>> triangles;
    std::shared_ptr<model> mdl;
  public:
    linesegment();
    linesegment(std::set<std::shared_ptr<vector>>);
    bool add_vector(std::shared_ptr<vector>);
    std::set<std::shared_ptr<vector>> get_vectors();
    std::set<std::shared_ptr<triangle>> get_triangles();
    bool insert_triangle(std::shared_ptr<triangle>);
  };
  class layersegment {
  private:
  std::array<std::shared_ptr<vector>, 2> vectors;
  public:
  layersegment(std::set<std::shared_ptr<vector>>);
  std::array<std::shared_ptr<vector>, 2> get_vectors();
};
}