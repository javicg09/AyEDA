#ifndef NODOAVL_H
#define NODOAVL_H

#include "NodoB.h"
#include <iostream>

template <typename Key>
class NodoAVL : public NodoB<Key> {
 public:
  NodoAVL(Key d)
      : NodoB<Key>(d, nullptr, nullptr), bal(0) {}

  int getBal() const { return bal; }
  void setBal(int b) { bal = b; }

  friend std::ostream& operator<<(std::ostream& os, const NodoAVL<Key>& nodo) {
    os << nodo.getDato() << "(" << nodo.bal << ")";
    return os;
  }

 private:
  int bal;
};

#endif
