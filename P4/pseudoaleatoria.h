#pragma once

#include "dispersion_function.h"

template<class Key>
class Pseudoaleatoria : public DispersionFunction<Key> {
 public:
  Pseudoaleatoria(const unsigned size) : tableSize_(size) {}
  unsigned operator()(const Key& k) const override {
    srand(k);
    return rand() % tableSize_;
  }
 private:
  unsigned tableSize_;
};