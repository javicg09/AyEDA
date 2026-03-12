#include "../lib/tape_sliding.h"

TapeSliding::TapeSliding(int x, int y, int num_colors) 
    : Tape(x, y, num_colors), celdas_(0, y - 1) {
  // Inicializamos cada fila con el rango de columnas x
  for (int i = 0; i < y; ++i) {
    celdas_[i] = SlidingVector<int>(0, x - 1);
  }
}

int TapeSliding::GetColor(int x, int y) const {
  try {
    return celdas_[y][x];
  } catch (const SVException& e) {
    Expand(x, y);
    return 0; // Las nuevas celdas son blancas por defecto
  }
}

void TapeSliding::NextColor(int x, int y) {
  try {
    int current = celdas_[y][x];
    celdas_[y][x] = (current + 1) % num_colors_;
  } catch (const SVException& e) {
    Expand(x, y);
    celdas_[y][x] = 1 % num_colors_; // Después de expandir, ya podemos asignar
  }
}

void TapeSliding::SetColor(int x, int y, int color) {
  try {
    celdas_[y][x] = color;
  } catch (const SVException& e) {
    // Si falla el acceso, expandimos la cinta y reintentamos
    Expand(x, y);
    celdas_[y][x] = color;
  }
}

void TapeSliding::Expand(int x, int y) const {
  // Si la hormiga se sale por arriba (y < min) o abajo (y > max)
  while (y < celdas_.get_min()) {
    celdas_.push_front(SlidingVector<int>(celdas_[celdas_.get_min()][0], celdas_[celdas_.get_min()].get_max()));
    // El constructor de arriba crea una fila nueva con el mismo rango de columnas que la actual
  }
  while (y > celdas_.get_max()) {
    celdas_.push_back(SlidingVector<int>(celdas_[celdas_.get_max()].get_min(), celdas_[celdas_.get_max()].get_max()));
  }

  // Si se sale por la izquierda (x < min) o derecha (x > max) en todas las filas
  for (int i = celdas_.get_min(); i <= celdas_.get_max(); ++i) {
    while (x < celdas_[i].get_min()) celdas_[i].push_front(0);
    while (x > celdas_[i].get_max()) celdas_[i].push_back(0);
  }
}