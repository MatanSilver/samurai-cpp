#include <list>
#include <vector>
#include "linesegment.hpp"
#include "layer.hpp"
#include "loop.hpp"
#include "ring.hpp"
#include "utils.hpp"

namespace samurai {
    layer::layer(std::vector<loop> looplist) {
        loopring = ring<loop>(looplist);
        //stitch intersections into loops
        closeloops();
    }

    layer::layer(std::vector<std::shared_ptr<linesegment>> lines) {
        std::vector<loop> loopvec;
        for (auto ls : lines) {
            loop l(ls);
            loopvec.push_back(loop(ls));
        }
        loopring = ring<loop>(loopvec);
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
        bool lastJoined;
        ringnode<loop> *base = loopring.get_node();
        while(goOn) {

            //if adjacent, join the two and make the base the next node
            //adjacent, end of list, flip
            std::tuple<bool, bool, bool> adj = base->get_val().adjacent(loopring.get_node()->get_val());
            //if ()
            base = loopring.proceed();



            if (goOn && !lastJoined) { //if last joined up, we already proceeded
                loopring.proceed();
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
