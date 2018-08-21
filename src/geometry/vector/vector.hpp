#pragma once

#include <array>
#include <vector>
#include <set>
#include <list>
#include "artifact.hpp"
#include "utils.hpp"


namespace samurai {
    class linesegment;

    class triangle;

    class model;

    class vector : public std::enable_shared_from_this<vector>, public artifact {
    private:
        std::array<float, 3> point;
    public:

        vector();

        vector(std::array<float, 3>);

        std::array<float, 3> get_point();

        void rotate(float, std::array<float, 3>);

        void translate(std::array<float, 3>);

        bool equal(std::shared_ptr<vector>);

        bool approx_equal(std::shared_ptr<vector>);
    };

    std::ostream &operator<<(std::ostream &out, const vector &v);
}