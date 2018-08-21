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
    std::vector<std::shared_ptr<vector>> vector_array(vectors.begin(), vectors.end());
    //std::copy(vectors.begin(), vectors.end(), std::back_inserter(vector_array));
    float z1 = vector_array[0]->get_point()[2];
    float z2 = vector_array[1]->get_point()[2];
    float z3 = vector_array[2]->get_point()[2];
    if (z1 > z && z2 > z && z3 > z) { //all above
      return false;
    } else if (z1 < z && z2 < z && z3 < z) { //all below
      return false;
    } else if (z1 == z && z2 == z && z3 == z) { //all on
      return false;
    } else if ((z1 == z && z2 != z && z3 != z) ||
    (z2 == z && z1 != z && z3 != z) ||
    (z3 == z && z1 != z && z2 != z)) {
      return false;
    }
    return true;
  }
  std::vector<std::shared_ptr<vector>> triangle::intersect_plane(float z) {
    //std::cout << "layer height: " << z << std::endl;
    std::vector<std::shared_ptr<vector>> vector_array(vectors.begin(), vectors.end());
    /*auto demisects = [](float z, std::shared_ptr<vector> vec1, std::shared_ptr<vector> vec2, std::shared_ptr<vector> vec3) {
      if (vec1->get_point()[2] == z) {
        float p1 = vec2->get_point()[2]-z;
        float p2 = vec3->get_point()[2]-z;
        if ((p1 > 0 && p2 > 0) || (p1 < 0 && p2 < 0)) { //if same sign TODO duplicate elsewhere
          return true;
        }
      }
      return false;
    };*/
    //std::copy(vectors.begin(), vectors.end(), std::back_inserter(vector_array));
    if (vector_array[0]->get_point()[2] == z && vector_array[1]->get_point()[2] == z) {
      // if vec 0 and vec 1 are both on plane
      return {vector_array[0], vector_array[1]};
    } else if (vector_array[1]->get_point()[2] == z && vector_array[2]->get_point()[2] == z) {
      // if vec 1 and vec 2 are both on plane
      return {vector_array[1], vector_array[2]};
    } else if (vector_array[0]->get_point()[2] == z && vector_array[2]->get_point()[2] == z) {
      // if vec 0 and vec 2 are both on plane
      return {vector_array[0], vector_array[2]};
    } else { // if only one or none are on the plane
      std::shared_ptr<vector> va, vb, origin;
      if ((vector_array[0]->get_point()[2] <= z && vector_array[1]->get_point()[2] <= z && vector_array[2]->get_point()[2] > z) ||
          (vector_array[0]->get_point()[2] >= z && vector_array[1]->get_point()[2] >= z && vector_array[2]->get_point()[2] < z)
          ) {
        // vec 0 is low, vec 1 is low, and vec 2 is high OR
        // vec 0 is high, vec 1 is high, and vec 2 is low
        va = vector_array[0];
        vb = vector_array[1];
        origin = vector_array[2];
      } else if ((vector_array[1]->get_point()[2] <= z && vector_array[2]->get_point()[2] <= z && vector_array[0]->get_point()[2] > z) ||
                 (vector_array[1]->get_point()[2] >= z && vector_array[2]->get_point()[2] >= z && vector_array[0]->get_point()[2] < z)
                 ) {
        // vec 0 is high, vec 1 is low, and vec 2 is low OR
        // vec 0 is low, vec 1 is high, and vec 2 is high
        va = vector_array[1];
        vb = vector_array[2];
        origin = vector_array[0];
      } else if ((vector_array[0]->get_point()[2] <= z && vector_array[2]->get_point()[2] <= z && vector_array[1]->get_point()[2] > z) ||
                 (vector_array[0]->get_point()[2] >= z && vector_array[2]->get_point()[2] >= z && vector_array[1]->get_point()[2] < z)
                 ) {
        // vec 0 is low, vec 1 is high, and vec 2 is low OR
        // vec 0 is high, vec 1 is low, and vec 2 is high
        va = vector_array[0];
        vb = vector_array[2];
        origin = vector_array[1];
      }
      else {
        //std::cout << "didn't satisfy\n";
        vector_array[0]->print();
        vector_array[1]->print();
        vector_array[2]->print();

      } // TODO add case where one is on the plane and the other two are alternating
      //TODO fails here
      float t1 = (z - va->get_point()[2]) / (origin->get_point()[2] - va->get_point()[2]);
      float t2 = (z - vb->get_point()[2]) / (origin->get_point()[2] - vb->get_point()[2]);
      float x1 = va->get_point()[0] + t1*(origin->get_point()[0]-va->get_point()[0]);
      float x2 = vb->get_point()[0] + t2*(origin->get_point()[0]-vb->get_point()[0]);
      float y1 = va->get_point()[1] + t1*(origin->get_point()[1]-va->get_point()[1]);
      float y2 = vb->get_point()[1] + t2*(origin->get_point()[1]-vb->get_point()[1]);
      std::array<float, 3> a1({x1, y1, z});
      std::array<float, 3> a2({x2, y2, z});
      std::shared_ptr<vector> v1 = std::make_shared<vector>(a1);
      std::shared_ptr<vector> v2 = std::make_shared<vector>(a2);
      //v1->insert_triangle(shared_from_this());
      //v2->insert_triangle(shared_from_this());
      return {v1, v2};
    }

  }
}