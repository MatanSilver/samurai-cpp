#pragma once

#include "utils.hpp"

namespace samurai {
    class artifact {
    public:
        //These functions should ALL be overloaded if a class inherits artifact

        virtual void rotate(std::array<float, 3> rot, std::array<float, 3> origin) {
            throw NotImplementedException();
        }
        virtual void translate(std::array<float, 3> vec) {
            throw NotImplementedException();
        }
    };
}
