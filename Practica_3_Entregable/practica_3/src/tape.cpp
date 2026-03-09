#include "../lib/tape.h"

Tape::Tape(int x, int y, int num_colors) : size_x_(x), size_y_(y), num_colors_(num_colors) {}

int Tape::get_size_x() const { return size_x_; }

int Tape::get_size_y() const { return size_y_; }

int Tape::get_num_colors() const { return num_colors_; }