#pragma once

#include "dispersion_function.h"

template<class Key>
class Sum : public DispersionFunction<Key> {
 public:
  Sum(const unsigned size) : tableSize_(size) {}
  unsigned operator()(const Key& k) const override {
    unsigned sum = 0;
    long int temp = k; // Copia de k para evitar modificar el original
    while (temp > 0) {
      sum += temp % 10;
      temp /= 10;
    }
    return sum % tableSize_;
  }
 private:
  unsigned tableSize_;
};