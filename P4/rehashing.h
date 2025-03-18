#pragma once

#include "dispersion_function.h"

template<class Key>
class Rehashing : public ExplorationFunction<Key> {
 public:
  Rehashing(DispersionFunction<Key>* fd, unsigned tableSize) : fd_(fd), tableSize_(tableSize) {}
  unsigned operator()(const Key& k, unsigned i) const override {
    srand(1); 
    unsigned result = 0; 
    for (size_t j = 0; j < i; j++) {
      result = rand();
    }
    return result % tableSize_;
  }
 private:
  DispersionFunction<Key>* fd_;
  unsigned tableSize_;
};