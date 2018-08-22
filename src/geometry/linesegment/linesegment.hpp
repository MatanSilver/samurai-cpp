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
        bool flipped;
    public:
        linesegment(std::array<std::shared_ptr<vector>, 2>);

        std::array<std::shared_ptr<vector>, 2> get_vectors();

        bool is_flipped();

        //adjacent, after, flip segment
        std::tuple<bool, bool, bool> adjacent(std::shared_ptr<linesegment> seg);

        void flip();

        void rotate(float, std::array<float, 3>);

        void translate(std::array<float, 3>);

        bool equal(std::shared_ptr<linesegment>);

        bool approx_equal(std::shared_ptr<linesegment>);

        bool contains_vector(std::shared_ptr<vector>);

        bool equivalent(std::shared_ptr<linesegment>);

        bool approx_equivalent(std::shared_ptr<linesegment>);
    };
}
