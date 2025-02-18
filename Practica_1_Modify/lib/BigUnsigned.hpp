#ifndef BIGUNSIGNED_HPP
#define BIGUNSIGNED_HPP

#include <iostream>
#include <vector>

class BigUnsigned {
private:
    // Se almacenan los dígitos en orden inverso: dígito 0 = unidad, etc.
    std::vector<unsigned char> digits;

    // Función auxiliar para eliminar ceros a la izquierda (dígitos de mayor peso)
    void removeLeadingZeros();

public:
    // Constructores:
    BigUnsigned(unsigned n = 0);
    BigUnsigned(const unsigned char* str);
    BigUnsigned(const BigUnsigned&); // Constructor de copia

    // Operador de asignación:
    BigUnsigned& operator=(const BigUnsigned&);

    // Inserción y extracción en flujo:
    friend std::ostream& operator<<(std::ostream&, const BigUnsigned&);
    friend std::istream& operator>>(std::istream&, BigUnsigned&);

    // Comparación:
    bool operator==(const BigUnsigned&) const;
    friend bool operator<(const BigUnsigned&, const BigUnsigned&);

    // Incremento/decremento:
    BigUnsigned& operator++();     // Pre-incremento
    BigUnsigned operator++(int);   // Post-incremento
    BigUnsigned& operator--();     // Pre-decremento
    BigUnsigned operator--(int);   // Post-decremento

    // Operadores aritméticos:
    friend BigUnsigned operator+(const BigUnsigned&, const BigUnsigned&);
    BigUnsigned operator-(const BigUnsigned&) const;
    BigUnsigned operator*(const BigUnsigned&) const;
    friend BigUnsigned operator/(const BigUnsigned&, const BigUnsigned&);
    BigUnsigned operator%(const BigUnsigned&) const;
};

#endif // BIGUNSIGNED_HPP
