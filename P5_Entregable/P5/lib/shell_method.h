#ifndef _SHELL_METHOD_H_
#define _SHELL_METHOD_H_

#include "sort_method.h"
#include "shell_sort.h"

template<class Key>
class Shell : public SortMethod<Key> {
  public:
    Shell(StaticSequence<Key>& seq, unsigned size, double alpha, bool trace = false)
      : SortMethod<Key>(seq, size, trace), alpha_(alpha) {}

    void Sort() override {
      shellSort(this->seq_, this->size_, this->alpha_, this->trace_);
    }

  private:
    double alpha_;
};

#endif