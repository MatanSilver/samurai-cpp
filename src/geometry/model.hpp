#pragma once
#include <vector>
#include <list>
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
    std::list<std::shared_ptr<linesegment>> slice_at_z(float z);
    std::list<std::list<std::shared_ptr<linesegment>>> slice(float layer_height);
    float highest_z();
    float lowest_z();
    bool add_triangle(std::shared_ptr<triangle>);
    std::list<std::shared_ptr<triangle>> get_triangles();
    std::set<std::shared_ptr<linesegment>> get_linesegments();
    std::set<std::shared_ptr<vector>> get_vectors();
    std::shared_ptr<vector> get_or_create_vector(std::array<float, 3>);
    //std::pair<bool, std::shared_ptr<vector>> get_or_create_vector(std::array<float, 3>);
    //std::shared_ptr<triangle> get_or_create_triangle(std::set<std::shared_ptr<vector>>, std::set<std::shared_ptr<linesegment>>, std::array<float, 3>);
    std::shared_ptr<linesegment> get_or_create_linesegment(std::set<std::shared_ptr<vector>>);
    //std::pair<bool, std::shared_ptr<linesegment>> get_or_create_linesegment(std::set<std::shared_ptr<vector>>);
    bool insert_vector(std::shared_ptr<vector>);
    void print();
  };
}