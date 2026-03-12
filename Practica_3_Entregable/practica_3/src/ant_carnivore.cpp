#include "../lib/ant_carnivore.h"

AntCarnivore::AntCarnivore(int x, int y, Orientation orient, const std::string& color, int life, const std::string& rules, double voracity)
  : Ant(x, y, orient, color, life), rules_(rules), voracity_(voracity) {}

void AntCarnivore::Move(Tape& tape) {
  decrement_life();
  int current_color = tape.GetColor(x_, y_);
  
  // Las carnívoras no ganan vida por el color de la celda
  Turn(current_color);
  Forward(tape);
}

std::string AntCarnivore::get_rules() const { return rules_; }
std::string AntCarnivore::get_type() const { return "C-" + rules_; }
double AntCarnivore::get_voracity() const { return voracity_; }

void AntCarnivore::Turn(int color) {
  char rule = rules_[color % rules_.length()];
  // Las orientaciones diagonales en nuestro Enum son 4, 5, 6, 7
  // kArribaDer(4), kAbajoDer(5), kAbajoIzq(6), kArribaIzq(7)
  
  int current_diag = static_cast<int>(orientation_);
  if (rule == 'D') {
    // Gira horario en las diagonales
    current_diag = (current_diag == 7) ? 4 : current_diag + 1;
  } else {
    // Gira anti-horario
    current_diag = (current_diag == 4) ? 7 : current_diag - 1;
  }
  orientation_ = static_cast<Orientation>(current_diag);
}

void AntCarnivore::Forward(Tape&) {
  switch (orientation_) {
    case kArribaDer: x_++; y_--; break;
    case kAbajoDer:  x_++; y_++; break;
    case kAbajoIzq:  x_--; y_++; break;
    case kArribaIzq: x_--; y_--; break;
    default: break;
  }
}