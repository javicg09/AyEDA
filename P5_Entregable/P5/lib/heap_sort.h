#ifndef _HEAP_SORT_H_
#define _HEAP_SORT_H_

#include "static_sequence.h"
#include <algorithm>
#include <iostream>

template<class Key>
void sink(StaticSequence<Key>& seq, unsigned size, unsigned i){
  unsigned max = i;
  unsigned left = (2*i) + 1;
  unsigned right = (2*i) + 2;

  if (left < size && seq[left] > seq[max]) max = left;
  if (right < size && seq[right] > seq[max]) max = right;

  if (max != i) {
    std::swap(seq[i], seq[max]);
    sink(seq, size, max);
  }
}

template<class Key>
void heapSort(StaticSequence<Key>& seq, unsigned size, bool trace = false) {
  unsigned mid = (size / 2) - 1;
  for (int i = mid; i >= 0; i--){
    sink(seq, size, i);
    if (trace) {
      for (unsigned k = 0; k < size; k++)
        std::cout << seq[k] << " ";
      std::cout << std::endl;
    }
  }
  for (int i = size - 1; i > 0; i--){
    std::swap(seq[0], seq[i]);
    sink(seq, i, 0);
    if (trace) {
      for (unsigned k = 0; k < size; k++)
        std::cout << seq[k] << " ";
      std::cout << std::endl;
    }
  }
}

#endif