#include "tape_periodic.h"

TapePeriodic::TapePeriodic(int x, int y, int num_colors) : Tape(x, y, num_colors) {
  celdas_.assign(size_y_, std::vector<int>(size_x_, 0));
}

int TapePeriodic::GetColor(int x, int y) const {
  return celdas_[WrapY(y)][WrapX(x)];
}

void TapePeriodic::NextColor(int x, int y) {
  int& celda = celdas_[WrapY(y)][WrapX(x)];
  celda = (celda + 1) % num_colors_;
}

int TapePeriodic::WrapX(int x) const {
  return (x % size_x_ + size_x_) % size_x_; 
}

int TapePeriodic::WrapY(int y) const {
  return (y % size_y_ + size_y_) % size_y_; 
}