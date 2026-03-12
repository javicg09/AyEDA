#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

#include "lib/simulator.h"
#include "lib/tape_periodic.h"
#include "lib/tape_reflective.h"
#include "lib/tape_sliding.h"
#include "lib/ant_herbivore.h"
#include "lib/ant_carnivore.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Uso: " << argv[0] << " <fichero_configuracion>\n";
    return 1;
  }

  std::ifstream config_file(argv[1]);
  if (!config_file.is_open()) {
    std::cerr << "Error al abrir el fichero de configuración.\n";
    return 1;
  }

  // Lectura de la cinta
  int size_x, size_y, num_colors;
  config_file >> size_x >> size_y >> num_colors;

  std::cout << "Seleccione el tipo de frontera:\n";
  std::cout << "1. Periódica\n2. Reflectora\n3. Deslizante (Infinita)\n> ";
  int option;
  std::cin >> option;
  std::cin.ignore(); // Limpiar el buffer

  Tape* tape = nullptr;
  switch (option) {
    case 1: tape = new TapePeriodic(size_x, size_y, num_colors); break;
    case 2: tape = new TapeReflective(size_x, size_y, num_colors); break;
    case 3: tape = new TapeSliding(size_x, size_y, num_colors); break;
    default:
      std::cerr << "Opción inválida.\n";
      return 1;
  }

  Simulator sim(tape);

  // Hormigas
  std::string line;
  std::getline(config_file, line); // Consumir salto de línea anterior
  std::getline(config_file, line); // Leer línea de hormigas

  std::stringstream ss(line);
  std::string ant_data;
  
 // Las hormigas vienen separadas por ';'
  while (std::getline(ss, ant_data, ';')) {
    std::stringstream ant_ss(ant_data);
    std::string type_rules, dir_str;
    int x, y;

    ant_ss >> type_rules >> x >> y >> dir_str;

    // Determinar orientación inicial
    Ant::Orientation orient;
    if (dir_str == "^")  orient = Ant::kArriba;
    else if (dir_str == ">")  orient = Ant::kDerecha;
    else if (dir_str == "v")  orient = Ant::kAbajo;
    else if (dir_str == "<")  orient = Ant::kIzquierda;
    else orient = Ant::kArriba;
    // Vida inicial y Voracidad
    int initial_life = 100;
    
    if (type_rules.substr(0, 2) == "H-") {
      std::string rules = type_rules.substr(2);
      sim.AddAnt(std::make_unique<AntHerbivore>(x, y, orient, "\033[32m", initial_life, rules));
    } 
    else if (type_rules.substr(0, 2) == "C-") {
      std::string rules = type_rules.substr(2);
      double voracity = 0.2; // 20% de robo de vida
      sim.AddAnt(std::make_unique<AntCarnivore>(x, y, orient, "\033[31m", initial_life, rules, voracity));
    }
  }

  // Lectura de celdas con colores
  int cx, cy, c_color;
  while (config_file >> cx >> cy >> c_color) {
    tape->SetColor(cx, cy, c_color);
  }

  // Ejecucion
  sim.Run();

  // Guardado final
  std::cout << "¿Desea guardar el estado de la simulación? (s/n): ";
  char save;
  std::cin >> save;
  if (save == 's' || save == 'S') {
    std::string filename;
    std::cout << "Nombre del archivo: ";
    std::cin >> filename;
    sim.SaveStateToFile(filename);
  }

  delete tape; // Limpiar memoria de la cinta
  return 0;
}