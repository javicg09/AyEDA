#ifndef _SUM_DISPERSION_H_
#define _SUM_DISPERSION_H_

#include "dispersion_function.h"

template<class Key>
class SumDispersion : public DispersionFunction<Key>{
  public:
    SumDispersion(const unsigned tableSize) : tableSize_(tableSize) {}

    unsigned operator()(const Key& k) const override {
      long valor = (long)k;
      long sum = 0;

      while(valor > 0){
        sum += (valor % 10); 
        valor /= 10;
      }

      return sum % tableSize_;
    };

  private:
    unsigned tableSize_;
};

#endif