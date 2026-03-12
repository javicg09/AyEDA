#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <algorithm>

#include "tape.h"
#include "ant.h"
#include "ant_herbivore.h"
#include "ant_carnivore.h"

class Simulator {
 public:
  // El constructor recibe la cinta ya creada (polimorfismo)
  Simulator(Tape* tape);
  ~Simulator() = default;

  void AddAnt(std::unique_ptr<Ant> ant);
  void Run();
  void Step();
  void Render() const;
  
  void SaveStateToFile(const std::string& filename) const;
  bool HasLivingAnts() const { return !ants_.empty(); }

 private:
  Tape* tape_; // Puntero a la clase base Tape
  std::vector<std::unique_ptr<Ant>> ants_;

  void ApplyInteractions();
  void CleanupDeadAnts();
};

#endif