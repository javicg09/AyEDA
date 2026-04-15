#ifndef _SORT_METHOD_H_
#define _SORT_METHOD_H_

#include "static_sequence.h"

template<class Key>
class SortMethod {
  public:
    SortMethod(StaticSequence<Key>& seq, unsigned size, int log = 0)
      : seq_(seq), size_(size), log_(log) {}
    virtual void Sort() = 0;

  protected:
    StaticSequence<Key>& seq_;
    unsigned size_;
    int log_;
};

#endif