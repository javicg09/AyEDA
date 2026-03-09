#include "lib/simulator.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  // Validación de argumentos de línea de comandos 
  if (argc < 2) {
    std::cerr << "Uso: " << argv[0] << " <fichero_inicial.txt>" << std::endl;
    return 1;
  }

  try {
    // Inicialización del simulador con el fichero 
    Simulator simulator(argv[1]);
    std::string input;

    std::cout << "Presione ENTER para el siguiente paso, 'q' para salir." << std::endl;

    // Bucle de evolución [cite: 36]
    while (true) {
      simulator.Render();
      std::getline(std::cin, input);
      if (input == "q") break;
      simulator.Step();
    }

    // Pregunta de salvado antes de terminar 
    std::cout << "¿Desea salvar el estado de la simulacion? (s/n): ";
    std::getline(std::cin, input);
    if (input == "s" || input == "S") {
      std::string out_name;
      std::cout << "Nombre del archivo: ";
      std::getline(std::cin, out_name);
      simulator.SaveStateToFile(out_name);
    }

  } catch (const std::exception& e) {
    std::cerr << "Error crítico: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}