#ifndef _SELECTION_METHOD_H_
#define _SELECTION_METHOD_H_

#include "sort_method.h"
#include "selection_sort.h"

template<class Key>
class Selection : public SortMethod<Key> {
  public:
    Selection(StaticSequence<Key>& seq, unsigned size, bool trace = false)
      : SortMethod<Key>(seq, size, trace) {}

    void Sort() override {
      selectionSort(this->seq_, this->size_, this->trace_);
    }
};

#endif