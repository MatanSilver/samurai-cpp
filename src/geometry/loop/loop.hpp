#pragma once

#include <tuple>
#include "linesegment.hpp"

namespace samurai {
    class loop : public artifact {
    private:
        std::list<std::shared_ptr<linesegment>> lines;
        bool flipped;
    public:
        loop(std::list<std::shared_ptr<linesegment>> ls) : lines(ls), flipped(false){
        };
        loop(std::shared_ptr<linesegment> l) : flipped(false) {
            lines.push_back(l);
        };

        bool add_line(std::shared_ptr<linesegment> line) {
            if (lines.size() == 0) {
                lines.push_back(line);
                return true;
            } else {
                std::tuple<bool, bool, bool> res = this->adjacent(line);
                if (std::get<0>(res) == false) {
                    return false;
                } else { //add the line!
                    if (std::get<2>(res)) {
                        line->flip();
                    }
                    if (std::get<1>(res)) { //push to end of loop
                        lines.push_back(line);
                    } else { //push to front of loop
                        lines.push_front(line);
                    }
                    return true;
                }
            }
            return false;
        }

        bool join_loop(loop zoop) {
            std::tuple<bool, bool, bool> res = this->adjacent(zoop);
            if (!std::get<0>(res)) {
                return false;
            }
            if (std::get<2>(res)) {
                this->flip();
            }
            if (std::get<1>(res)) {
                //lines.splice(lines.end(), zoop);
            } else {
                //lines.splice(lines.begin(), zoop);
            }
            return true;
        }

        //adjacent, end of list, flip segment
        std::tuple<bool, bool, bool> adjacent(std::shared_ptr<linesegment> line) {
            std::tuple<bool, bool, bool> front_res = lines.front()->adjacent(line);
            std::tuple<bool, bool, bool> back_res = lines.back()->adjacent(line);
            bool adjacent = std::get<0>(front_res) || std::get<0>(back_res);
            bool end_of_list = std::get<1>(back_res);
            bool flip = std::get<2>(front_res) || std::get<2>(back_res);
            return std::make_tuple(adjacent, end_of_list, flip);
        }

        //adjacent, end of list, flip loop
        std::tuple<bool, bool, bool> adjacent(std::list<std::shared_ptr<linesegment>> zoop) {
            std::tuple<bool, bool, bool> front_res_front = lines.front()->adjacent(zoop.front());
            std::tuple<bool, bool, bool> front_res_back = lines.front()->adjacent(zoop.front());
            std::tuple<bool, bool, bool> back_res_front = lines.back()->adjacent(zoop.front());
            std::tuple<bool, bool, bool> back_res_back = lines.back()->adjacent(zoop.back());
            bool adjacent = std::get<0>(front_res_front) || std::get<0>(front_res_back)
                            || std::get<0>(back_res_front) || std::get<0>(back_res_back);
            bool end_of_list = std::get<1>(back_res_front) || std::get<1>(back_res_back);
            //need both front and back to check if this is the last segment in the loop
            bool front_of_list = !std::get<1>(front_res_front) || !std::get<1>(front_res_back);
            //if front of new linelist is adjacent to front of old, mark flip
            //if flip is marked on back_res_back, or if flip is marked on front_res_front
            bool flip = std::get<2>(front_res_front) || std::get<2>(back_res_back);
            return std::make_tuple(adjacent, end_of_list, flip);
        }

        std::tuple<bool, bool, bool> adjacent(loop zoop) {
            return adjacent(zoop.lines);
        }


        bool contains(std::shared_ptr<linesegment> line) {
            for (auto l : lines) {
                if (line == l) {
                    return true;
                }
            }
            return false;
        }

        void flip() {
            for (auto l : lines) {
                l->flip();
            }
            std::reverse(lines.begin(), lines.end());
            this->flipped = true;
        }

        inline bool closed() {
            return (std::get<0>(lines.front()->adjacent(lines.back())) && lines.size() > 2);
        }
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
