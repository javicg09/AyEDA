#include "../lib/simulator.h"
#include <fstream>
#include <iostream>

Simulator::Simulator(Tape* tape) : tape_(tape) {}

void Simulator::AddAnt(std::unique_ptr<Ant> ant) {
  ants_.push_back(std::move(ant));
}

void Simulator::Run() {
  std::string input;
  std::cout << "Simulación iniciada. Presione ENTER para avanzar, 'q' para salir.\n";
  
  while (HasLivingAnts()) {
    Render();
    std::getline(std::cin, input);
    if (input == "q") break;
    Step();
  }

  if (!HasLivingAnts()) {
    std::cout << "Simulación finalizada: No quedan hormigas vivas.\n";
  }
}

void Simulator::Step() {
  for (auto& ant : ants_) {
    if (!ant->IsDead()) {
      // Cambiamos el color de la celda
      tape_->NextColor(ant->get_x(), ant->get_y());
      
      // la hormiga consulta el color, gira y se mueve
      ant->Move(*tape_);
    }
  }

  ApplyInteractions();
  CleanupDeadAnts();
}

void Simulator::ApplyInteractions() {
  for (size_t i = 0; i < ants_.size(); ++i) {
    for (size_t j = 0; j < ants_.size(); ++j) {
      if (i == j) continue; // No interactúa consigo misma

      // Si coinciden en la misma posición
      if (ants_[i]->get_x() == ants_[j]->get_x() && 
          ants_[i]->get_y() == ants_[j]->get_y()) {
        
        // Intentar ver si la hormiga i es carnívora usando dynamic_cast
        AntCarnivore* predator = dynamic_cast<AntCarnivore*>(ants_[i].get());
        
        if (predator && !ants_[j]->IsDead()) {
          int victim_life = ants_[j]->get_life();
          int stolen_life = static_cast<int>(victim_life * predator->get_voracity());
          
          // Transferencia de vida
          ants_[j]->set_life(victim_life - stolen_life);
          predator->set_life(predator->get_life() + stolen_life);
          
          std::cout << "[Interacción] Carnívora robó " << stolen_life << " de vida.\n";
        }
      }
    }
  }
}

void Simulator::CleanupDeadAnts() {
  // Elimina del vector aquellas hormigas cuyo IsDead() sea true
  ants_.erase(
    std::remove_if(ants_.begin(), ants_.end(),
      [](const std::unique_ptr<Ant>& ant) {
        return ant->IsDead();
      }),
    ants_.end()
  );
}

void Simulator::Render() const {
  // Limpiar pantalla
  std::cout << "\033[2J\033[1;1H"; 

  // Dibujar la cinta
  for (int y = 0; y < tape_->get_size_y(); ++y) {
    for (int x = 0; x < tape_->get_size_x(); ++x) {
      bool ant_present = false;
      for (const auto& ant : ants_) {
        if (ant->get_x() == x && ant->get_y() == y) {
          std::cout << *ant; // Llama al operador << de Ant
          ant_present = true;
          break;
        }
      }
      if (!ant_present) {
        int color = tape_->GetColor(x, y);
        if (color == 0) std::cout << ".";
        else std::cout << color;
      }
      std::cout << " ";
    }
    std::cout << "\n";
  }

  // Mostrar información detallada de cada hormiga (Requisito Práctica 3)
  std::cout << "\n--- Hormigas Vivas: " << ants_.size() << " ---\n";
  for (const auto& ant : ants_) {
    std::cout << ant->get_type() << ": (" << ant->get_x() << "," 
              << ant->get_y() << ") Vida: " << ant->get_life() << "\n";
  }
}

void Simulator::SaveStateToFile(const std::string& filename) const {
  std::ofstream out(filename);
  if (!out.is_open()) return;

  // Línea 1: Dimensiones y colores
  out << tape_->get_size_x() << " " << tape_->get_size_y() << " " 
      << tape_->get_num_colors() << "\n";

  // Línea 2: Hormigas
  for (size_t i = 0; i < ants_.size(); ++i) {
    // Usamos el método virtual polimórfico
    int orient_int = ants_[i]->get_orientation();
    
    // Mapeo local para el guardado (opcional, podrías tener un método to_char() en la hormiga)
    char dir_char;
    // Si es herbívora (0-3), si es carnívora (4-7)
    if (orient_int < 4) {
      const char* map = "^>v<";
      dir_char = map[orient_int];
    } else {
      // Símbolos para diagonales
      const char map[] = {'/', '\\', '/', '\\'}; 
      dir_char = map[orient_int - 4];
    }
    
    out << ants_[i]->get_type() << " " << ants_[i]->get_x() << " " 
        << ants_[i]->get_y() << " " << dir_char;
    
    if (i < ants_.size() - 1) out << " ; ";
  }
  out << "\n";

  // Línea 3: Celdas no blancas
  for (int y = 0; y < tape_->get_size_y(); ++y) {
    for (int x = 0; x < tape_->get_size_x(); ++x) {
      if (tape_->GetColor(x, y) != 0) {
        out << x << " " << y << " " << tape_->GetColor(x, y) << "\n";
      }
    }
  }
  std::cout << "Estado guardado en: " << filename << "\n";
}