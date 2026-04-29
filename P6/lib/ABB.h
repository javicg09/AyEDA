#ifndef ABB_H
#define ABB_H

#include "AB.h"

template <typename Key>
class ABB : public AB<Key> {
 public:
  ABB() {}

  bool insertar(const Key& k) override {
    return insertarRec(this->raiz, k);
  }

  bool buscar(const Key& k) const override {
    return buscarRec(this->raiz, k);
  }

 private:
  bool insertarRec(NodoB<Key>*& nodo, const Key& k) {
    if (!nodo) {
      nodo = new NodoB<Key>(k);
      return true;
    }
    if (k == nodo->getDato()) return false;
    if (k < nodo->getDato()) return insertarRec(nodo->getIzdo(), k);
    return insertarRec(nodo->getDcho(), k);
  }

  bool buscarRec(NodoB<Key>* nodo, const Key& k) const {
    if (!nodo) return false;
    if (nodo->getDato() == k) return true;
    if (k < nodo->getDato()) return buscarRec(nodo->getIzdo(), k);
    return buscarRec(nodo->getDcho(), k);
  }
};

#endif
