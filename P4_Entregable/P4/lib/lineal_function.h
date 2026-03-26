#ifndef _LINEAL_FUNCTION_H_
#define _LINEAL_FUNCTION_H_

#include "exploration_function.h"

template<class Key>
class LinealFunction : public ExplorationFunction<Key>{
  public:
    unsigned operator()(const Key& k, unsigned i)const override {
      return i;
    };
};

#endif