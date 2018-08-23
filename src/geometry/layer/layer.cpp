#include <list>
#include <vector>
#include "linesegment.hpp"
#include "layer.hpp"
#include "loop.hpp"
#include "ring.hpp"
#include "utils.hpp"

namespace samurai {
    layer::layer(std::vector<loop> looplist) {
        loops = looplist;
        //stitch intersections into loops
        closeloops();
    }

    layer::layer(std::vector<std::shared_ptr<linesegment>> lines) {
        for (auto ls : lines) {
            loop l(ls);
            loops.push_back(loop(ls));
        }
        //stitch intersections into loops
        closeloops();
    }

    std::vector<loop> layer::get_loops() {
        return loops;
    }

    bool layer::closeloops() {
        throw NotImplementedException();
    }
}
