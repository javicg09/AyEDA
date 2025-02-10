#include "BigInteger.hpp"
#include <iostream>

using namespace std;

// Función que calcula el mcd de dos números BigInteger utilizando el algoritmo de Euclides.
// Se usan los valores absolutos, de modo que se ignoran los signos.
BigInteger gcd(BigInteger a, BigInteger b) {
    if(a < BigInteger(0))
        a = -a;
    if(b < BigInteger(0))
        b = -b;
    while (!(b == BigInteger(0))) {
        BigInteger r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    cout << "Ingrese dos números enteros (BigInteger):" << endl;
    BigInteger num1, num2;
    cin >> num1 >> num2;
    BigInteger result = gcd(num1, num2);
    cout << "El máximo común divisor es: " << result << endl;
    return 0;
}
