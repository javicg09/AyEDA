#ifndef _MERGE_SORT_H_
#define _MERGE_SORT_H_

#include "static_sequence.h"
#include <algorithm>
#include <vector>

template<class Key>
void mix(StaticSequence<Key>& seq, unsigned begin, unsigned mid, unsigned end) {
  std::vector<Key> aux(end - begin + 1);
  int i = begin, j = mid + 1, k = 0;
  while (i <= mid && j <= end) {
    if (seq[i] < seq[j]) {
        aux[k] = seq[i];
        i++;
    } else{
      aux[k] = seq[j];
      j++;
    }
    k++;
  }
  // copiar restos
  while (i <= mid) aux[k++] = seq[i++];
  while (j <= end) aux[k++] = seq[j++];

  // copiar aux de vuelta a seq
  for (unsigned l = begin; l <= end; l++) {
    seq[l] = aux[l - begin];
  }
}

template<class Key>
void mergeSort(StaticSequence<Key>& seq, unsigned begin, unsigned end, unsigned size, int log = 0) {
  if (begin < end) {
    unsigned mid = (begin + end) / 2;
    mergeSort(seq, begin, mid, size, log);
    mergeSort(seq, mid + 1, end, size, log);
    mix(seq, begin, mid, end);
    if (log >= 2) {
      for (unsigned k = 0; k < size; k++)
        std::cout << seq[k] << " ";
      std::cout << std::endl;
    }
  }
}

#endif