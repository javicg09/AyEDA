#include "../lib/nif.h"
#include <cstdlib>

NIF::NIF(){
  nif_ = rand() % 100000000;
}

NIF::NIF(const long nif){
  nif_ = nif;
}

bool NIF::operator<(const NIF& other) const{
  return this->nif_ < other.nif_;
}

bool NIF::operator>(const NIF& other) const{
  return this->nif_ > other.nif_;
}

bool NIF::operator==(const NIF& other) const{
  return this->nif_ == other.nif_;
}

NIF::operator long() const {
  return nif_;
}

std::istream& operator>>(std::istream& is, NIF& nif) {
  is >> nif.nif_;
  return is;
}

std::ostream& operator<<(std::ostream& os, const NIF& nif) {
  os << nif.nif_;
  return os;
}