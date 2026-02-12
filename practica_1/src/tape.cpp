#include "../lib/tape.h"

Tape::Tape(int x, int y) : size_x_(x), size_y_(y) {
  // Inicializa el vector de vectores con valor 0 (blanco).
  color_.assign(size_y_, std::vector<int>(size_x_, 0));
}

int Tape::GetColor(int x, int y) const { return color_[y][x]; }

void Tape::SetColor(int x, int y, int color) { color_[y][x] = color; }

int Tape::get_size_x() const { return size_x_; }

int Tape::get_size_y() const { return size_y_; }

std::ostream& operator<<(std::ostream& os, const Tape& t) {
  for (const std::vector<int>& row : t.color_) {
    for (int cell : row) {
      os << (cell == 0 ? ' ' : 'x');
    }
    os << "\n";
  }
  return os;
}