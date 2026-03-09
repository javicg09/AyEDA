#ifndef ANT_H_
#define ANT_H_

#include <iostream>
#include "../lib/tape.h"

// Representa a la hormiga. Es responsable de su posición, orientación,
// movimiento según las reglas y visualización propia.
class Ant {
 public:
  // Enum de valores de orientación de la hormiga
  enum Orientation { kIzquierda = 0, kDerecha = 1, kArriba = 2, kAbajo = 3 };

  // Constructor
  Ant(int x, int y, Orientation dir);

  // Ejecuta la lógica de giro, cambio de color y avance sobre la cinta.
  void Move(Tape& tape);

  // Lógica de giros
  void TurnLeft();
  void TurnRight();
  void Forward();

  // Getters
  int get_x() const;
  int get_y() const;
  Orientation get_orientation() const;

  // Sobrecarga para mostrar la hormiga según su dirección: <, >, ^, v.
  friend std::ostream& operator<<(std::ostream& os, const Ant& ant);

 private:
  int x_;
  int y_;
  Orientation dir_;
};

#endif  // ANT_H_