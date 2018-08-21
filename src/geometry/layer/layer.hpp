#pragma once
#include <list>
#include "container.hpp"
#include "artifact.hpp"

namespace samurai {
  class linesegment;
  class layer : public artifact {
  private:
    std::list<std::list<std::shared_ptr<linesegment>>> loops;
    std::list<std::list<std::shared_ptr<linesegment>>> linelist_to_loops(std::list<std::shared_ptr<linesegment>>);
  public:
    //initialize with a list of lines
    layer(std::list<std::shared_ptr<linesegment>>);
    //initialize with a list of loops
    layer(std::list<std::list<std::shared_ptr<linesegment>>>);
    std::list<std::list<std::shared_ptr<linesegment>>> get_loops();
  };
}
