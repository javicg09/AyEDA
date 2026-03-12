#include "../lib/ant.h"

Ant::Ant(int x, int y, Orientation orient, const std::string& color_code, int initial_life)
    : x_(x), y_(y), orientation_(orient), color_code_(color_code), life_time_(initial_life) {
}

int Ant::get_life() const { return life_time_; }
void Ant::set_life(int life) { life_time_ = life; }
void Ant::decrement_life() { if (life_time_ > 0) life_time_--; }
bool Ant::IsDead() const { return life_time_ <= 0; }

int Ant::get_x() const { return x_; }
int Ant::get_y() const { return y_; }

Ant::Orientation Ant::get_orientation() const { return orientation_; }

std::ostream& operator<<(std::ostream& os, const Ant& ant) {
  // Aplicamos el color ANSI de la hormiga
  os << ant.color_code_;
  
  // Representación visual según orientación
  switch (ant.orientation_) {
    case Ant::kArriba:    os << "^"; break;
    case Ant::kAbajo:     os << "v"; break;
    case Ant::kIzquierda: os << "<"; break;
    case Ant::kDerecha:   os << ">"; break;
  }
  
  // Reset de color ANSI
  os << "\033[0m";
  return os;
}