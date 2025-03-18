#ifndef STATIC_SEQUENCE_CC
#define STATIC_SEQUENCE_CC

#include "static_sequence.h"

template<class Key>
bool staticSequence<Key>::search(const Key& k) const {
  for (const auto& item : container_) {
    if (item == k) {
      return true;
    }
  }
  return false;
}

template<class Key>
bool staticSequence<Key>::insert(const Key& k) {
  container_.push_back(k);
  emptySlots_[container_.size() - 1] = false;
  return true;
}


template<class Key>
bool staticSequence<Key>::isFull() const {
  for (const auto& slot : emptySlots_) {
    if (slot) {
      return false;
    }
  }
  return true;
}

#endif