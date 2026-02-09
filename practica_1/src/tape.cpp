#include "../lib/tape.h"

Tape::Tape(int x, int y) {
  sizeX_ = x;
  sizeY_ = y;
  color_.assign(y, std::vector<int>(x, 0));
}

int Tape::getColor(int x, int y) const { return color_[y][x]; }

void Tape::setColor(int x, int y, int color) { color_[y][x] = color; }

int Tape::getsizeX() { return sizeX_; }

int Tape::gestsizeY() { return sizeY_; }

std::ostream& operator<<(std::ostream& os, const Tape& t) {
  for (const std::vector<int>& row : t.color_) {
    for (int cell : row) {
      os << (cell == 0 ? ' ' : 'x');
    }
    os << "\n";
  }
  return os;
}