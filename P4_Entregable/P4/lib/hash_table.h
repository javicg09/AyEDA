#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include "dispersion_function.h"
#include "exploration_function.h"
#include "static_sequence.h"
#include "dynamic_sequence.h"

// HashTable Cerrada, se coge por defecto
template<class Key, class Container = StaticSequence<Key>>
class HashTable : public Sequence<Key> {
  public:
    HashTable(unsigned tableSize, DispersionFunction<Key>& fd, ExplorationFunction<Key>& fe, unsigned blockSize)
    : tableSize_(tableSize), blockSize_(blockSize), fd_(fd), fe_(fe) {
        // crear el array y sus posiciones
        table_ = new Container*[tableSize_];
        for (unsigned i = 0; i < tableSize_; i++) {
            table_[i] = new Container(blockSize_);
        }
    }

    bool search(const Key& k) const override {
      unsigned pos = fd_(k) % tableSize_;      // posición inicial
        
      if (table_[pos]->search(k)) return true; // Comprobar si está en la posicion inicial
        
      for (unsigned i = 1; i < tableSize_; i++) {  // explora otras posiciones
          unsigned newPos = (pos + fe_(k, i)) % tableSize_;
          if (table_[newPos]->search(k)) return true;
      }
      return false;
    }

    bool insert(const Key& k) override {
      unsigned pos = fd_(k) % tableSize_;
      if(!table_[pos]->isFull()){
        table_[pos]->insert(k);
        return true;
      }
      for (unsigned i = 1; i < tableSize_; i++) {
          unsigned newPos = (pos + fe_(k, i)) % tableSize_;
          if (!table_[newPos]->isFull()) {
            table_[newPos]->insert(k);
            return true;
          }
      }
      return false;
    };

  private:
    unsigned tableSize_;
    unsigned blockSize_;
    Container** table_;  // array de punteros a Container
    DispersionFunction<Key>& fd_;
    ExplorationFunction<Key>& fe_;
};

// HashTable Abierta
template<class Key>
class HashTable<Key, DynamicSequence<Key>> : public Sequence<Key> {
  public:
    HashTable(unsigned tableSize, DispersionFunction<Key>& fd)
      : tableSize_(tableSize), fd_(fd) {
        table_ = new DynamicSequence<Key>*[tableSize_];
        for (unsigned i = 0; i < tableSize_; i++) {
            table_[i] = new DynamicSequence<Key>();
        }
    };

    bool search(const Key& k) const override {
      unsigned pos = fd_(k) % tableSize_;
      return table_[pos]->search(k);
    };

    bool insert(const Key& k) override {
      unsigned pos = fd_(k) % tableSize_;
      return table_[pos]->insert(k);
    }

  private:
    unsigned tableSize_;
    DynamicSequence<Key>** table_;
    DispersionFunction<Key>& fd_;
};
#endif