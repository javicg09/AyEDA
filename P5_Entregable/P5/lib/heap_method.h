#ifndef _HEAP_METHOD_H_
#define _HEAP_METHOD_H_

#include "sort_method.h"
#include "heap_sort.h"

template<class Key>
class Heap : public SortMethod<Key> {
  public:
    Heap(StaticSequence<Key>& seq, unsigned size, bool trace = false)
      : SortMethod<Key>(seq, size, trace) {}

    void Sort() override {
      heapSort(this->seq_, this->size_, this->trace_);
    }
};

#endif