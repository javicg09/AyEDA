#pragma once

#include <cstdlib>

template<class Key>
class ExplorationFunction {
 public:
  virtual unsigned operator()(const Key&, unsigned) const = 0;
  virtual ~ExplorationFunction() {}
};