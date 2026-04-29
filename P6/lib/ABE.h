#ifndef ABE_H
#define ABE_H

#include "AB.h"

template <typename Key>
class ABE : public AB<Key> {
 public:
  ABE() {}

  bool insertar(const Key& k) override {
    if (buscar(k)) return false;
    insertarEq(this->raiz, k);
    return true;
  }

  bool buscar(const Key& k) const override {
    return buscarRec(this->raiz, k);
  }

 private:
  void insertarEq(NodoB<Key>*& nodo, const Key& k) {
    if (!nodo) {
      nodo = new NodoB<Key>(k);
      return;
    }
    if (this->tama(nodo->getIzdo()) <= this->tama(nodo->getDcho())) {
      insertarEq(nodo->getIzdo(), k);
    } else {
      insertarEq(nodo->getDcho(), k);
    }
  }

  bool buscarRec(NodoB<Key>* nodo, const Key& k) const {
    if (!nodo) return false;
    if (nodo->getDato() == k) return true;
    return buscarRec(nodo->getIzdo(), k) || buscarRec(nodo->getDcho(), k);
  }
};

#endif
