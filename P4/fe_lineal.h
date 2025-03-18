#pragma once

#include "exploration_function.h"
#include "dispersion_function.h"

template<class Key>
class feLineal: public ExplorationFunction<Key> {
 public:
  feLineal(DispersionFunction<Key>* fd, unsigned tableSize) : fd_(fd), tableSize_(tableSize) {}
  unsigned operator()(const Key& k, unsigned i) const {return (fd_->operator()(k) + i) % tableSize_;}
 private:
  unsigned tableSize_;
  DispersionFunction<Key>* fd_;
};