#pragma once

#include "dispersion_function.h"

template<class Key>
class DoubleHashing : public ExplorationFunction<Key> {
 public:
  DoubleHashing(DispersionFunction<Key>* fd, unsigned tableSize) : fd_(fd), tableSize_(tableSize) {}
  unsigned operator()(const Key& k, unsigned i) const override {return (fd_->operator()(k) + (fd_->operator()(k) * i)) % tableSize_;}
 private:
  DispersionFunction<Key>* fd_;
  unsigned tableSize_;
};