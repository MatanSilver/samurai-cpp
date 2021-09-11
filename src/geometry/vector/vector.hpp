#pragma once

#include <array>
#include <vector>
#include <memory>
#include <set>
#include <list>
#include "artifact.hpp"
#include "utils.hpp"


namespace samurai {
    typedef std::array<float, 3> point_t;

    class linesegment;

    class triangle;

    class model;

    class vector : public std::enable_shared_from_this<vector>, public artifact {
    private:
        point_t point;
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