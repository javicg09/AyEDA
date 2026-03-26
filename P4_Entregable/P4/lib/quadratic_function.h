#ifndef _QUADRATIC_FUNCTION_H_
#define _QUADRATIC_FUNCTION_H_

#include "exploration_function.h"

template<class Key>
class QuadraticFunction : public ExplorationFuntion<Key>{
  public:
    unsigned operator()(const Key& k, unsigned i)const override {
      return i * i;
    };
};

#endif