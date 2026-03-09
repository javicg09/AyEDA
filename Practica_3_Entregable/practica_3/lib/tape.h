#ifndef TAPE_H_
#define TAPE_H_

#include <iostream>
#include <vector>

// Aunque usamos int internamente para n colores, el enum ayuda a la legibilidad.
enum class Color : int { kColor0 = 0, kColor1 = 1, kColor2 = 2, kColor3 = 3 };

// Representa la cinta bidimensional de celdas sobre la que se mueve la hormiga.
// Se encarga de almacenar los colores y de la visualización.
class Tape {
 public:
  // Inicializa la cinta con tamaño fijo, por defecto todas blancas (0).
  Tape(int x, int y, int num_colors);

  // Consulta el color de una celda (0 para blanca, 1 para negra).
  int GetColor(int x, int y) const;
  
  // Modifica el color de una celda.
  void SetColor(int x, int y, int color);

  // Incrementa el color de la celda de forma cíclica (0 -> 1 -> ... -> n-1 -> 0).
  void NextColor(int x, int y);

  int get_size_x() const;
  int get_size_y() const;
  int get_num_colors() const;

  // Sobrecarga para mostrar la cinta: blancas con ' ' y negras con 'x'.
  friend std::ostream& operator<<(std::ostream& os, const Tape& tape);

 private:
  int size_x_;
  int size_y_;
  int num_colors_;
  std::vector<std::vector<int>> color_;
};

#endif  // TAPE_H_