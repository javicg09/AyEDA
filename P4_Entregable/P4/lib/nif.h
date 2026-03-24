#ifndef _NIF_H_
#define _NIF_H_

class NIF {
  public:
    NIF();
    NIF(const long nif);

    bool operator<(const NIF& other) const;
    bool operator>(const NIF& other) const;
    bool operator==(const NIF& other) const;

    operator long() const;

  private:
    long nif_;
};

#endif