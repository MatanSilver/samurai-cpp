#pragma once

#include <vector>
#include <array>
#include <set>
#include "artifact.hpp"

namespace samurai {
    class vector;

    class linesegment;

    class model;

    class triangle : public std::enable_shared_from_this<triangle>, public artifact {
    private:
        std::set<std::shared_ptr<vector>> vectors;
        std::set<std::shared_ptr<linesegment>> linesegments;
        std::array<float, 3> normal;
    public:

        triangle();

        triangle(std::set<std::shared_ptr<vector>>, std::set<std::shared_ptr<linesegment>>, std::array<float, 3>
        );

        std::set<std::shared_ptr<vector>> get_vectors();

        std::set<std::shared_ptr<linesegment>> get_linesegments();

        std::array<float, 3> get_normal();

        bool insert_linesegment(std::shared_ptr<linesegment>);

        bool insert_vector(std::shared_ptr<vector>);

        std::vector<std::shared_ptr<vector>> intersect_plane(float);

        bool intersects_z(float);
    };
}
