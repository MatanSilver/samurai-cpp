#include <unordered_set>
#include <list>
#include <set>
#include <vector>
#include <utility>
#include <cmath>
#include "model.hpp"
#include "linesegment.hpp"
#include "triangle.hpp"
#include "vector.hpp"
#include "layer.hpp"

namespace samurai {
    model::model() {

    }

    //returns a layer containing a vector of closed loops
    layer model::slice_at_z(float z) {
        std::vector<std::shared_ptr<linesegment>> linelist;
        for (auto t : this->triangles) { //TODO change this to only check neighbors?
            if (t->intersects_z(z)) {
                std::array<std::shared_ptr<vector>, 2> vecs = t->intersect_z(z);
                auto ls = std::make_shared<linesegment>(vecs);
                linelist.push_back(ls);
            }
        }
        layer l(linelist);
        return l;
    }

    std::vector<layer> model::slice(float layer_height) {
        std::vector<layer> layers;
        for (float z = this->lowest_z(); z < this->highest_z(); z += layer_height) {
            //slice the model at z
            layer l(this->slice_at_z(z));
            layers.push_back(l);
        }
        return layers;
    }

    std::string layers_to_gcode(std::vector<layer> layers) {
        return "test";
    }

    bool
    splice_in_list(std::vector<std::shared_ptr<linesegment>> *ll1, std::vector<std::shared_ptr<linesegment>> *ll2) {
        throw NotImplementedException();
        //TODO implement
        /*
        if (!is_ordered(ll1) || !is_ordered(ll2)) {
            std::cout << "illegal splice of unordered list" << std::endl;
            throw std::runtime_error("illegal splice of unordered list");
            return false;
        } //TODO check all conditionals
        if (vector_approx((*ll2)[ll2->size() - 1]->get_vectors()[1], (*ll1)[0]->get_vectors()[0]) ==
            true) { //forwards in beginning
            ll1->insert(ll1->begin(), ll2->begin(), ll2->end());
        } else if (vector_approx((*ll2)[0]->get_vectors()[0], (*ll1)[ll1->size() - 1]->get_vectors()[1]) ==
                   true) { //forwards at end
            ll1->insert(ll1->end(), ll2->begin(), ll2->end());
        } else if (vector_approx((*ll2)[0]->get_vectors()[0], (*ll1)[ll1->size() - 1]->get_vectors()[1]) ==
                   true) { //backwards at beginning
            flip(ll2);
            ll1->insert(ll1->begin(), ll2->begin(), ll2->end());
        } else if (
                vector_approx((*ll2)[ll2->size() - 1]->get_vectors()[1], (*ll1)[ll1->size() - 1]->get_vectors()[1]) ==
                true) { //backwards at end
            flip(ll2);
            ll1->insert(ll1->end(), ll2->begin(), ll2->end());
        } else {
            return false;
        }
        return true;
         */
    }

    void flip(std::vector<std::shared_ptr<linesegment>> *ll) {
        std::reverse(ll->begin(), ll->end());
        for (auto ls : *ll) {
            ls->flip();
        }
    }

    bool vector_approx(std::shared_ptr<vector> vec1, std::shared_ptr<vector> vec2) {
        auto pnt1 = vec1->get_point();
        auto pnt2 = vec2->get_point();
        if (std::abs(pnt1[0] - pnt2[0]) < 0.0001 && std::abs(pnt1[1] - pnt2[1]) < 0.0001 &&
            std::abs(pnt1[2] - pnt2[2]) < 0.0001) {
            return true;
        }
        return false;
    }

    bool are_joined(std::shared_ptr<linesegment> ls1, std::shared_ptr<linesegment> ls2) {
        /*std::vector<std::shared_ptr<vector>> ls1v = ls1->get_vectors();
        std::vector<std::shared_ptr<vector>> ls2v = ls2->get_vectors();
        if (ls1v[0]->get_point() == ls2v[0]->get_point()) {
            ls2->flip();
            return true;
        } else if (ls1v[1]->get_point() == ls2v[0]->get_point())
            return false;*/
        return false;
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


    void model::rotate(float angle, std::array<float, 3> axis) {
        for (auto v : this->get_vectors()) {
            v->rotate(angle, axis);
        }
    }

    void model::translate(std::array<float, 3> vec) {
        for (auto v : this->get_vectors()) {
            v->translate(vec);
        }
    }

    bool model::insert_triangle(std::shared_ptr<triangle> tri) {
        //there should be no duplicate triangles in an STL file.
        //if necessary, check for existing equivalent triangle
        this->triangles.push_back(tri);
        return true;
    }

    std::vector<std::shared_ptr<triangle>> model::get_triangles() {
        return triangles;
    }

    std::vector<std::shared_ptr<linesegment>> model::get_linesegments() {
        return linesegments;
    }

    std::vector<std::shared_ptr<vector>> model::get_vectors() {
        return vectors;
    }

    std::shared_ptr<vector> model::insert_vector(std::array<float, 3> pnt) {
        // TODO this is SUPER slow
        auto newvec = std::make_shared<vector>(pnt);
        for (auto vec : vectors) {
            if (newvec->approx_equal(vec)) {
                return vec; //true for found
            }
        }
        vectors.push_back(newvec);
        return newvec;
    }

    std::shared_ptr<linesegment> model::insert_linesegment(std::array<std::shared_ptr<vector>, 2> vecs) {
        auto newls = std::make_shared<linesegment>(vecs);
        for (auto ls : linesegments) {
            if (newls->approx_equivalent(ls)) {
                return ls; //true for found
            }
        }
        linesegments.push_back(newls);
        return newls; //false for not found*/
    }

    std::shared_ptr<vector> model::insert_vector(std::shared_ptr<samurai::vector> newvec) {
        for (auto vec : vectors) {
            if (newvec->approx_equal(vec)) {
                return vec; //true for found
            }
        }
        vectors.push_back(newvec);
        return newvec;
    }

    std::shared_ptr<linesegment> model::insert_linesegment(std::shared_ptr<linesegment> newls) {
        for (auto ls : linesegments) {
            if (newls->approx_equivalent(ls)) {
                return ls; //true for found
            }
        }
        linesegments.push_back(newls);
        return newls; //false for not found*/
    }

    std::ostream &operator<<(std::ostream &out, model &m) {
        auto triangles = m.get_triangles();
        for (auto t : triangles) {
            std::cout << std::endl << "___TRIANGLE___" << std::endl;
            for (auto v : t->get_vectors()) {
                std::cout << v << std::endl;
            }
        }
        return out;
    }

}
