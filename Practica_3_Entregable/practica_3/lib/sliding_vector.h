#ifndef SLIDING_VECTOR_H_
#define SLIDING_VECTOR_H_

#include <vector>
#include <stdexcept>
#include <string>

// Excepción específica
class SVException : public std::exception {
 public:
  const char* what() const noexcept override {
    return "SVException: Índice fuera del rango del SlidingVector";
  }
};

template <typename T>
class SlidingVector {
 public:
  // Constructor: define el rango inicial
  SlidingVector(int min = 0, int max = -1) 
      : index_min_(min), index_max_(max) {
    if (max >= min) {
      data_.resize(max - min + 1);
    }
  }

  // Sobrecarga del operador [] para acceso con mapeo de índices
  T& operator[](int index) {
    if (index < index_min_ || index > index_max_) {
      throw SVException(); // Señaliza situación excepcional
    }
    // Mapeo: sv[index_min] -> data_[0]
    return data_[index - index_min_];
  }

  // Sobrecarga del operador [] (versión const)
  const T& operator[](int index) const {
    if (index < index_min_ || index > index_max_) {
      throw SVException();
    }
    return data_[index - index_min_];
  }

  // Métodos para crecimiento dinámico
  void push_back(const T& value) {
    data_.push_back(value);
    index_max_++;
  }

  void push_front(const T& value) {
    data_.insert(data_.begin(), value);
    index_min_--;
  }

  // Getters para los límites actuales
  int get_min() const { return index_min_; }
  int get_max() const { return index_max_; }

 private:
  std::vector<T> data_; // Contenedor encapsulado
  int index_min_;       // Rango inferior
  int index_max_;       // Rango superior
};

#endif