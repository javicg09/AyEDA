#ifndef TAPE_REFLECTIVE_H_
#define TAPE_REFLECTIVE_H_

#include "tape.h"

class TapeReflective : public Tape {
 public:
  TapeReflective(int x, int y, int num_colors);

  int GetColor(int x, int y) const override;
  void NextColor(int x, int y) override;

  // Método necesario para que el Simulator detecte el choque
  bool IsInside(int x, int y) const;

 private:
  std::vector<std::vector<int>> cells_;
};

#endif