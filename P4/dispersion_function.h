#pragma once

#include <cstdlib>

template<class Key>
class DispersionFunction {
 public:
  virtual unsigned operator()(const Key&) const = 0;
  virtual ~DispersionFunction() {}
};