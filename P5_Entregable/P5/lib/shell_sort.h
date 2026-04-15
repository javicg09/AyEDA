#ifndef _SHELL_SORT_H_
#define _SHELL_SORT_H_

#include "static_sequence.h"
#include <algorithm>
#include <iostream>

// Imprime la secuencia completa con un prefijo descriptivo
template<class Key>
void printSeq(const StaticSequence<Key>& seq, unsigned size, const std::string& label) {
  std::cout << label;
  for (unsigned k = 0; k < size; k++)
    std::cout << seq[k] << " ";
  std::cout << std::endl;
}

/*
 * Shell Sort con 4 niveles de traza:
 *   Nivel 0: sin traza
 *   Nivel 1: estado inicial y estado final
 *   Nivel 2: estado tras completar cada fase de gap
 *   Nivel 3: estado tras procesar cada elemento en el bucle interno
 *   Nivel 4: estado tras cada swap individual
 */
template<class Key>
void shellSort(StaticSequence<Key>& seq, unsigned size, double alpha, int log = 0) {
  if (log >= 1)
    printSeq(seq, size, "[Inicial]: ");

  unsigned gap = size * alpha;

  while (gap >= 1) {
    if (log >= 2)
      std::cout << "[Gap=" << gap << "]" << std::endl;

    for (int i = gap; i < (int)size; i++) {
      int j = i;
      while (j >= (int)gap && seq[j] < seq[j - gap]) {
        std::swap(seq[j], seq[j - gap]);
        j -= gap;

        if (log >= 4)
          printSeq(seq, size, "  [Swap]: ");
      }

      if (log == 3)
        printSeq(seq, size, "  [Paso i=" + std::to_string(i) + "]: ");
    }

    if (log >= 2)
      printSeq(seq, size, "[Tras gap=" + std::to_string(gap) + "]: ");

    gap *= alpha;
  }

  if (log >= 1)
    printSeq(seq, size, "[Final]: ");
}

#endif
