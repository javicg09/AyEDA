#ifndef AVL_H
#define AVL_H

#include "ABB.h"
#include "NodoAVL.h"
#include <iostream>
#include <queue>

template <typename Key>
class AVL : public ABB<Key> {
 public:
  AVL(bool traza = false) : traza_(traza) {}

  bool insertar(const Key& k) override {
    bool crece = false;
    return insertarAVL(this->raiz, new NodoAVL<Key>(k), crece);
  }

  void escribir(std::ostream& os) const {
    if (!this->raiz) {
      os << "[arbol vacio]\n";
      return;
    }
    escribirNiveles(os, this->raiz, traza_);
  }

 private:
  bool traza_;

  bool insertarAVL(NodoB<Key>*& nodo, NodoAVL<Key>* nuevo, bool& crece) {
    if (!nodo) {
      nodo = nuevo;
      crece = true;
      return true;
    }

    NodoAVL<Key>* nodoAvl = static_cast<NodoAVL<Key>*>(nodo);

    if (nuevo->getDato() == nodo->getDato()) {
      delete nuevo;
      crece = false;
      return false;
    }

    if (nuevo->getDato() < nodo->getDato()) {
      bool resultado = insertarAVL(nodo->getIzdo(), nuevo, crece);
      if (crece) {
        nodoAvl->setBal(nodoAvl->getBal() - 1);
        if (nodoAvl->getBal() == -2) {
          if (traza_) {
            std::cout << "Desbalanceo:\n";
            escribirNiveles(std::cout, this->raiz, true);
          }
          NodoAVL<Key>* hijoIzq = static_cast<NodoAVL<Key>*>(nodo->getIzdo());
          if (hijoIzq->getBal() == 1) {
            rotarID(nodo);
            if (traza_) {
              std::cout << "Rotacion ID en [" << nodoAvl->getDato() << "("
                        << nodoAvl->getBal() << ")]:\n";
              escribirNiveles(std::cout, this->raiz, true);
            }
          } else {
            rotarII(nodo);
            if (traza_) {
              std::cout << "Rotacion II en [" << nodoAvl->getDato() << "("
                        << nodoAvl->getBal() << ")]:\n";
              escribirNiveles(std::cout, this->raiz, true);
            }
          }
          crece = false;
        } else if (nodoAvl->getBal() == 0) {
          crece = false;
        }
      }
      return resultado;
    } else {
      bool resultado = insertarAVL(nodo->getDcho(), nuevo, crece);
      if (crece) {
        nodoAvl->setBal(nodoAvl->getBal() + 1);
        if (nodoAvl->getBal() == 2) {
          if (traza_) {
            std::cout << "Desbalanceo:\n";
            escribirNiveles(std::cout, this->raiz, true);
          }
          NodoAVL<Key>* hijoDer = static_cast<NodoAVL<Key>*>(nodo->getDcho());
          if (hijoDer->getBal() == -1) {
            rotarDI(nodo);
            if (traza_) {
              std::cout << "Rotacion DI en [" << nodoAvl->getDato() << "("
                        << nodoAvl->getBal() << ")]:\n";
              escribirNiveles(std::cout, this->raiz, true);
            }
          } else {
            rotarDD(nodo);
            if (traza_) {
              std::cout << "Rotacion DD en [" << nodoAvl->getDato() << "("
                        << nodoAvl->getBal() << ")]:\n";
              escribirNiveles(std::cout, this->raiz, true);
            }
          }
          crece = false;
        } else if (nodoAvl->getBal() == 0) {
          crece = false;
        }
      }
      return resultado;
    }
  }

  void rotarII(NodoB<Key>*& nodo) {
    NodoAVL<Key>* nodo1 = static_cast<NodoAVL<Key>*>(nodo->getIzdo());
    nodo->setIzdo(nodo1->getDcho());
    nodo1->setDcho(nodo);

    NodoAVL<Key>* nodoAvl = static_cast<NodoAVL<Key>*>(nodo);
    if (nodo1->getBal() == -1) {
      nodoAvl->setBal(0);
      nodo1->setBal(0);
    } else {
      nodoAvl->setBal(-1);
      nodo1->setBal(1);
    }

    nodo = nodo1;
  }

  void rotarDD(NodoB<Key>*& nodo) {
    NodoAVL<Key>* nodo1 = static_cast<NodoAVL<Key>*>(nodo->getDcho());
    nodo->setDcho(nodo1->getIzdo());
    nodo1->setIzdo(nodo);

    NodoAVL<Key>* nodoAvl = static_cast<NodoAVL<Key>*>(nodo);
    if (nodo1->getBal() == 1) {
      nodoAvl->setBal(0);
      nodo1->setBal(0);
    } else {
      nodoAvl->setBal(1);
      nodo1->setBal(-1);
    }

    nodo = nodo1;
  }

  void rotarID(NodoB<Key>*& nodo) {
    NodoAVL<Key>* nodo1 = static_cast<NodoAVL<Key>*>(nodo->getIzdo());
    NodoAVL<Key>* nodo2 = static_cast<NodoAVL<Key>*>(nodo1->getDcho());

    nodo1->setDcho(nodo2->getIzdo());
    nodo2->setIzdo(nodo1);
    nodo->setIzdo(nodo2->getDcho());
    nodo2->setDcho(nodo);

    NodoAVL<Key>* nodoAvl = static_cast<NodoAVL<Key>*>(nodo);
    if (nodo2->getBal() == -1) {
      nodoAvl->setBal(1);
      nodo1->setBal(0);
    } else if (nodo2->getBal() == 0) {
      nodoAvl->setBal(0);
      nodo1->setBal(0);
    } else {
      nodoAvl->setBal(0);
      nodo1->setBal(-1);
    }
    nodo2->setBal(0);

    nodo = nodo2;
  }

  void rotarDI(NodoB<Key>*& nodo) {
    NodoAVL<Key>* nodo1 = static_cast<NodoAVL<Key>*>(nodo->getDcho());
    NodoAVL<Key>* nodo2 = static_cast<NodoAVL<Key>*>(nodo1->getIzdo());

    nodo1->setIzdo(nodo2->getDcho());
    nodo2->setDcho(nodo1);
    nodo->setDcho(nodo2->getIzdo());
    nodo2->setIzdo(nodo);

    NodoAVL<Key>* nodoAvl = static_cast<NodoAVL<Key>*>(nodo);
    if (nodo2->getBal() == 1) {
      nodoAvl->setBal(-1);
      nodo1->setBal(0);
    } else if (nodo2->getBal() == 0) {
      nodoAvl->setBal(0);
      nodo1->setBal(0);
    } else {
      nodoAvl->setBal(0);
      nodo1->setBal(1);
    }
    nodo2->setBal(0);

    nodo = nodo2;
  }

  void escribirNiveles(std::ostream& os, NodoB<Key>* raiz, bool mostrarBal) const {
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
          if (mostrarBal) {
            NodoAVL<Key>* navl = static_cast<NodoAVL<Key>*>(n);
            os << " [" << *navl << "]";
          } else {
            os << " [" << n->getDato() << "]";
          }
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
};

#endif
