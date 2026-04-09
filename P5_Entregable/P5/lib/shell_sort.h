#ifndef _SHELL_SORT_H_
#define _SHELL_SORT_H_

#include "static_sequence.h"
#include <algorithm>
#include <iostream>

template<class Key>
void shellSort(StaticSequence<Key>& seq, unsigned size, double alpha, bool trace = false) {
  unsigned gap = size * alpha;

  while(gap >= 1) {
    for(int i = gap; i < size; i++){
      int j = i;
      while(j >= gap && seq[j] < seq[j - gap]){
        std::swap(seq[j], seq[j - gap]);
        j -= gap;
      }
    }
    if (trace) {
      for (unsigned k = 0; k < size; k++)
        std::cout << seq[k] << " ";
      std::cout << std::endl;
    }
    gap *= alpha;
  }
}

#endif