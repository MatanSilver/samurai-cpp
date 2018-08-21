#pragma once

#include <list>
#include "artifact.hpp"
#include "loop.hpp"

namespace samurai {
    class linesegment;

    class layer : public artifact {
    private:
        std::list<loop> loops;

        std::list<loop> linelist_to_loops(std::list<std::shared_ptr<linesegment>>);

    public:
        //initialize with a list of lines
        layer(std::list<std::shared_ptr<linesegment>>);

        //initialize with a list of loops
        layer(std::list<loop>);

        std::list<loop> get_loops();
    };
}
