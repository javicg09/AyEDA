#ifndef _NIF_H_
#define _NIF_H_

#include <iostream>

class NIF {
  public:
    NIF();
    NIF(const long nif);

    bool operator<(const NIF& other) const;
    bool operator>(const NIF& other) const;
    bool operator==(const NIF& other) const;

    operator long() const;

    friend std::istream& operator>>(std::istream& is, NIF& nif);
    friend std::ostream& operator<<(std::ostream& os, const NIF& nif);

  private:
    long nif_;
};

#endif