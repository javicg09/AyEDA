#ifndef _RANDOM_DISPERSION_H_
#define _RANDOM_DISPERSION_H_

#include "dispersion_function.h"
#include <cstdlib>

template<class Key>
class RandomDispersion : public DispersionFunction<Key>{
  public:
    RandomDispersion(const unsigned tableSize) : tableSize_(tableSize) {}

    unsigned operator()(const Key& k) const override {
      srand((long)k);
      return rand() % tableSize_;
    };

  private:
    unsigned tableSize_;
};

#endif