#include "../lib/simulator.h"
#include "../lib/ant_langton.h"
#include <fstream>
#include <sstream>

Simulator::Simulator(const std::string& input_file) : steps_(0) {
  std::ifstream file(input_file);
  if (!file.is_open()) {
    throw std::runtime_error("Error: No se pudo abrir el fichero: " + input_file);
  }

  // Línea 1: Tamaño y número de colores
  int sx, sy, n_colors;
  file >> sx >> sy >> n_colors;
  tape_ = new Tape(sx, sy, n_colors);

  // Línea 2: Hormigas
  std::string line;
  std::getline(file, line); // Limpiar buffer
  std::getline(file, line);
  std::stringstream ss(line);
  std::string segment;

  int color_idx = 0;
  while (std::getline(ss, segment, ';')) { // Separadas por ';' 
    std::stringstream ant_data(segment);
    std::string rules;
    int x, y;
    char dir_char;
    ant_data >> rules >> x >> y >> dir_char;

    // Convertir char a enum Orientation
    Ant::Orientation orient;
    if (dir_char == '^') orient = Ant::kArriba;
    else if (dir_char == 'v') orient = Ant::kAbajo;
    else if (dir_char == '<') orient = Ant::kIzquierda;
    else orient = Ant::kDerecha;

    // Creamos la hormiga específica (Polimorfismo)
    ants_.push_back(new AntLangton(x, y, orient, rules, kColors[color_idx % kColors.size()]));
    color_idx++;
  }

  // Línea 3..n: Celdas no blancas
  int cx, cy, c_val;
  while (file >> cx >> cy >> c_val) {
    tape_->SetColor(cx, cy, c_val);
  }
  file.close();
}

// El método Run gestiona el bucle principal de la simulación
void Simulator::Run() {
  std::string input;
  std::cout << "Simulación iniciada. Presione ENTER para avanzar, 'q' para detenerse.\n";
  
  while (true) {
    Render();
    std::getline(std::cin, input);
    if (input == "q") break;
    Step();
  }
}

void Simulator::Step() {
  // Todas las hormigas realizan su movimiento en la cinta común
  for (Ant* ant : ants_) {
    // Comprobar límites antes de mover
    if (ant->get_x() >= 0 && ant->get_x() < tape_->get_size_x() &&
        ant->get_y() >= 0 && ant->get_y() < tape_->get_size_y()) {
      ant->Move(*tape_); // Llamada polimórfica
    }
  }
  steps_++;
}

void Simulator::Render() const {
  std::cout << "\033[H\033[2JStep: " << steps_ << "\n";
  for (int i = 0; i < tape_->get_size_y(); ++i) {
    for (int j = 0; j < tape_->get_size_x(); ++j) {
      bool ant_present = false;
      for (Ant* ant : ants_) {
        if (ant->get_x() == j && ant->get_y() == i) {
          std::cout << *ant; // Dibuja la hormiga con su color
          ant_present = true;
          break;
        }
      }
      if (!ant_present) {
        int color = tape_->GetColor(j, i);
        if (color == 0) std::cout << " "; 
        else std::cout << color; // Muestra el número de color
      }
    }
    std::cout << "\n";
  }
}

// Asegúrate de incluir el nombre de la clase Simulator:: 
// y el const al final de la firma.
void Simulator::SaveStateToFile(const std::string& filename) const {
  std::ofstream out_file(filename);
  if (!out_file.is_open()) return;

  // Línea 1: Tamaño y colores [cite: 38, 41]
  out_file << tape_->get_size_x() << " " << tape_->get_size_y() << " " 
           << tape_->get_num_colors() << "\n";

  // Línea 2: Hormigas separadas por ';' [cite: 39, 42]
  for (size_t i = 0; i < ants_.size(); ++i) {
    char dir_char;
    switch (ants_[i]->get_orientation()) {
      case Ant::kArriba:    dir_char = '^'; break;
      case Ant::kAbajo:     dir_char = 'v'; break;
      case Ant::kIzquierda: dir_char = '<'; break;
      case Ant::kDerecha:   dir_char = '>'; break;
    }
    out_file << ants_[i]->get_rules() << " " << ants_[i]->get_x() 
             << " " << ants_[i]->get_y() << " " << dir_char;
    if (i < ants_.size() - 1) out_file << " ; ";
  }
  out_file << "\n";

  // Línea 3+: Celdas no blancas [cite: 39, 43]
  for (int y = 0; y < tape_->get_size_y(); ++y) {
    for (int x = 0; x < tape_->get_size_x(); ++x) {
      if (tape_->GetColor(x, y) != 0) {
        out_file << x << " " << y << " " << tape_->GetColor(x, y) << "\n";
      }
    }
  }
}

Simulator::~Simulator() {
  for (Ant* ant : ants_) delete ant;
  delete tape_;
}