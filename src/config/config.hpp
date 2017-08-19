#pragma once
#include <string>
#include "json.hpp"
using json = nlohmann::json;

namespace samurai {
  class config {
  private:
    float layer_height;
  public:
    config(std::string filename);
    float get_layer_height();
  };
}