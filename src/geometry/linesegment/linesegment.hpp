#pragma once
#include <vector>
#include <iostream>
#include <set>
#include <array>
#include <tuple>

namespace samurai {
  class vector; //forward declarations (notice no include)
  class triangle;
  class model;
  struct vector_compare;
  class linesegment : public std::enable_shared_from_this<linesegment>{
  private:
    std::vector<std::shared_ptr<vector>> vectors;
    std::set<std::shared_ptr<triangle>> triangles;
    std::shared_ptr<model> mdl;
    bool flipped;
  public:
    linesegment(std::vector<std::shared_ptr<vector>>);
    std::vector<std::shared_ptr<vector>> get_vectors();
    std::set<std::shared_ptr<triangle>> get_triangles();
    bool insert_triangle(std::shared_ptr<triangle>);
    bool is_flipped();
    //adjacent, after, flip segment
    std::tuple<bool, bool, bool> adjacent(std::shared_ptr<linesegment> seg);
    void flip();
  };
}
