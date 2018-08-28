#pragma once

#include <tuple>
#include "linesegment.hpp"

namespace samurai {
    class loop : public artifact {
    private:
        std::list<std::shared_ptr<linesegment>> lines;
        bool flipped;
    public:
        loop(std::list<std::shared_ptr<linesegment>> ls);
        loop(std::shared_ptr<linesegment> l);

        bool add_line(std::shared_ptr<linesegment> line);

        bool join_loop(loop zoop);

        //adjacent, end of list, flip segment
        std::tuple<bool, bool, bool> adjacent(std::shared_ptr<linesegment> line);

        //adjacent, end of list, flip loop
        std::tuple<bool, bool, bool> adjacent(std::list<std::shared_ptr<linesegment>> zoop);

        std::tuple<bool, bool, bool> adjacent(loop zoop);

        bool contains(std::shared_ptr<linesegment> line);

        bool is_ordered();

        void flip();

        bool is_closed();
    };

    class OpenLoopException
            : public std::exception {

    public:

        // Construct with given error message:
        OpenLoopException(const char *error = "Unable to close loop!") {
            errorMessage = error;
        }

        // Provided for compatibility with std::exception.
        const char *what() const noexcept {
            return errorMessage.c_str();
        }

    private:

        std::string errorMessage;
    };
}
