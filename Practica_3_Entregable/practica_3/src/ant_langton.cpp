#include "ant_langton.h"

AntLangton::AntLangton(int x, int y, Orientation dir, const std::string& rules, const std::string& color_ansi) 
 : Ant(x, y, dir, color_ansi), rules_(rules) {}

void AntLangton::Move(Tape& tape) {
  int current_color = tape.GetColor(x_, y_);
  
  // Determinar sentido de giro
  char action = rules_[current_color];

  if (action == 'I') {
    TurnLeft();  // Giro 90 grados izquierda
  } else if (action == 'D') {
    TurnRight(); // Giro 90 grados derecha
  }

  // Cambiar color de la celda
  tape.NextColor(x_, y_);

  // Avanzar a la siguiente celda.
  Forward();
}