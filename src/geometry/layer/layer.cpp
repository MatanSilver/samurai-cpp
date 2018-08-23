#include <list>
#include <vector>
#include "linesegment.hpp"
#include "layer.hpp"
#include "loop.hpp"
#include "ring.hpp"
#include "utils.hpp"

namespace samurai {
    layer::layer(std::vector<loop> looplist) {
        loops_adversary = looplist;
        loop l = loops_adversary.front();
        loops.push_back(l);
        loops_adversary.erase(loops_adversary.begin());
        //stitch intersections into loops
        closeloops();
    }

    layer::layer(std::vector<std::shared_ptr<linesegment>> lines) {
        for (auto ls : lines) {
            loop l(ls);
            loops_adversary.push_back(loop(ls));
        }
        loop l = loops_adversary.front();
        loops.insert(loops.begin(), l);
        loops_adversary.erase(loops_adversary.begin());
        //stitch intersections into loops
        closeloops();
    }

    std::vector<loop> layer::get_loops() {
        return loops;
    }

    bool layer::closeloops() {
        //throw NotImplementedException();
        //TODO implement
        bool goOn = true;
        while(goOn) {
            for (auto l1 : loops) {
                for (auto l2 : loops_adversary) {

                }
            }
        }
    }

    bool layer::all_closed() {
        for (auto l : loops) {
            if (!l.is_closed()) {
                return false;
            }
        }
        return true;
    }
}
