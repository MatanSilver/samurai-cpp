#include <list>
#include <vector>
#include "linesegment.hpp"
#include "layer.hpp"
#include "loop.hpp"
#include "ring.hpp"

namespace samurai {
  layer::layer(std::list<std::list<std::shared_ptr<linesegment>>> looplist) {
    loops = looplist;
  }
  layer::layer(std::list<std::shared_ptr<linesegment>> linelist) {
    loops = linelist_to_loops(linelist);
  }
  std::list<std::list<std::shared_ptr<linesegment>>> layer::get_loops() {
    return loops;
  }
  std::list<loop> layer::linelist_to_loops(std::list<std::shared_ptr<linesegment>> linelist) {
    ring<loop> r = ring<loop>();
    for (auto l : linelist) {
      loop(std::list<std::shared_ptr<linesegment>> lines)
      std::list<std::shared_ptr<linesegment>> tmplinelist = {l};
      loop newloop
      ringbuff.add(loop(tmplinelist));
    }
    while(ringbuff.proceed()) {
      baseloop = ringbuff.get_val();
      while (ringbuff.proceed()) {
        cmploop = ringbuff.get_val();
        bool success = baseloop.join_loop(cmploop);
        if (success) {
          //remove cmploop from buffer
          ringbuff.remove()
        }
      }
    }
  }
}
