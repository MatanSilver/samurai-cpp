//
// Created by Matan Silver on 8/28/18.
//

#include "loop.hpp"
#include <list>
#include "linesegment.hpp"
#include <tuple>

namespace samurai {
    loop::loop(std::list<std::shared_ptr<linesegment>> ls) : lines(ls), flipped(false) {
    };

    loop::loop(std::shared_ptr<linesegment> l) : flipped(false) {
        lines.push_back(l);
    };

    bool loop::add_line(std::shared_ptr<linesegment> line) {
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

    bool loop::join_loop(loop zoop) {
        std::tuple<bool, bool, bool> res = this->adjacent(zoop);
        if (!std::get<0>(res)) {
            return false;
        }
        if (std::get<2>(res)) {
            this->flip();
        }
        if (std::get<1>(res)) {
            lines.splice(lines.end(), zoop.lines);
        } else {
            lines.splice(lines.begin(), zoop.lines);
        }
        return true;
    }

//adjacent, end of list, flip segment
    std::tuple<bool, bool, bool> loop::adjacent(std::shared_ptr<linesegment> line) {
        std::tuple<bool, bool, bool> front_res = lines.front()->adjacent(line);
        std::tuple<bool, bool, bool> back_res = lines.back()->adjacent(line);
        bool adjacent = std::get<0>(front_res) || std::get<0>(back_res);
        bool end_of_list = std::get<1>(back_res);
        bool flip = std::get<2>(front_res) || std::get<2>(back_res);
        return std::make_tuple(adjacent, end_of_list, flip);
    }

//adjacent, end of list, flip loop
    std::tuple<bool, bool, bool> loop::adjacent(std::list<std::shared_ptr<linesegment>> zoop) {
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

    std::tuple<bool, bool, bool> loop::adjacent(loop zoop) {
        return adjacent(zoop.lines);
    }

    bool loop::contains(std::shared_ptr<linesegment> line) {
        throw NotImplementedException();
        //TODO implement
        for (auto l : lines) {
            if (line == l) {
                return true;
            }
        }
        return false;
    }

    bool loop::is_ordered() {
        throw NotImplementedException();
        //TODO implement
        /*
        size_t len = lines.size();
        for (int i = 0; i < len - 1; i++) {
            if (!vector_approx((*loop)[i + 1]->get_vectors()[0], (*loop)[i]->get_vectors()[1])) {
                return false;
            }
        }
        return true;
         */
    }

    void loop::flip() {
        //TODO implement
        throw NotImplementedException();
        for (auto l : lines) {
            l->flip();
        }
        std::reverse(lines.begin(), lines.end());
        this->flipped = true;
    }

    bool loop::is_closed() {
        //TODO implement
        //throw NotImplementedException();
        return (std::get<0>(lines.front()->adjacent(lines.back())) && lines.size() > 2);
    }

}
