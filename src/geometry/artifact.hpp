#pragma once

#include "utils.hpp"

namespace samurai {
    class artifact {
    public:
        //These functions should ALL be overloaded if a class inherits container
        virtual bool rotate_x(float rad) {
            throw NotImplementedException();
        }

        virtual bool rotate_y(float rad) {
            throw NotImplementedException();
        }

        virtual bool rotate_z(float rad) {
            throw NotImplementedException();
        }

        virtual bool translate_x(float rad) {
            throw NotImplementedException();
        }

        virtual bool translate_y(float rad) {
            throw NotImplementedException();
        }

        virtual bool translate_z(float rad) {
            throw NotImplementedException();
        }
        virtual bool rotate(std::array<float, 3> rot, std::array<float, 3> origin) {
            throw NotImplementedException();
        }
        virtual bool translate(std::array<float, 3> vec) {
            throw NotImplementedException();
        }
    };
}
