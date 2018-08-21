#include "linesegment.hpp"
#include "vector.hpp"
#include <set>
#include <iostream>
#include <list>

namespace samurai {
    vector::vector() {
    }

    vector::vector(std::array<float, 3> pnt) {
        point = std::array<float, 3>(pnt);
    }

    std::array<float, 3> vector::get_point() {
        return point;
    }

    std::list<std::shared_ptr<linesegment>> vector::get_linesegments() {
        return linesegments;
    }

    std::list<std::shared_ptr<triangle>> vector::get_triangles() {
        return triangles;
    }

    bool vector::insert_linesegment(std::shared_ptr<linesegment> ls) {
        bool contained = std::any_of(linesegments.begin(), linesegments.end(), [ls](std::shared_ptr<linesegment> ls2){
            return ls2->equivalent(ls); });
        if (contained == true) {
            return false;
        }
        linesegments.push_back(ls);
        return true;
    }

    bool vector::insert_triangle(std::shared_ptr<triangle> tri) {
        //triangles.insert(tri);
        return false;
    }

    void vector::print() {
        std::cout << "{" << point[0] << "," << point[1] << "," << point[2] << "}" << std::endl;
    }

    bool vector::rotate_x(float) {
        return false;
    }

    bool vector::rotate_y(float) {
        return false;
    }

    bool vector::rotate_z(float) {
        return false;
    }

    bool vector::rotate(std::array<float, 3> rot, std::array<float, 3> origin) {
        this->translate({-origin[0], -origin[1], -origin[2]});
        this->rotate_x(rot[0]);
        this->rotate_y(rot[1]);
        this->rotate_z(rot[2]);
        this->translate(origin);
        return true;
    }

    bool vector::translate(std::array<float, 3> offset) {
        point[0] += offset[0];
        point[1] += offset[1];
        point[2] += offset[2];
        return true;
    }
}