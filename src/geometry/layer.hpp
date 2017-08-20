#pragma once
#include <list>

namespace samurai {
  class linesegment;
  class layer {
  private:
    std::list<std::list<std::shared_ptr<layersegment>>> loops;
    std::list<std::list<std::shared_ptr<layersegment>>> linelist_to_loops(std::list<std::shared_ptr<layersegment>>);
  public:
    layer(std::list<std::shared_ptr<layersegment>>);
    std::list<std::list<std::shared_ptr<layersegment>>> get_loops();
  };
}