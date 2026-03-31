#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

// Clase base que define la secuencia de valores a ordenar
template<class Key>
class Sequence {
  public:
    virtual bool search(const Key& k) const = 0;
    virtual bool insert(const Key& k) = 0;  

    virtual Key operator[](const unsigned i) const = 0;
    virtual Key& operator[](const unsigned i) = 0;
};

#endif