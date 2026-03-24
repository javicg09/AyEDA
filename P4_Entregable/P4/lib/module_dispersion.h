#ifndef _MODULE_DISPERSION_H_
#define _MODULE_DISPERSION_H_

#include "dispersion_function.h"

template<class Key>
class ModuleDispersion : public DispersionFunction<Key> {
  public:
    ModuleDispersion(const unsigned tableSize) : tableSize_(tableSize) {};

    unsigned operator()(const Key& k) const override{
      return (long)k % tableSize_;
    };

  private:
    unsigned tableSize_;
};

#endif