#pragma once
#include <vector>
#include <list>
#include <array>
#include <unordered_set>
#include <set>
#include <utility>
#include <shared_mutex>
#include <mutex>

namespace samurai {
  class triangle; //forward declarations
  class linesegment;
  class vector;
  class model {
  private:
    std::list<std::shared_ptr<triangle>> triangles;
    std::set<std::shared_ptr<vector>> vectors;
    std::set<std::shared_ptr<linesegment>> linesegments;

  public:
    model();
    #ifdef MULTI_THREAD
    std::shared_timed_mutex mtx;
    #endif
    std::vector<std::shared_ptr<linesegment>> slice_at_z(float z);
    std::vector<std::vector<std::vector<std::shared_ptr<linesegment>>>> slice(float layer_height);
    float highest_z();
    float lowest_z();
    bool rotate(std::array<float, 3>, std::array<float, 3>);
    bool rotate_x(float);
    bool rotate_y(float);
    bool rotate_z(float);
    bool translate(std::array<float, 3>);
    bool add_triangle(std::shared_ptr<triangle>);
    std::list<std::shared_ptr<triangle>> get_triangles();
    std::set<std::shared_ptr<linesegment>> get_linesegments();
    std::set<std::shared_ptr<vector>> get_vectors();
    std::shared_ptr<vector> get_or_create_vector(std::array<float, 3>);
    std::shared_ptr<linesegment> get_or_create_linesegment(std::vector<std::shared_ptr<vector>>);
    bool insert_vector(std::shared_ptr<vector>);
    void print();
  };
  bool is_ordered(std::vector<std::shared_ptr<linesegment>> *loop);
  bool are_joined(std::shared_ptr<linesegment> ls1, std::shared_ptr<linesegment> ls2);
  bool is_closed(std::vector<std::shared_ptr<linesegment>> *ll);
  bool vector_approx(std::shared_ptr<vector> vec1, std::shared_ptr<vector>);
  void flip(std::vector<std::shared_ptr<linesegment>> *ll);
  std::vector<std::vector<std::shared_ptr<linesegment>>> linelist_to_openloops(std::vector<std::shared_ptr<linesegment>>);
  std::vector<std::vector<std::shared_ptr<linesegment>>> closeloops(std::vector<std::vector<std::shared_ptr<linesegment>>>);
  bool splice_in_list(std::vector<std::shared_ptr<linesegment>> &ll1, std::vector<std::shared_ptr<linesegment>> &ll2);
}
