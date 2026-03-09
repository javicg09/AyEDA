#ifndef ANT_LANGTON_H_
#define ANT_LANGTON_H_

#include "ant.h"

// Implementa una hormiga definida por una secuencia de giros
class AntLangton : public Ant {
 public:
  AntLangton(int x, int y, Orientation dir, const std::string& rules, const std::string& color_ansi);

  // Implementación de las reglas generalizadas de giro
  void Move(Tape& tape) override;
  std::string get_rules() const override { return rules_; }

 private:
  std::string rules_; // Cadena de 'D' e 'I'
};

#endif  // ANT_LANGTON_H_