#include "../lib/tape_reflective.h"

TapeReflective::TapeReflective(int x, int y, int num_colors) : Tape(x, y, num_colors) {
    celdas_.assign(size_y_, std::vector<int>(size_x_, 0));
}

int TapeReflective::GetColor(int x, int y) const {
  if (IsInside(x, y)) {
    return celdas_[y][x];
  }
  return -1; // Señal de fuera de límites para que el simulador reaccione
}

void TapeReflective::NextColor(int x, int y) {
  if (IsInside(x, y)) {
    celdas_[y][x] = (celdas_[y][x] + 1) % num_colors_;
  }
}

void TapeReflective::SetColor(int x, int y, int color) {
  if (IsInside(x, y)) {
    celdas_[y][x] = color;
  }
}

bool TapeReflective::IsInside(int x, int y) const {
  return (x >= 0 && x < size_x_ && y >= 0 && y < size_y_);
}
