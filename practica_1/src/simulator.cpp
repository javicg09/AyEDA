#include "../lib/simulator.h"
#include <iostream>
#include <fstream>

Simulator::Simulator(int sx, int sy, int ax, int ay, Ant::Orientation adir)
    : tape_(sx, sy), ant_(ax, ay, adir), steps_(0) {}

void Simulator::SetInitialBlackCell(int x, int y) {
  tape_.SetColor(x, y, 1);
}

bool Simulator::IsFinished() const {
  return (ant_.get_x() < 0 || ant_.get_x() >= tape_.get_size_x() ||
          ant_.get_y() < 0 || ant_.get_y() >= tape_.get_size_y());
}

void Simulator::Step() {
  if (!IsFinished()) {
    ant_.Move(tape_);
    steps_++;
    Render();
  }
}

void Simulator::Render() const {
  std::cout << "Paso numero: " << steps_ << std::endl;
  for (int i = 0; i < tape_.get_size_y(); ++i) {
    for (int j = 0; j < tape_.get_size_x(); ++j) {
      if (j == ant_.get_x() && i == ant_.get_y()) {
        std::cout << ant_;
      } else {
        std::cout << (tape_.GetColor(j, i) == 0 ? ' ' : 'x');
      }
    }
    std::cout << "\n";
  }
  std::cout << "--------------------------------" << std::endl;
}

void Simulator::SaveStateToFile(const std::string& filename) const {
  std::ofstream out_file(filename);
  if (!out_file.is_open()) {
    std::cerr << "Error: No se pudo crear el archivo " << filename << std::endl;
    return;
  }

  // Línea 1: Tamaño de la cinta [cite: 58]
  out_file << tape_.get_size_x() << " " << tape_.get_size_y() << "\n";
  
  // Línea 2: Posición inicial y orientación de la hormiga [cite: 59]
  out_file << ant_.get_x() << " " << ant_.get_y() << " " 
           << static_cast<int>(ant_.get_orientation()) << "\n";

  // Línea 3..n: Posiciones de las celdas negras (valor binario 1) [cite: 60]
  for (int i = 0; i < tape_.get_size_y(); ++i) {
    for (int j = 0; j < tape_.get_size_x(); ++j) {
      if (tape_.GetColor(j, i) == 1) {
        out_file << j << " " << i << "\n";
      }
    }
  }
  
  std::cout << "Estado guardado exitosamente en: " << filename << std::endl;
}