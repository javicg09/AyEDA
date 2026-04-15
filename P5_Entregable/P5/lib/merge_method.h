#ifndef _MERGE_METHOD_H_
#define _MERGE_METHOD_H_

#include "sort_method.h"
#include "merge_sort.h"

template<class Key>
class Merge : public SortMethod<Key> {
  public:
    Merge(StaticSequence<Key>& seq, unsigned size, int log = 0)
      : SortMethod<Key>(seq, size, log) {}

    void Sort() override {
      mergeSort(this->seq_, 0, this->size_ - 1, this->size_, this->log_);
    }
};

#endif