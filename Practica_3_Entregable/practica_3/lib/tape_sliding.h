#ifndef TAPE_SLIDING_H_
#define TAPE_SLIDING_H_

#include "tape.h"
#include "sliding_vector.h"

class TapeSliding : public Tape {
 public:
  TapeSliding(int x, int y, int num_colors);

  int GetColor(int x, int y) const override;
  void NextColor(int x, int y) override;
  void SetColor(int x, int y, int color) override;

 private:
  // Una estructura SlidingVector que contiene SlidingVectors de enteros
  mutable SlidingVector<SlidingVector<int>> celdas_;

  // Método interno para expandir la cinta cuando se captura la excepción
  void Expand(int x, int y) const;
};

#endif