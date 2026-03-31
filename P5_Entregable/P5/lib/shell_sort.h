#ifndef _SHELL_SORT_H_
#define _SHELL_SORT_H_

#include "static_sequence.h"
#include <algorithm>

template<class Key>
void shellSort(StaticSequence<Key>& seq, unsigned size, double alpha) {
  unsigned gap = size * alpha;
  
  while(gap >= 1) {
    for(int i = gap; i < size; i++){
      int j = i;
      while(j >= gap && seq[j] < seq[j - gap]){
        std::swap(seq[j], seq[j - gap]);
        j -= gap;
      }
    }
    gap *= alpha;
  }
}

#endif