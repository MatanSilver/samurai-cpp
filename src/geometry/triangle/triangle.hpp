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
        //TODO change to arrays of fixed size?
        std::vector<std::shared_ptr<vector>> vectors;
        std::vector<std::shared_ptr<linesegment>> linesegments;
        std::array<float, 3> normal;
    public:

        triangle();

        triangle(std::vector<std::shared_ptr<vector>>, std::vector<std::shared_ptr<linesegment>>, std::array<float, 3>
        );

        std::vector<std::shared_ptr<vector>> get_vectors();

        std::vector<std::shared_ptr<linesegment>> get_linesegments();

        std::array<float, 3> get_normal();

        bool insert_linesegment(std::shared_ptr<linesegment>);

        bool insert_vector(std::shared_ptr<vector>);

        std::vector<std::shared_ptr<vector>> intersect_plane(float);

        bool intersects_z(float);

        bool contains_linesegment(std::shared_ptr<linesegment>);

        bool contains_vector(std::shared_ptr<vector>);

        /*
         * Triangles should never appear twice in an STL file, so there should be no need to check for
         * equivalence between triangles. Perhaps in the future those functions could be added for further robustness
         * and if any model editing abilities are added.
         */
    };
}
