#pragma once
#include "utils.hpp"
#include "artifact.hpp"

namespace samurai {
  class container {
  public:
    //These functions should ALL be overloaded if a class inherits container
    virtual bool contains(artifact obj) {
      throw NotImplementedException();
    }
    virtual bool in(artifact obj) {
      throw NotImplementedException();
    }
  };
}
