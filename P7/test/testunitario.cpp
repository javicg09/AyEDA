#include <cassert>
#include <iostream>
#include "AVL.h"

int main() {
  AVL<int> avl;

  for (int i = 1; i <= 10; ++i) avl.insertar(i);

  std::cout << "\nAVL con 10 nodos (1-10):\n";
  avl.escribir(std::cout);

  avl.eliminarNodosPares();

  std::cout << "\nAVL tras eliminarNodosPares():\n";
  avl.escribir(std::cout);

  int nodos = avl.tamanyo();
  std::cout << "\nNumero de nodos: " << nodos << "\n";

  assert(nodos == 5 && "Deben quedar exactamente 5 nodos impares");

  std::cout << "Test PASADO: quedan exactamente " << nodos << " nodos impares.\n";
  return 0;
}
