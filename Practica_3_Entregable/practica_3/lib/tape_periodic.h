#ifndef TAPE_PERIODIC_H_
#define TAPE_PERIODIC_H_

#include "tape.h"

class TapePeriodic : public Tape {
  public:
    // Constructor
    TapePeriodic(int x, int y, int num_colors);

    int GetColor(int x, int y) const override;
    void NextColor(int x, int y) override;
    void SetColor(int x, int y, int color) override;

    // Método auxiliar para gestionar el envolvimiento periódico
    int WrapX(int x) const;
    int WrapY(int y) const;
  private:
    std::vector<std::vector<int>> celdas_;
};

#endif //TAPE_PERIODIC_H_