#ifndef NODOB_H
#define NODOB_H

template <typename Key>
class NodoB {
 public:
  NodoB(Key dato, NodoB<Key>* izdo = nullptr, NodoB<Key>* dcho = nullptr)
      : dato(dato), izdo(izdo), dcho(dcho) {}

  Key& getDato() { return dato; }
  const Key& getDato() const { return dato; }

  NodoB<Key>*& getIzdo() { return izdo; }
  NodoB<Key>* getIzdo() const { return izdo; }

  NodoB<Key>*& getDcho() { return dcho; }
  NodoB<Key>* getDcho() const { return dcho; }

  void setDato(const Key& d) { dato = d; }
  void setIzdo(NodoB<Key>* i) { izdo = i; }
  void setDcho(NodoB<Key>* d) { dcho = d; }

 protected:
  Key dato;
  NodoB<Key>* izdo;
  NodoB<Key>* dcho;
};

#endif
