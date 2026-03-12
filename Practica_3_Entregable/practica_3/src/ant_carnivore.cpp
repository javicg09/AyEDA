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
  
  if (rule == 'D') {
    orientation_ = static_cast<Orientation>((orientation_ + 1) % 4);
  } else {
    orientation_ = static_cast<Orientation>((orientation_ + 3) % 4);
  }
}

void AntCarnivore::Forward(Tape&) {
  switch (orientation_) {
    case kArriba:    x_++; y_--; break;
    case kDerecha:   x_++; y_++; break;
    case kAbajo:     x_--; y_++; break;
    case kIzquierda: x_--; y_--; break;
    default: break;
  }
}