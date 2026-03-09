#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include "../lib/ant.h"
#include "../lib/tape.h"

// Gestiona la interacción entre la cinta y la hormiga, controlando
// los pasos de la simulación y la visualización conjunta.
class Simulator {
 public:
  // El constructor ahora se encarga de procesar el fichero de configuración
  Simulator(const std::string& input_file);
  ~Simulator(); // Destructor para liberar la memoria de las hormigas

  void Run(); // Ejecuta el bucle principal
  void Step(); // Evoluciona un paso todas las hormigas
  void Render() const; // Visualización por pantalla
  void SaveStateToFile(const std::string& filename) const; // Persistencia 

 private:
  Tape* tape_;
  std::vector<Ant*> ants_; // Vector de punteros para polimorfismo
  int steps_;
  
  // Lista de colores ANSI para asignar a cada hormiga 
  const std::vector<std::string> kColors = { "\033[1;31m", "\033[1;32m", "\033[1;34m", "\033[1;35m", "\033[1;36m" };
};

#endif  // SIMULATOR_H_