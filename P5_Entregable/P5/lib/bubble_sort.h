#ifndef _BUBBLE_SORT_H_
#define _BUBBLE_SORT_H_

#include "static_sequence.h"
#include <algorithm>

template<class Key>
void bubbleSort(StaticSequence<Key>& seq, unsigned size) {
  for (unsigned i = 0; i < size - 1; i++) {
    for (unsigned j = i; j < size - 1 - i; j++) {
      if (seq[j] > seq[j + 1]) {
        std::swap(seq[j], seq[j + 1]);
      }  
    }
  }
}

#endif