#ifndef _STATIC_SEQUENCE_H_
#define _STATIC_SEQUENCE_H_

#include "sequence.h"

template<class Key>
class StaticSequence : public Sequence<Key> {
  public:
    StaticSequence(const unsigned size) : size_(size) {
      data_ = new Key[size_];
    }

    bool search(const Key& k) const override {
      for (unsigned i = 0; i < size_; i++) {
        if (data_[i] == k) return true;
      }
      return false;
    }

    bool insert(const Key& k) override {
      if (isFull()) return false;
      data_[size_] = k;
      size_++;
      return true;
    }

    bool isFull() const {
      return size_ == blockSize_;
    }

    Key operator[](const unsigned i) const override {
      return data_[i];
    }

    Key& operator[](const unsigned i) override {
      return data_[i];
    }

  private:
    Key* data_;
    unsigned size_;
};

#endif