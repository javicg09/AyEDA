#include "../lib/ant.h"

Ant::Ant(int x, int y, Orientation dir) : x_(x), y_(y), dir_(dir) {}

void Ant::Move(Tape& tape) {
  int current_color = tape.GetColor(x_, y_);

  if (current_color == 0) {  // Blanca
    tape.SetColor(x_, y_, 1);
    TurnLeft();
  } else {                   // Negra
    tape.SetColor(x_, y_, 0);
    TurnRight();
  }
  Forward();
}

void Ant::TurnLeft() {
  switch (dir_) {
    case kArriba:    dir_ = kIzquierda; break;
    case kIzquierda: dir_ = kAbajo;     break;
    case kAbajo:     dir_ = kDerecha;   break;
    case kDerecha:   dir_ = kArriba;    break;
  }
}

void Ant::TurnRight() {
  switch (dir_) {
    case kArriba:    dir_ = kDerecha;   break;
    case kDerecha:   dir_ = kAbajo;     break;
    case kAbajo:     dir_ = kIzquierda; break;
    case kIzquierda: dir_ = kArriba;    break;
  }
}

void Ant::Forward() {
  if (dir_ == kArriba) y_--;
  else if (dir_ == kAbajo) y_++;
  else if (dir_ == kIzquierda) x_--;
  else if (dir_ == kDerecha) x_++;
}

int Ant::get_x() const { return x_; }
int Ant::get_y() const { return y_; }
Ant::Orientation Ant::get_orientation() const { return dir_; }

std::ostream& operator<<(std::ostream& os, const Ant& ant) {
  char icons[] = {'<', '>', '^', 'v'};
  os << icons[ant.dir_];
  return os;
}