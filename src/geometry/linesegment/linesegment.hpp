#pragma once

#include <vector>
#include <iostream>
#include <set>
#include <array>
#include <list>
#include <tuple>
#include "artifact.hpp"

namespace samurai {
    class vector; //forward declarations (notice no include)
    class triangle;

    class model;

    struct vector_compare;

    class linesegment : public std::enable_shared_from_this<linesegment>, public artifact {
    private:
        std::array<std::shared_ptr<vector>, 2> vectors;
        std::list<std::shared_ptr<triangle>> triangles;
        std::shared_ptr<model> mdl;
        bool flipped;
    public:
        linesegment(std::array<std::shared_ptr<vector>, 2>);

        std::array<std::shared_ptr<vector>, 2> get_vectors();

        std::list<std::shared_ptr<triangle>> get_triangles();

        bool insert_triangle(std::shared_ptr<triangle>);

        bool is_flipped();

        //adjacent, after, flip segment
        std::tuple<bool, bool, bool> adjacent(std::shared_ptr<linesegment> seg);

        void flip();

        bool rotate(float, float, float, float);

        bool translate(std::array<float, 3>);

        bool equivalent(std::shared_ptr<linesegment> seg);
    };
}
