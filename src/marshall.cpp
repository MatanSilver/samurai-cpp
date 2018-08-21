#include <vector>
#include <array>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <queue>
#include "marshall.hpp"
#include "linesegment.hpp"
#include "model.hpp"
#include "triangle.hpp"
#include "vector.hpp"


namespace samurai {
    void marshall_triangle(std::shared_ptr<model> mdl, bin_stl::triangle t) {
        std::vector<std::shared_ptr<vector>> vec_vec;
        std::vector<std::shared_ptr<linesegment>> ls_vec;

        auto p1 = mdl->get_or_create_vector({t.v1.x, t.v1.y, t.v1.z});
        vec_vec.push_back(p1);
        auto p2 = mdl->get_or_create_vector({t.v2.x, t.v2.y, t.v2.z});
        vec_vec.push_back(p2);
        auto p3 = mdl->get_or_create_vector({t.v3.x, t.v3.y, t.v3.z});
        vec_vec.push_back(p3);
        auto ls1 = mdl->get_or_create_linesegment({p1, p2});
        auto ls2 = mdl->get_or_create_linesegment({p2, p3});
        auto ls3 = mdl->get_or_create_linesegment({p1, p3});

        mdl->insert_vector(p1);
        mdl->insert_vector(p2);
        mdl->insert_vector(p3);

        std::array<float, 3> normal = {t.normal.x, t.normal.y, t.normal.z};
        //create triangle (guaranteed all triangles are unique unless something is seriously wrong with stl file)
        auto tri = std::make_shared<triangle>(vec_vec, ls_vec, normal);
        //add vectors to triangle
        tri->insert_vector(p1);
        tri->insert_vector(p2);
        tri->insert_vector(p3);
        tri->insert_linesegment(ls1);
        tri->insert_linesegment(ls2);
        tri->insert_linesegment(ls3);

        mdl->add_triangle(tri);

        return;
    }

    std::shared_ptr<model> stl_data_to_model(bin_stl::stl_data *data) {
        std::shared_ptr<model> mdl = std::make_shared<model>();

        int i = 0;
        for (auto t : data->triangles) {
            i++;
            marshall_triangle(mdl, t);
        }
        return mdl;
    }
}
