#ifndef ANT_HERBIVORE_H_
#define ANT_HERBIVORE_H_

#include "ant.h"

class AntHerbivore : public Ant {
 public:
  AntHerbivore(int x, int y, Orientation orient, const std::string& color, int life, const std::string& rules);
  virtual ~AntHerbivore() {}

  // Implementación del movimiento para herbívoras
  void Move(Tape& tape) override;
  
  std::string get_rules() const override;
  std::string get_type() const override;

 protected:
  std::string rules_;
  
  // Métodos auxiliares de giro y avance ortogonal
  void Turn(int color);
  void Forward(Tape&);
};

#endif