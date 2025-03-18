#pragma once

#include <cstddef>
#include "sequence.h"

// Cerrada
template<class Key>
class staticSequence : public Sequence<Key> {
 public:
  staticSequence(const unsigned size) : blockSize_(size) {emptySlots_.resize(blockSize_, true);}

  bool search(const Key& k) const override;
  bool insert(const Key& k) override;
  bool isFull() const override;

  size_t size() const { return container_.size(); } // Método para obtener el tamaño
  const Key& operator[](size_t index) const {return container_[index];} // Operador de acceso por índice

 private:
  unsigned blockSize_;
  std::vector<Key> container_;
  std::vector<bool> emptySlots_; 
};

#include "static_sequence.cc"