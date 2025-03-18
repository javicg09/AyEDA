#ifndef DYNAMIC_SEQUENCE_CC
#define DYNAMIC_SEQUENCE_CC

#include "dynamic_sequence.h"

template<class Key>
bool dynamicSequence<Key>::search(const Key& k) const {
  for (int i = 0; i < container_.size(); i++) {
    if (container_[i] == k) {
      return true;
    }
  }
  return false;
}

template<class Key>
bool dynamicSequence<Key>::insert(const Key& k) {
  for (int i = 0; i < container_.size(); i++) {
    if (container_[i] == k) {
      return false;
    }
  }
  container_.push_back(k);
  return true;
}

#endif