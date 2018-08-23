#pragma once

#include <vector>
#include <string>
#include <list>
#include <array>
#include <unordered_set>
#include <set>
#include <utility>
#include "layer.hpp"
#include "artifact.hpp"

namespace samurai {
    class triangle; //forward declarations
    class linesegment;

    class vector;

    class model : artifact {
    private:
        std::vector<std::shared_ptr<triangle>> triangles;
        std::vector<std::shared_ptr<vector>> vectors;
        std::vector<std::shared_ptr<linesegment>> linesegments;

    public:
        model();

        layer slice_at_z(float z);

        std::vector<layer> slice(float layer_height);

        float highest_z();

        float lowest_z();

        void rotate(float, std::array<float, 3>);

        void translate(std::array<float, 3>);

        bool insert_triangle(std::shared_ptr<triangle> tri);

        std::vector<std::shared_ptr<triangle>> get_triangles();

        std::vector<std::shared_ptr<linesegment>> get_linesegments();

        std::vector<std::shared_ptr<vector>> get_vectors();

        std::shared_ptr<vector> insert_vector(std::array<float, 3> pnt);

        std::shared_ptr<vector> insert_vector(std::shared_ptr<samurai::vector> vec);

        std::shared_ptr<linesegment> insert_linesegment(std::array<std::shared_ptr<vector>, 2> vecs);

        std::shared_ptr<linesegment> insert_linesegment(std::shared_ptr<linesegment> newls);
    };

    bool are_joined(std::shared_ptr<linesegment> ls1, std::shared_ptr<linesegment> ls2);

    bool vector_approx(std::shared_ptr<vector> vec1, std::shared_ptr<vector>);

    void flip(std::vector<std::shared_ptr<linesegment>> *ll);

    bool splice_in_list(std::vector<std::shared_ptr<linesegment>> &ll1, std::vector<std::shared_ptr<linesegment>> &ll2);

    std::string layers_to_gcode(std::vector<layer>);

    std::ostream &operator<<(std::ostream &out, const model &m);

}
