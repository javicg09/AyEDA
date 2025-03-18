#pragma once

#include <cstddef>
#include "sequence.h"

template<class Key>
class Sequence;

//Abierta
template<class Key>
class dynamicSequence : public Sequence<Key> {
 public:
  
  bool search(const Key& k) const override;
  bool insert(const Key& k) override;
  bool isFull() const override {return false;}

  size_t size() const { return container_.size(); } // Método para obtener el tamaño
  const Key& operator[](size_t index) const { return container_[index]; } // Operador de acceso por índice

 private:
 std::vector<Key> container_;
};

#include "dynamic_sequence.cc"