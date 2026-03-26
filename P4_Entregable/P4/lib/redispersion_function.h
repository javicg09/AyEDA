#ifndef _REDISPERSION_FUNCTION_H_
#define _REDISPERSION_FUNCTION_H_

#include "exploration_function.h"
#include <cstdlib>

template<class Key>
class RedispersionFunction : public ExplorationFunction<Key>{
  public:
    unsigned operator()(const Key& k, unsigned i)const override {
      srand((long)k);
      for(unsigned j = 0; j < i; j++) rand();
      return rand();
    };
};

#endif