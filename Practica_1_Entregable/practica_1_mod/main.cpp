#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../lib/simulator.h"

// Función auxiliar para cargar los datos del fichero.
bool LoadConfig(const std::string& filename, int& sx, int& sy, int& ax, int& ay, int& adir, std::vector<std::pair<int, int>>& black_cells) {
  std::ifstream file(filename);
  if (!file.is_open()) return false;

  // Línea 1: Tamaño de la cinta.
  if (!(file >> sx >> sy)) return false;

  // Línea 2: Posición inicial y orientación de la hormiga.
  if (!(file >> ax >> ay >> adir)) return false;

  // Línea 3..n: Posiciones de las celdas negras.
  int bx, by;
  while (file >> bx >> by) {
    black_cells.push_back({bx, by});
  }

  return true;
}

int main(int argc, char* argv[]) {
  // Verificación de argumentos de línea de comandos
  if (argc < 2) {
    std::cerr << "Uso: " << argv[0] << " <fichero_configuracion.txt>" << std::endl;
    return 1;
  }

  int sx, sy, ax, ay, adir;
  std::vector<std::pair<int, int>> initial_blacks;

  if (!LoadConfig(argv[1], sx, sy, ax, ay, adir, initial_blacks)) {
    std::cerr << "Error al leer el fichero de configuracion." << std::endl;
    return 1;
  }

  // Creación del simulador con los datos leídos
  Simulator sim(sx, sy, ax, ay, static_cast<Ant::Orientation>(adir));

  // Añadir las celdas negras iniciales leídas del fichero
  for (const std::pair<int, int> &pos : initial_blacks) {
    sim.SetInitialBlackCell(pos.first, pos.second);
  }

  std::cout << "Simulacion iniciada. Presione Enter para cada paso (o 'q' para salir)." << std::endl;

  // Bucle principal de la simulación
  std::string input;
  while (!sim.IsFinished()) {
    sim.Step();
    std::getline(std::cin, input);
    if (input == "q") break;
  }

  if (sim.IsFinished()) {
    std::cout << "La hormiga ha alcanzado el limite de la cinta." << std::endl;
  }

  // Lógica de salvaguarda del estado final 
  std::cout << "¿Desea salvar el estado de la simulacion? (s/n): ";
  std::getline(std::cin, input);
  if (input == "s" || input == "S") {
    std::cout << "Introduce el nombre del archivo de salida: ";
    std::string out_filename;
    std::getline(std::cin, out_filename);
  
    // Llamada al método void
    sim.SaveStateToFile(out_filename);
  }

  std::cout << "Simulacion terminada." << std::endl;

  return 0;
}