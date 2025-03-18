#ifndef HASH_TABLE_CC
#define HASH_TABLE_CC

#include "static_sequence.h"
#include "dynamic_sequence.h"
#include "hash_table.h"

// Implementación del constructor para la técnica de dispersión cerrada.
template<class Key, class Container>
HashTable<Key, Container>::HashTable(unsigned int tableSize, DispersionFunction<Key>* fd, ExplorationFunction<Key>* fe, unsigned int blockSize) : tableSize_(tableSize), fd_(fd), fe_(fe), blockSize_(blockSize) {
  table_ = new Container*[tableSize_];
  for (unsigned int i = 0; i < tableSize_; i++) {
    table_[i] = new Container(blockSize_);
  }
}

// Implementación del constructor para la técnica de dispersión abierta.
template<class Key, class Container> HashTable<Key, Container>::HashTable(unsigned int tableSize, DispersionFunction<Key>* fd) : tableSize_(tableSize), fd_(fd), fe_(nullptr), blockSize_(0) {
  table_ = new Container*[tableSize_];
  for (unsigned int i = 0; i < tableSize_; i++) {
    table_[i] = new dynamicSequence<Key>(); // Utilizamos dynamicSequence como Container
  }
}

// Implementación del destructor
template<class Key, class Container> HashTable<Key, Container>::~HashTable() {
  for (unsigned int i = 0; i < tableSize_; i++) {
    delete table_[i];
  }
  delete[] table_;
}

template<class Key, class Container>
bool HashTable<Key, Container>::search(const Key& k) const {
  unsigned fd_result = fd_->operator()(k);
  Sequence<Key>* sequence = table_[fd_result];
  if (sequence->search(k)) {
    return true;
  }

  if (fe_ != nullptr) {
    for (int i = 1; i < tableSize_; i++) {
      sequence = table_[fe_->operator()(k, i)];
      if (sequence == nullptr) {
        continue;
      }
      if (sequence->search(k)) {
        std::cout << "Encontrado" << std::endl;
        return true;
      }
    }
  }
  return false;
}

template<class Key, class Container>
bool HashTable<Key, Container>::insert(const Key& k) {
  unsigned fd_result = fd_->operator()(k);
  Sequence<Key>* sequence = table_[fd_result];
  if (sequence->search(k)) {
    return false;
  }

  if (!sequence->isFull()) {
    sequence->insert(k);
    return true;
  }

  if (fe_ != nullptr) {
    for (int i = 1; i < tableSize_; ++i) {
      sequence = table_[fe_->operator()(k, i)];
      if (sequence != nullptr && !sequence->isFull() && !sequence->search(k)) {
        sequence->insert(k);
        std::cout << "Insertado" << std::endl;
        return true;
      }
    }
  }
  return false;
}

template<class Key, class Container>
bool HashTable<Key, Container>::isFull() const {
  for (int i = 0; i < tableSize_; i++) {
    Sequence<Key>* sequence = table_[i];
    if (!sequence->isFull()) {
      return false; 
    }
  }
  return true;
}

template<class Key, class Container>
void HashTable<Key, Container>::printTable() const {
  for (unsigned int i = 0; i < tableSize_; ++i) {
    if (table_[i] != nullptr) {
      std::cout << "Slot " << i << ": ";
      for (unsigned int j = 0; j < table_[i]->size(); ++j) {
        std::cout << (*table_[i])[j] << " ";
      }
      std::cout << std::endl;
    }
  }
}

#endif