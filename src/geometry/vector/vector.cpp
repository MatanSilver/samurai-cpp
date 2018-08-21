#include "linesegment.hpp"
#include "vector.hpp"
#include <set>
#include <fstream>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <list>
#include <cmath>
#include "utils.hpp"

namespace samurai {

    vector::vector(std::array<float, 3> pnt) {
        point = std::array<float, 3>(pnt);
    }

    std::array<float, 3> vector::get_point() {
        return point;
    }

    bool vector::rotate(float angle, std::array<float, 3> axis) {
        float u = axis[0], v = axis[1], w = axis[2];
        std::array<std::array<float, 1>, 4> inputMatrix = {point[0], point[1], point[2], 1.0};
        std::array<std::array<float, 1>, 4> outputMatrix = {0.0, 0.0, 0.0, 0.0};
        std::array<std::array<float, 4>, 4> rotationMatrix;
        float L = (u*u + v * v + w * w);
        angle = angle * M_PI / 180.0; //converting to radian value
        float u2 = u * u;
        float v2 = v * v;
        float w2 = w * w;

        rotationMatrix[0][0] = (u2 + (v2 + w2) * cos(angle)) / L;
        rotationMatrix[0][1] = (u * v * (1 - cos(angle)) - w * sqrt(L) * sin(angle)) / L;
        rotationMatrix[0][2] = (u * w * (1 - cos(angle)) + v * sqrt(L) * sin(angle)) / L;
        rotationMatrix[0][3] = 0.0;

        rotationMatrix[1][0] = (u * v * (1 - cos(angle)) + w * sqrt(L) * sin(angle)) / L;
        rotationMatrix[1][1] = (v2 + (u2 + w2) * cos(angle)) / L;
        rotationMatrix[1][2] = (v * w * (1 - cos(angle)) - u * sqrt(L) * sin(angle)) / L;
        rotationMatrix[1][3] = 0.0;

        rotationMatrix[2][0] = (u * w * (1 - cos(angle)) - v * sqrt(L) * sin(angle)) / L;
        rotationMatrix[2][1] = (v * w * (1 - cos(angle)) + u * sqrt(L) * sin(angle)) / L;
        rotationMatrix[2][2] = (w2 + (u2 + v2) * cos(angle)) / L;
        rotationMatrix[2][3] = 0.0;

        rotationMatrix[3][0] = 0.0;
        rotationMatrix[3][1] = 0.0;
        rotationMatrix[3][2] = 0.0;
        rotationMatrix[3][3] = 1.0;

        std::array<std::array<float, 1>, 4> output;
        for(int i = 0; i < 4; i++ ){
            for(int j = 0; j < 1; j++){
                outputMatrix[i][j] = 0;
                for(int k = 0; k < 4; k++){
                    outputMatrix[i][j] += rotationMatrix[i][k] * inputMatrix[k][j];
                }
            }
        }
        point = {outputMatrix[0][0], outputMatrix[1][0], outputMatrix[2][0]};
        return true;
    }

    bool vector::translate(std::array<float, 3> offset) {
        point[0] += offset[0];
        point[1] += offset[1];
        point[2] += offset[2];
        return true;
    }

    bool vector::equivalent(std::shared_ptr<vector> vec) {
        return this->get_point() == vec->get_point();
    }

    bool vector::approx_equivalent(std::shared_ptr<vector> vec) {
        auto p1 = this->get_point();
        auto p2 = vec->get_point();
        return ((p1[0] - p2[0] <= EPSILON) &&
                (p1[1] - p2[1] <= EPSILON) &&
                (p1[2] - p2[2] <= EPSILON));
    }

    std::ostream &operator<<(std::ostream &out, const vector &v) {
        vector v2 = v; //demote to non-const
        auto p = v2.get_point();
        out << "<" << p[0] << ", " << p[1] << ", " << p[2] << ">";
        return out;
    }
}