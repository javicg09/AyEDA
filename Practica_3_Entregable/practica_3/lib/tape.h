#ifndef TAPE_H_
#define TAPE_H_

#include <iostream>
#include <vector>

// Representa la clase base de la cinta
class Tape {
 public:
  // Inicializa la cinta con tamaño fijo, por defecto todas blancas (0).
  Tape(int x, int y, int num_colors);
  virtual ~Tape() {}

  // Consulta el color de una celda (0 para blanca, 1 para negra).
  virtual int GetColor(int x, int y) const = 0;

  // Incrementa el color de la celda de forma cíclica (0 -> 1 -> ... -> n-1 -> 0).
  virtual void NextColor(int x, int y) = 0;

  int get_size_x() const;
  int get_size_y() const;
  int get_num_colors() const;

 protected:
  int size_x_;
  int size_y_;
  int num_colors_;
};

#endif  // TAPE_H_