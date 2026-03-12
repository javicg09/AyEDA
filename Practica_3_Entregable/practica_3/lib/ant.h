#ifndef ANT_H_
#define ANT_H_

#include <string>
#include <iostream>
#include "tape.h"

class Ant {
 public:
  // Orientaciones ortogonales (H) y diagonales (C)
  enum Orientation { kArriba, kDerecha, kAbajo, kIzquierda };

  Ant(int x, int y, Orientation orient, const std::string& color_code, int initial_life);
  virtual ~Ant() {}

  // Métodos virtuales puros para la jerarquía
  virtual void Move(Tape& tape) = 0;
  virtual std::string get_rules() const = 0;
  virtual std::string get_type() const = 0;

  // Gestión de vida 
  int get_life() const;
  void set_life(int life);
  void decrement_life();
  bool IsDead() const;

  // Getters de posición y estado
  int get_x() const;
  int get_y() const;
  Orientation get_orientation() const;

  // Sobrecarga para mostrar info: tipo, posición y vida 
  friend std::ostream& operator<<(std::ostream& os, const Ant& ant);

 protected:
  int x_, y_;
  Orientation orientation_;
  std::string color_code_;
  int life_time_; // Atributo LifeTime
};

#endif