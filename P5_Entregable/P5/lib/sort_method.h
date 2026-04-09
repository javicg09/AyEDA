#ifndef _SORT_METHOD_H_
#define _SORT_METHOD_H_

#include "static_sequence.h"

template<class Key>
class SortMethod {
  public:
    SortMethod(StaticSequence<Key>& seq, unsigned size, bool trace = false)
      : seq_(seq), size_(size), trace_(trace) {}
    virtual void Sort() = 0;

  protected:
    StaticSequence<Key>& seq_;
    unsigned size_;
    bool trace_;
};

#endif