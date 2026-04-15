#ifndef _BUBBLE_SORT_H_
#define _BUBBLE_SORT_H_

#include "static_sequence.h"
#include <algorithm>
#include <iostream>

template<class Key>
void bubbleSort(StaticSequence<Key>& seq, unsigned size, int log = 0) {
  for (unsigned i = 0; i < size - 1; i++) {
    for (unsigned j = 0; j < size - 1 - i; j++) {
      if (seq[j] > seq[j + 1]) {
        std::swap(seq[j], seq[j + 1]);
      }
    }
    if (log >= 2) {
      for (unsigned k = 0; k < size; k++)
        std::cout << seq[k] << " ";
      std::cout << std::endl;
    }
  }
}

#endif