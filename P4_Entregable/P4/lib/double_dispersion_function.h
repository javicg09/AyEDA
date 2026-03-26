#ifndef _DOUBLE_DISPERSION_FUNCTION_H_
#define _DOUBLE_DISPERSION_FUNCTION_H_

#include "exploration_function.h"
#include "dispersion_function.h"

template<class Key>
class DoubleDispersionFunction : public ExplorationFuntion<Key>{
  public:
    DoubleDispersionFunction(DispersionFunction<Key>* fd) : fd_(fd) {}

    unsigned operator()(const Key& k, unsigned i)const override {
      return fd_->operator()(k) * i; // Llama a la funcion auxiliar con k y multiplica el resultado por i
    };

  private:
    DispersionFunction<Key>* fd_;
};

#endif