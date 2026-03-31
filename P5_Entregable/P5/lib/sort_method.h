#ifndef _SORT_METHOD_H_
#define _SORT_METHOD_H_

#include "static_sequence.h"

template<class Key>
class SortMethod {
  public:
    SortMethod(StaticSequence<Key>& seq, unsigned size) : seq_(seq), size_(size) {}
    virtual void Sort() = 0;

  private:
    StaticSequence<Key>& seq_;
    unsigned size_;
};

#endif