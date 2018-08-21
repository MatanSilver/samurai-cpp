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
        std::set<std::shared_ptr<vector>> vec_set;
        std::set<std::shared_ptr<linesegment>> ls_set;
#ifdef MULTI_THREAD
        mdl->mtx.lock_shared();
#endif
        auto p1 = mdl->get_or_create_vector({t.v1.x, t.v1.y, t.v1.z});
        vec_set.insert(p1);
        auto p2 = mdl->get_or_create_vector({t.v2.x, t.v2.y, t.v2.z});
        vec_set.insert(p2);
        auto p3 = mdl->get_or_create_vector({t.v3.x, t.v3.y, t.v3.z});
        vec_set.insert(p3);
        auto ls1 = mdl->get_or_create_linesegment({p1, p2});
        auto ls2 = mdl->get_or_create_linesegment({p2, p3});
        auto ls3 = mdl->get_or_create_linesegment({p1, p3});
#ifdef MULTI_THREAD
        mdl->mtx.unlock_shared();
        mdl->mtx.lock();
#endif
        mdl->insert_vector(p1); // TODO if NOT found, add to model
        mdl->insert_vector(p2);
        mdl->insert_vector(p3);

#ifdef MULTI_THREAD
        mdl->mtx.unlock();
#endif
        std::array<float, 3> normal = {t.normal.x, t.normal.y, t.normal.z};
        //create triangle (guaranteed all triangles are unique unless something is seriously wrong with stl file)
        auto tri = std::make_shared<triangle>(vec_set, ls_set, normal);
        //add vectors to triangle
        tri->insert_vector(p1);
        tri->insert_vector(p2);
        tri->insert_vector(p3);
        tri->insert_linesegment(ls1);
        tri->insert_linesegment(ls2);
        tri->insert_linesegment(ls3);

#ifdef MULTI_THREAD
        mdl->mtx.lock();
#endif
        mdl->add_triangle(tri);
#ifdef MULTI_THREAD
        mdl->mtx.unlock();
#endif
        return;
    }

    std::shared_ptr<model> stl_data_to_model(bin_stl::stl_data *data) {
        std::shared_ptr<model> mdl = std::make_shared<model>();
#ifdef MULTI_THREAD
        std::queue<std::thread> qu;
#endif
        int i = 0;
        for (auto t : data->triangles) {
            i++;
#ifdef TRUNCATE
            if (i > 500) break; //TODO remove after debugging
#endif

#ifdef MULTI_THREAD
            if (qu.size() < 10) {
              qu.push(std::thread(marshall_triangle, mdl, t));
            } else {
              while (!qu.empty()) {
                qu.front().join();
                qu.pop();
              }
            }
#else
            marshall_triangle(mdl, t);
#endif
        }
        return mdl;
    }
}
