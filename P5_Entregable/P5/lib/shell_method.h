#ifndef _SHELL_METHOD_H_
#define _SHELL_METHOD_H_

#include "sort_method.h"
#include "shell_sort.h"

template<class Key>
class Shell : public SortMethod<Key> {
  public:
    Shell(StaticSequence<Key>& seq, unsigned size, double alpha, int log = 0)
      : SortMethod<Key>(seq, size, log), alpha_(alpha) {}

    void Sort() override {
      shellSort(this->seq_, this->size_, this->alpha_, this->log_);
    }

  private:
    double alpha_;
};

#endif