#ifndef BIGINTEGER_HPP
#define BIGINTEGER_HPP

#include "BigUnsigned.hpp"
#include <iostream>

class BigInteger {
private:
    // Se utiliza un BigUnsigned para almacenar el valor absoluto.
    BigUnsigned absValue;
    // Indica si el número es negativo. (false: no negativo; true: negativo)
    bool negative;

    // Función auxiliar para asegurar que el cero siempre se almacene como no negativo.
    void normalize();

public:
    // Constructores
    BigInteger(int n = 0);
    BigInteger(const BigUnsigned& bu);
    BigInteger(const BigInteger& other);

    // Operador de asignación
    BigInteger& operator=(const BigInteger& other);

    // Inserción y extracción en flujo
    friend std::ostream& operator<<(std::ostream& os, const BigInteger& num);
    friend std::istream& operator>>(std::istream& is, BigInteger& num);

    // Operadores de comparación
    bool operator==(const BigInteger& other) const;
    friend bool operator<(const BigInteger& lhs, const BigInteger& rhs);

    // Incremento/Decremento
    BigInteger& operator++();     // Pre-incremento
    BigInteger operator++(int);   // Post-incremento
    BigInteger& operator--();     // Pre-decremento
    BigInteger operator--(int);   // Post-decremento

    // Operadores aritméticos
    friend BigInteger operator+(const BigInteger& a, const BigInteger& b);
    BigInteger operator-(const BigInteger& b) const;
    BigInteger operator*(const BigInteger& b) const;
    friend BigInteger operator/(const BigInteger& a, const BigInteger& b);
    BigInteger operator%(const BigInteger& b) const;

    // Operador unario menos
    BigInteger operator-() const;
};

#endif // BIGINTEGER_HPP
