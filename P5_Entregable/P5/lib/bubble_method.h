#ifndef _BUBBLE_METHOD_H_
#define _BUBBLE_METHOD_H_

#include "sort_method.h"
#include "bubble_sort.h"

template<class Key>
class Bubble : public SortMethod<Key> {
  public:
    Bubble(StaticSequence<Key>& seq, unsigned size, int log = 0)
      : SortMethod<Key>(seq, size, log) {}

    void Sort() override {
      bubbleSort(this->seq_, this->size_, this->log_);
    }
};

#endif