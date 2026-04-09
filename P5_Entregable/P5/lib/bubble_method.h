#ifndef _BUBBLE_METHOD_H_
#define _BUBBLE_METHOD_H_

#include "sort_method.h"
#include "bubble_sort.h"

template<class Key>
class Bubble : public SortMethod<Key> {
  public:
    Bubble(StaticSequence<Key>& seq, unsigned size, bool trace = false)
      : SortMethod<Key>(seq, size, trace) {}

    void Sort() override {
      bubbleSort(this->seq_, this->size_, this->trace_);
    }
};

#endif