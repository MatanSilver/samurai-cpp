#include "json.hpp"
#include "config.hpp"

using json = nlohmann::json;

#include <iostream>
#include <fstream>
#include <string>

namespace samurai {
    config::config(std::string filename) {
        std::string rawtext = "";
        std::string line;
        std::ifstream config_file(filename);
        if (config_file.is_open()) {
            json j;
            config_file >> j;
            this->layer_height = j["layer_height"];
        }
    }

    float config::get_layer_height() {
        return this->layer_height;
    }
}