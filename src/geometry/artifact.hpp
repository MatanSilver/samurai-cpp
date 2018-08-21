#pragma once

#include "utils.hpp"

namespace samurai {
    class artifact {
    public:
        //These functions should ALL be overloaded if a class inherits artifact

        virtual bool rotate(std::array<float, 3> rot, std::array<float, 3> origin) {
            throw NotImplementedException();
        }
        virtual bool translate(std::array<float, 3> vec) {
            throw NotImplementedException();
        }
    };
}
