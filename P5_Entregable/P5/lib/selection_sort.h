#ifndef _SELECTION_SORT_H_
#define _SELECTION_SORT_H_

#include "static_sequence.h"
#include <algorithm>

template<class Key>
void selectionSort(StaticSequence<Key>& seq, unsigned size) {
  for (unsigned i = 0; i < size - 1; i++) {
    unsigned minPos = i;  // asume que i es el mínimo
    for (unsigned j = i + 1; j < size; j++) {
      if (seq[j] < seq[minPos]) {
        minPos = j;  // actualiza posición del mínimo
      }  
    }
    std::swap(seq[i], seq[minPos]);  // coloca el mínimo en su sitio
  }
}

#endif