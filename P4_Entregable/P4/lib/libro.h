#ifndef _LIBRO_H_
#define _LIBRO_H_

#include <iostream>
#include <string>

struct ISBN {
  std::string prefijo;       // 978 o 979
  std::string grupo;         // 3
  std::string titular;       // 16
  std::string publicacion;   // 148410
  std::string digito_control;// 0
  operator long() const {
    std::string concat = prefijo + grupo + titular + publicacion + digito_control;
    return std::stol(concat);
  }
};

class Libro {
  public:
    Libro();
    Libro(const ISBN& isbn, const std::string& autor, const std::string& titulo, const int anyo_publicado, std::string& genero);

    operator long() const;

    bool operator<(const Libro& other) const;
    bool operator>(const Libro& other) const;
    bool operator==(const Libro& other) const;

    friend std::istream& operator>>(std::istream& is, Libro& libro);

  private:
    ISBN isbn_;
    std::string autor_;
    std::string titulo_;
    int anyo_publicado_;
    std::string genero_;
};

#endif