#ifndef ANT_CARNIVORE_H_
#define ANT_CARNIVORE_H_

#include "ant.h"

class AntCarnivore : public Ant {
 public:
  AntCarnivore(int x, int y, Orientation orient, const std::string& color, 
               int life, const std::string& rules, double voracity);
  
  void Move(Tape& tape) override;
  
  std::string get_rules() const override;
  std::string get_type() const override;
  double get_voracity() const;

 protected:
  std::string rules_;
  double voracity_;
  
  void Turn(int color);
  void Forward(Tape&);
};

#endif