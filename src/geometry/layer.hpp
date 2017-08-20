#pragma once
#include <list>

namespace samurai {
  class linesegment;
  class layer {
  private:
    std::list<std::list<std::shared_ptr<linesegment>>> loops;
    std::list<std::list<std::shared_ptr<linesegment>>> linelist_to_loops(std::list<std::shared_ptr<linesegment>>);
  public:
    layer(std::list<std::shared_ptr<linesegment>>);
    std::list<std::list<std::shared_ptr<linesegment>>> get_loops();
  };
}