#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include "../lib/ant.h"
#include "../lib/tape.h"

// Gestiona la interacción entre la cinta y la hormiga, controlando
// los pasos de la simulación y la visualización conjunta.
class Simulator {
 public:
  // Contructor
  Simulator(int sx, int sy, int ax, int ay, Ant::Orientation adir);

  // Ejecuta un paso completo: movimiento, actualización y dibujo.
  void Step();
  
  // Indica si la hormiga ha salido de los límites de la cinta.
  bool IsFinished() const;

  // Permite añadir celdas negras iniciales desde el archivo.
  void SetInitialBlackCell(int x, int y);

  // Dibuja el estado actual de la cinta con la hormiga superpuesta.
  void Render() const;

  // Guarda el estado actual de la simulación en un fichero con el formato requerido.
  void SaveStateToFile(const std::string& filename) const;

 private:
  Tape tape_;
  Ant ant_;
  int steps_;
};

#endif  // SIMULATOR_H_