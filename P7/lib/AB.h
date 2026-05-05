#ifndef AB_H
#define AB_H

#include <iostream>
#include <queue>

#include "NodoB.h"

template <typename Key>
class AB {
 public:
  AB() : raiz(nullptr) {}
  virtual ~AB() { destruir(raiz); }

  virtual bool insertar(const Key& k) = 0;
  virtual bool buscar(const Key& k) const = 0;

  void inorden() const {
    inordenRec(raiz);
    std::cout << "\n";
  }

  void escribir(std::ostream& os) const {
    if (!raiz) {
      os << "[arbol vacio]\n";
      return;
    }
    std::queue<NodoB<Key>*> cola;
    cola.push(raiz);
    int nivel = 0;
    while (!cola.empty()) {
      int sz = static_cast<int>(cola.size());
      os << "Nivel " << nivel << ":";
      std::queue<NodoB<Key>*> siguiente;
      for (int i = 0; i < sz; ++i) {
        NodoB<Key>* n = cola.front();
        cola.pop();
        if (n) {
          os << " [" << n->getDato() << "]";
          siguiente.push(n->getIzdo());
          siguiente.push(n->getDcho());
        } else {
          os << " [.]";
        }
      }
      os << "\n";
      std::swap(cola, siguiente);
      ++nivel;
    }
  }

  int contarMultiplosDe5() const {
    return contarMultiplosDe5Rec(raiz);
  }

 protected:
  NodoB<Key>* raiz;

  int tama(NodoB<Key>* nodo) const {
    if (!nodo) return 0;
    return 1 + tama(nodo->getIzdo()) + tama(nodo->getDcho());
  }

 private:
  void inordenRec(NodoB<Key>* nodo) const {
    if (!nodo) return;
    inordenRec(nodo->getIzdo());
    std::cout << nodo->getDato() << " ";
    inordenRec(nodo->getDcho());
  }

  void destruir(NodoB<Key>* nodo) {
    if (!nodo) return;
    destruir(nodo->getIzdo());
    destruir(nodo->getDcho());
    delete nodo;
  }

  int contarMultiplosDe5Rec(NodoB<Key>* nodo) const {
    if (!nodo) return 0;
    int count = (nodo->getDato() % 5 == 0) ? 1 : 0;
    return count + contarMultiplosDe5Rec(nodo->getIzdo()) + contarMultiplosDe5Rec(nodo->getDcho());
  }
};

template <typename Key>
std::ostream& operator<<(std::ostream& os, const AB<Key>& ab) {
  ab.escribir(os);
  return os;
}

#endif
