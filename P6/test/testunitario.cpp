#include <cassert>
#include <iostream>
#include "../lib/ABB.h"

bool testUnitario() {
    ABB<int> arbol;
    arbol.insertar(50);
    arbol.insertar(25);
    arbol.insertar(75);
    arbol.insertar(12);
    arbol.insertar(55);
    arbol.insertar(28);
    arbol.insertar(40);

    int contador = arbol.contarMultiplosDe5();
    if (contador != 5) {
        assert(false);
    }
    return true;
}

int main() {
    bool paso = testUnitario();
    if (paso) {
        std::cout << "El test pasó." << std::endl;
    } else {
        std::cout << "El test no pasó." << std::endl;
    }
    return 0;
}