#pragma once

#include <list>
#include "artifact.hpp"
#include "loop.hpp"
#include "ring.hpp"

namespace samurai {
    class linesegment;

    class layer : public artifact {
    private:
        std::vector<loop> loops;
        std::vector<loop> loops_adversary;

    public:
        //initialize with a list of lines
        layer(std::vector<std::shared_ptr<linesegment>>);

        //initialize with a list of loops
        layer(std::vector<loop>);

        bool closeloops();

        std::vector<loop> get_loops();

        bool all_closed();
    };
}
