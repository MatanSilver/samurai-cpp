#pragma once

#include "binary_stl.hpp"

namespace samurai {
    class model;

    class linesegment;

    class triangle;

    class vector;

    std::shared_ptr<model> stl_data_to_model(bin_stl::stl_data *);

    void marshall_triangle(std::shared_ptr<model> mdl, bin_stl::triangle t);
}