#include "../lib/libro.h"

Libro::Libro() : anyo_publicado_(0) {}

Libro:: Libro(const ISBN& isbn, const std::string& autor, const std::string& titulo, const int anyo_publicado, std::string& genero)
  : isbn_(isbn), autor_(autor), titulo_(titulo), anyo_publicado_(anyo_publicado), genero_(genero) {}

Libro::operator long() const {
  return (long)isbn_;
}

bool Libro::operator<(const Libro& other) const {
  return (long)isbn_ < (long)other.isbn_;
};
bool Libro::operator>(const Libro& other) const {
  return (long)isbn_ > (long)other.isbn_;
}
bool Libro::operator==(const Libro& other) const {
  return (long)isbn_ == (long)other.isbn_;
}

std::istream& operator>>(std::istream& is, Libro& libro) {
    std::cout << "Prefijo: ";
    is >> libro.isbn_.prefijo;
    std::cout << "Grupo: ";
    is >> libro.isbn_.grupo;
    std::cout << "Titular: ";
    is >> libro.isbn_.titular;
    std::cout << "Publicacion: ";
    is >> libro.isbn_.publicacion;
    std::cout << "Digito control: ";
    is >> libro.isbn_.digito_control;
    is.ignore();
    std::cout << "Autor: ";
    std::getline(is, libro.autor_);
    std::cout << "Titulo: ";
    std::getline(is, libro.titulo_);
    std::cout << "Año publicacion: ";
    is >> libro.anyo_publicado_;
    is.ignore();
    std::cout << "Genero: ";
    std::getline(is, libro.genero_);
    return is;
}

std::istream& leerISBN(std::istream& is, Libro& libro) {
    std::cout << "ISBN (formato XXX-X-XX-XXXXXX-X): ";
    std::string isbn;
    is >> isbn;
    
    std::stringstream ss(isbn);
    std::getline(ss, libro.isbn_.prefijo, '-');
    std::getline(ss, libro.isbn_.grupo, '-');
    std::getline(ss, libro.isbn_.titular, '-');
    std::getline(ss, libro.isbn_.publicacion, '-');
    std::getline(ss, libro.isbn_.digito_control, '-');
    
    return is;
}