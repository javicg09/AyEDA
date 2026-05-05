#ifndef NIF_H
#define NIF_H

#include <cstdlib>
#include <iostream>

class NIF {
 public:
  NIF() : nif_(static_cast<long>(rand()) % 100000000L) {}
  NIF(long nif) : nif_(nif < 0 ? -nif % 100000000L : nif % 100000000L) {}

  bool operator<(const NIF& o) const { return nif_ < o.nif_; }
  bool operator>(const NIF& o) const { return nif_ > o.nif_; }
  bool operator==(const NIF& o) const { return nif_ == o.nif_; }

  operator long() const { return nif_; }

  friend std::ostream& operator<<(std::ostream& os, const NIF& nif) {
    static const char letras[] = "TRWAGMYFPDXBNJZSQVHLCKE";
    os << nif.nif_ << letras[nif.nif_ % 23];
    return os;
  }

  friend std::istream& operator>>(std::istream& is, NIF& nif) {
    is >> nif.nif_;
    return is;
  }

 private:
  long nif_;
};

#endif
