#pragma once

#include "module.h"
#include "sum.h"
#include "pseudoaleatoria.h"
#include "fe_lineal.h"
#include "fe_quadratic.h"
#include "double_hashing.h"
#include "rehashing.h"
#include "nif.h"

template<class Key>
class Sequence;

template<class Key>
class staticSequence;

// Definición de la clase HashTable
template<class Key, class Container = staticSequence<Key>>
class HashTable : public Sequence<Key> {
 public:
  HashTable(unsigned int tableSize, DispersionFunction<Key>* fd, ExplorationFunction<Key>* fe, unsigned int blockSize); // Constructor para la técnica de dispersión cerrada.
  HashTable(unsigned int tableSize, DispersionFunction<Key>* fd); // Constructor para la técnica de dispersión abierta.
  ~HashTable();

  
  bool search(const Key& key) const;
  bool insert(const Key& key);
  bool isFull() const;
  void printTable() const;

 private:
  unsigned int tableSize_;
  Container** table_;
  DispersionFunction<Key>* fd_;
  ExplorationFunction<Key>* fe_;
  unsigned int blockSize_;
};

#include "hash_table.cc"