#include <list>
#include "sequence.h"

template<class Key>
class DynamicSequence : public Sequence<Key> {
  public:
    bool search(const Key& k) const override {
      for (const Key& elem : list_) {
          if (elem == k) return true;
      }
      return false;
    }

    bool insert(const Key& k) override {
      list_.push_back(k);
      return true;
    }

  private:
    std::list<Key> list_;
};