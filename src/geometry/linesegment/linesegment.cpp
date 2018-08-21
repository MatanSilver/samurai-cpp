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

    std::set<std::shared_ptr<triangle>> linesegment::get_triangles() {
        return this->triangles;
    }

    bool linesegment::insert_triangle(std::shared_ptr<triangle> tri) {
        for (auto t : this->triangles) { //check if triangle exists
            if (t == tri) {
                return false;
            }
        }
        this->triangles.insert(tri);
        return true;
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

    bool linesegment::rotate(std::array<float, 3> rot, std::array<float, 3> origin) {
        for (auto v : this->vectors) {
            v.rotate(rot, origin);
        }
    }

    bool linesegment::translate(std::array<float, 3> vec) {
        for (auto v : this->vectors) {
            v.translate(vec);
        }
    }
}
