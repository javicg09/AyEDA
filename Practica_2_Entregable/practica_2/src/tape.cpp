#include "../lib/tape.h"

Tape::Tape(int x, int y, int num_colors) : size_x_(x), size_y_(y), num_colors_(num_colors) {
  // Inicializa el vector de vectores con valor 0 (blanco).
  color_.assign(size_y_, std::vector<int>(size_x_, 0));
}

int Tape::GetColor(int x, int y) const { return color_[y][x]; }

void Tape::SetColor(int x, int y, int color) { color_[y][x] = color; }

void Tape::NextColor(int x, int y) {
  if (y >= 0 && y < size_y_ && x >= 0 && x < size_x_) {
    // Incremento cíclico: (color + 1) MOD n.
    color_[y][x] = (color_[y][x] + 1) % num_colors_;
  }
}

int Tape::get_size_x() const { return size_x_; }

int Tape::get_size_y() const { return size_y_; }

int Tape::get_num_colors() const { return num_colors_; }

std::ostream& operator<<(std::ostream& os, const Tape& t) {
  for (const std::vector<int>& row : t.color_) {
    for (int cell : row) {
      os << (cell == 0 ? '0' : '1');
    }
    os << "\n";
  }
  return os;
}