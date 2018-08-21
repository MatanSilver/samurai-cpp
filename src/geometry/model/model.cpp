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

    layer model::slice_at_z(float z) {
        /*std::list<std::shared_ptr<linesegment>> linelist;
        for (auto t : this->triangles) { //TODO change this to only check neighbors?
            if (t->intersects_z(z)) {
                //std::cout << "triangle intersects " << z << std::endl;
                std::vector<std::shared_ptr<vector>> vecs = t->intersect_plane(z);
                auto ls = std::make_shared<linesegment>(vecs);
                for (auto v : vecs) {
                    v->insert_linesegment(ls);
                }
                linelist.push_back(ls);
            }
        }
        layer l(linelist);
        return l;*/
    }

    std::vector<layer> model::slice(float layer_height) {
        /*std::vector<layer> layer_vec;
        for (float z = this->lowest_z(); z < this->highest_z(); z += layer_height) {
            //slice the model at z
            layer linelist(this->slice_at_z(z));
            //stitch intersections into loops
            std::vector<std::vector<std::shared_ptr<linesegment>>> openloops = samurai::linelist_to_openloops(linelist);
            std::vector<std::vector<std::shared_ptr<linesegment>>> closedloops = samurai::closeloops(openloops);
            looplist_list.push_back(closedloops);
        }
        return looplist_list;*/
    }

    std::string layers_to_gcode(std::vector<layer> layers) {
        return "test";
    }

    std::vector<std::vector<std::shared_ptr<linesegment>>>
    linelist_to_openloops(std::vector<std::shared_ptr<linesegment>> linelist) {
        std::vector<std::vector<std::shared_ptr<linesegment>>> openloops;
        for (auto line : linelist) {
            openloops.push_back({line});
        }
        return openloops;
    }

    bool
    splice_in_list(std::vector<std::shared_ptr<linesegment>> *ll1, std::vector<std::shared_ptr<linesegment>> *ll2) {

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
    }

    //void flip(std::vector<std::shared_ptr<linesegment>> *ll);
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

    bool is_ordered(std::vector<std::shared_ptr<linesegment>> *loop) {
        size_t len = loop->size();
        for (int i = 0; i < len - 1; i++) {
            if (!vector_approx((*loop)[i + 1]->get_vectors()[0], (*loop)[i]->get_vectors()[1])) {
                return false;
            }
        }
        return true;
    }

    bool are_joined(std::shared_ptr<linesegment> ls1, std::shared_ptr<linesegment> ls2) {
        /*std::vector<std::shared_ptr<vector>> ls1v = ls1->get_vectors();
        std::vector<std::shared_ptr<vector>> ls2v = ls2->get_vectors();
        if (ls1v[0]->get_point() == ls2v[0]->get_point()) {
            ls2->flip();
            return true;
        } else if (ls1v[1]->get_point() == ls2v[0]->get_point())
            return false;*/
    }

    bool is_closed(std::vector<std::shared_ptr<linesegment>> *loop) {
        if (is_ordered(loop) && are_joined((*loop)[0], (*loop)[loop->size() - 1])) {
            return true;
        }
        return false;
    }

    std::vector<std::vector<std::shared_ptr<linesegment>>>
    closeloops(std::vector<std::vector<std::shared_ptr<linesegment>>> openloops) {
        std::vector<std::vector<std::shared_ptr<linesegment>>> closedloops;
        int tries = 0;
        while (openloops.size() > 1) {
            size_t iters = openloops.size() - 1;
            std::cout << openloops.size();
            const size_t iters_c = iters;
            for (int i = 0; i < iters; i++) { //iterate over all but the last
                bool result = splice_in_list(&openloops[i], &openloops[iters_c]);
                if (result == true) {
                    std::cout << "able to splice" << std::endl;
                    tries = 0;
                    openloops.pop_back(); //cut off last element
                    iters--;
                    if (is_closed(&openloops[i]) == true) {
                        closedloops.push_back(openloops[i]);
                        i--;
                        if (openloops.size() > 1) {
                            //remove openloops[i]
                            openloops.erase(openloops.begin() + i);
                        } else {
                            openloops = {};
                        }
                    }
                } else {
                    tries++;
                    if (tries > 10) {
                        std::cout << "another try" << std::endl;
                        throw std::runtime_error("unable to stitch loops");
                    }
                }
                tries++;
            }
        }
        return closedloops;
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
        for (auto vec : this->get_vectors()) {
            vec->rotate(angle, axis);
        }
    }

    void model::translate(std::array<float, 3> vec) {

    }

    bool model::add_triangle(std::shared_ptr<triangle> tri) {
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

    bool model::insert_vector(std::shared_ptr<vector> vec) {
        this->vectors.push_back(vec);
        return true;
    }

    std::shared_ptr<vector> model::get_or_create_vector(std::array<float, 3> pnt) {
        // TODO this is SUPER slow
        auto newvec = std::make_shared<vector>(pnt);
        for (auto vec : vectors) {
            if (newvec->approx_equal(vec)) {
                return vec; //true for found
            }
        }
        return newvec;
    }

    std::shared_ptr<linesegment> model::get_or_create_linesegment(std::array<std::shared_ptr<vector>, 2> vectors) {
        auto newls = std::make_shared<linesegment>(vectors);
        for (auto ls : linesegments) {
            if (newls->approx_equivalent(ls)) {
                return ls; //true for found
            }
        }
        return newls; //false for not found*/
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
