#include "linesegment.hpp"
#include "vector.hpp"
#include "triangle.hpp"
#include "model.hpp"
#include <iostream>
#include <algorithm>

namespace samurai {
    linesegment::linesegment(std::array<std::shared_ptr<vector>, 2> vectors) {
        this->vectors = vectors;
        //this->triangles = triangles;
    }

    std::array<std::shared_ptr<vector>, 2> linesegment::get_vectors() {
        return this->vectors;
    }

    bool linesegment::is_flipped() {
        return this->flipped;
    }

    void linesegment::flip() {
        std::reverse(this->vectors.begin(), this->vectors.end());
        this->flipped = true;
        return;
    }

    //adjacent, after, flip segment
    std::tuple<bool, bool, bool> linesegment::adjacent(std::shared_ptr<linesegment> seg) {
        bool adjacent = false;
        bool after = false;
        bool flip = false;
        if (this->vectors[1]->get_point() == seg->vectors[0]->get_point()) {
            after = true;
            adjacent = true;
        } else if (this->vectors[1]->get_point() == seg->vectors[1]->get_point()) {
            after = true;
            flip = true;
            adjacent = true;
        } else if (this->vectors[0]->get_point() == seg->vectors[0]->get_point()) {
            flip = true;
            adjacent = true;
        } else if (this->vectors[0]->get_point() == seg->vectors[1]->get_point()) {
            adjacent = true;
        } else {
            //adjacent already == false
        }
        return std::make_tuple(adjacent, after, flip);
    }

    void linesegment::rotate(float angle, std::array<float, 3> axis) {
        for (auto vec : vectors) {
            vec->rotate(angle, axis);
        }
    }

    void linesegment::translate(std::array<float, 3> vec) {
        for (auto v : vectors) {
            v->translate(vec);
        }
    }

    bool linesegment::equal(std::shared_ptr<linesegment> seg) {
        return (this->vectors[0]->equal(seg->get_vectors()[0]) &&
         this->vectors[1]->equal(seg->get_vectors()[1]));
    }

    bool linesegment::approx_equal(std::shared_ptr<linesegment> seg) {
        return (this->vectors[0]->approx_equal(seg->get_vectors()[0]) &&
                this->vectors[1]->approx_equal(seg->get_vectors()[1]));
    }

    bool linesegment::equivalent(std::shared_ptr<linesegment> seg) {
        if (this->equal(seg)) {
            return true;
        }
        auto ls = std::make_shared<linesegment>(seg->get_vectors());
        ls->flip();
        if (this->equal(ls)) {

        }

        return false;
    }

    bool linesegment::approx_equivalent(std::shared_ptr<linesegment> seg) {
        if (this->approx_equal(seg)) {
            return true;
        }
        auto ls = std::make_shared<linesegment>(seg->get_vectors());
        ls->flip();
        if (this->approx_equal(ls)) {

        }

        return false;
    }
}
