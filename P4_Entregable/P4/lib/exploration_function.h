#ifndef _EXPLORATION_FUNCTION_H_
#define _EXPLORATION_FUNCTION_H_

template<class Key>
class ExplorationFunction{
  public:
    virtual unsigned operator()(const Key& k, unsigned i) const = 0;
};

#endif