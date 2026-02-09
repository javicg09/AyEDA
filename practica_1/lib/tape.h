#ifndef _TAPE_
#define _TAPE_
#include <fstream>
#include <iostream>
#include <vector>

class Tape {
 public:
  Tape(int x, int y);
  int getColor(int x, int y) const;
  void setColor(int x, int y, int color);

  int getsizeX();
  int gestsizeY();

  friend std::ostream& operator<<(std::ostream& os, const Tape& t);

 private:
  int sizeX_, sizeY_;
  std::vector<std::vector<int>> color_;
};
#endif