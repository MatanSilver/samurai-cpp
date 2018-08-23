#include <vector>
#include <set>
#include <array>
#include <cmath>
#include "triangle.hpp"
#include "vector.hpp"
#include "linesegment.hpp"
#include <iostream>
#include "utils.hpp"

namespace samurai {
    triangle::triangle() {

    }

    triangle::triangle(std::vector<std::shared_ptr<vector>> vectors,
                       std::vector<std::shared_ptr<linesegment>> linesegments,
                       std::array<float, 3> normal) {
        this->vectors = vectors;
        this->linesegments = linesegments;
        this->normal = normal;
    }

    std::vector<std::shared_ptr<vector>> triangle::get_vectors() {
        return vectors;
    }

    std::vector<std::shared_ptr<linesegment>> triangle::get_linesegments() {
        return linesegments;
    }

    std::array<float, 3> triangle::get_normal() {
        return normal;
    }

    bool triangle::insert_linesegment(std::shared_ptr<linesegment> ls) {
        if (!this->contains_linesegment(ls)) {
            linesegments.push_back(ls);
            return true;
        }
        return false;
    }

    bool triangle::insert_vector(std::shared_ptr<vector> vec) {
        if (!this->contains_vector(vec)) {
            this->vectors.push_back(vec);
            return true;
        }
        return false;
    }

    bool triangle::contains_linesegment(std::shared_ptr<linesegment> ls) {
        for (auto l : linesegments) {
            if (ls->approx_equivalent(l)) {
                return true;
            }
        }
        return false;
    }

    bool triangle::contains_vector(std::shared_ptr<vector> vec) {
        for (auto v : vectors) {
            if (vec->approx_equal(v)) {
                return true;
            }
        }
        return false;
    }

    void triangle::rotate(float angle, std::array<float, 3> axis) {
        for (auto v : vectors) {
            v->rotate(angle, axis);
        }
    }

    void triangle::translate(std::array<float, 3> offset) {
        for (auto v : vectors) {
            v->translate(offset);
        }
    }

    bool triangle::intersects_z(float z) {
        float z1 = vectors[0]->get_point()[2];
        float z2 = vectors[1]->get_point()[2];
        float z3 = vectors[2]->get_point()[2];

        int count_above = 0, count_below = 0, count_on = 0;

        count_on += (abs(z1 - z) <= EPSILON); //fuzzing
        count_on += (abs(z2 - z) <= EPSILON);
        count_on += (abs(z3 - z) <= EPSILON);

        count_above += (z1 - z > EPSILON);
        count_above += (z2 - z > EPSILON);
        count_above += (z3 - z > EPSILON);

        count_below += (z - z1 > EPSILON);
        count_below += (z - z2 > EPSILON);
        count_below += (z - z3 > EPSILON);

        if ((count_on == 2) ||
            (count_above == 2 && count_below == 1) ||
            (count_above == 1 && count_below == 2)) {
            return true;
        }
        return false;
    }

    std::array<std::shared_ptr<vector>, 2> triangle::intersect_z(float z) {
        throw NotImplementedException();
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
        if (vectors[0]->get_point()[2] == z && vectors[1]->get_point()[2] == z) {
            // if vec 0 and vec 1 are both on plane
            return {vectors[0], vectors[1]};
        } else if (vectors[1]->get_point()[2] == z && vectors[2]->get_point()[2] == z) {
            // if vec 1 and vec 2 are both on plane
            return {vectors[1], vectors[2]};
        } else if (vectors[0]->get_point()[2] == z && vectors[2]->get_point()[2] == z) {
            // if vec 0 and vec 2 are both on plane
            return {vectors[0], vectors[2]};
        } else { // if only one or none are on the plane
            std::shared_ptr<vector> va, vb, origin;
            if ((vectors[0]->get_point()[2] <= z && vectors[1]->get_point()[2] <= z &&
                    vectors[2]->get_point()[2] > z) ||
                (vectors[0]->get_point()[2] >= z && vectors[1]->get_point()[2] >= z &&
                        vectors[2]->get_point()[2] < z)
                    ) {
                // vec 0 is low, vec 1 is low, and vec 2 is high OR
                // vec 0 is high, vec 1 is high, and vec 2 is low
                va = vectors[0];
                vb = vectors[1];
                origin = vectors[2];
            } else if ((vectors[1]->get_point()[2] <= z && vectors[2]->get_point()[2] <= z &&
                    vectors[0]->get_point()[2] > z) ||
                       (vectors[1]->get_point()[2] >= z && vectors[2]->get_point()[2] >= z &&
                               vectors[0]->get_point()[2] < z)
                    ) {
                // vec 0 is high, vec 1 is low, and vec 2 is low OR
                // vec 0 is low, vec 1 is high, and vec 2 is high
                va = vectors[1];
                vb = vectors[2];
                origin = vectors[0];
            } else if ((vectors[0]->get_point()[2] <= z && vectors[2]->get_point()[2] <= z &&
                    vectors[1]->get_point()[2] > z) ||
                       (vectors[0]->get_point()[2] >= z && vectors[2]->get_point()[2] >= z &&
                               vectors[1]->get_point()[2] < z)
                    ) {
                // vec 0 is low, vec 1 is high, and vec 2 is low OR
                // vec 0 is high, vec 1 is low, and vec 2 is high
                va = vectors[0];
                vb = vectors[2];
                origin = vectors[1];
            } else {
                //std::cout << "didn't satisfy\n";
                std::cout << vectors[0] << std::endl
                          << vectors[1] << std::endl
                          << vectors[2] << std::endl;

            } // TODO add case where one is on the plane and the other two are alternating
            //TODO fails here
            float t1 = (z - va->get_point()[2]) / (origin->get_point()[2] - va->get_point()[2]);
            float t2 = (z - vb->get_point()[2]) / (origin->get_point()[2] - vb->get_point()[2]);
            float x1 = va->get_point()[0] + t1 * (origin->get_point()[0] - va->get_point()[0]);
            float x2 = vb->get_point()[0] + t2 * (origin->get_point()[0] - vb->get_point()[0]);
            float y1 = va->get_point()[1] + t1 * (origin->get_point()[1] - va->get_point()[1]);
            float y2 = vb->get_point()[1] + t2 * (origin->get_point()[1] - vb->get_point()[1]);
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