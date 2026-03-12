#include "../lib/ant_herbivore.h"

AntHerbivore::AntHerbivore(int x, int y, Orientation orient, const std::string& color, int life, const std::string& rules)
    : Ant(x, y, orient, color, life), rules_(rules) {}

void AntHerbivore::Move(Tape& tape) {
  // Decrementar vida por el esfuerzo del movimiento
  decrement_life();

  // Obtener color actual y alimentarse
  int current_color = tape.GetColor(x_, y_);
  life_time_ += current_color;

  // Girar según las reglas de Gale et al.
  Turn(current_color);
  
  // Avanzar a la nueva posición
  Forward(tape);
}

std::string AntHerbivore::get_rules() const { return rules_; }
std::string AntHerbivore::get_type() const { return "H-" + rules_; }

void AntHerbivore::Turn(int color) {
  // 'D' gira a la derecha, 'I' a la izquierda
  char rule = rules_[color % rules_.length()];
  
  if (rule == 'D') {
    orientation_ = static_cast<Orientation>((orientation_ + 1) % 4);
  } else {
    orientation_ = static_cast<Orientation>((orientation_ + 3) % 4);
  }
}

void AntHerbivore::Forward(Tape&) {
  switch (orientation_) {
    case kArriba:    y_--; break;
    case kDerecha:   x_++; break;
    case kAbajo:     y_++; break;
    case kIzquierda: x_--; break;
    default: break;
  }
}