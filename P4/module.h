#pragma once

#include "dispersion_function.h"

template<class Key>
class Module : public DispersionFunction<Key> {
 public:
  Module(const unsigned size) : tableSize_(size) {}
  unsigned operator()(const Key& k) const override {return k % tableSize_;}

 private:
 unsigned tableSize_;
};
