#include "nif.h"

nif::nif() {
  srand(time(nullptr));
  value_ = rand() % 100000000;
}

nif& nif::operator/=(int divisor) {
  value_ /= divisor;
  return *this;
}

std::istream& operator>>(std::istream& input, nif& n) {
  long value;
  std::cout << "Introduce el valor del NIF: ";
  input >> value;
  n = nif(value);
  return input;
}