#include "BigInteger.hpp"
#include <cassert>

// Función auxiliar para normalizar el cero
void BigInteger::normalize() {
    // Si el valor absoluto es 0, se fuerza el signo a no negativo.
    if (absValue == BigUnsigned(0u))
        negative = false;
}

// Constructor a partir de un entero
BigInteger::BigInteger(int n) : absValue(0u), negative(false) {
    if (n < 0) {
        negative = true;
        // Se asume que n no es el mínimo entero (para simplificar)
        absValue = BigUnsigned(static_cast<unsigned>(-n));
    } else {
        absValue = BigUnsigned(static_cast<unsigned>(n));
    }
    normalize();
}

// Constructor a partir de un BigUnsigned (siempre no negativo)
BigInteger::BigInteger(const BigUnsigned& bu) : absValue(bu), negative(false) {
    normalize();
}

// Constructor de copia
BigInteger::BigInteger(const BigInteger& other)
    : absValue(other.absValue), negative(other.negative)
{ }

// Operador de asignación
BigInteger& BigInteger::operator=(const BigInteger& other) {
    if (this != &other) {
        absValue = other.absValue;
        negative = other.negative;
    }
    return *this;
}

// Operador de inserción en flujo (salida)
std::ostream& operator<<(std::ostream& os, const BigInteger& num) {
    if (num.negative && !(num.absValue == BigUnsigned(0u)))
        os << "-";
    os << num.absValue;
    return os;
}

// Operador de extracción en flujo (entrada)
// Se permite opcionalmente un signo inicial ('-' o '+')
std::istream& operator>>(std::istream& is, BigInteger& num) {
    std::string input;
    is >> input;
    if (!input.empty() && input[0] == '-') {
        num.negative = true;
        input = input.substr(1);
    } else {
        num.negative = false;
        if (!input.empty() && input[0] == '+')
            input = input.substr(1);
    }
    num.absValue = BigUnsigned(reinterpret_cast<const unsigned char*>(input.c_str()));
    num.normalize();
    return is;
}

// Operador de igualdad
bool BigInteger::operator==(const BigInteger& other) const {
    return (negative == other.negative) && (absValue == other.absValue);
}

// Operador "menor que" (friend)
bool operator<(const BigInteger& lhs, const BigInteger& rhs) {
    // Si los signos difieren, el negativo es menor
    if (lhs.negative != rhs.negative)
        return lhs.negative;
    // Si ambos son no negativos, se compara el valor absoluto
    if (!lhs.negative)
        return lhs.absValue < rhs.absValue;
    else
        // Si ambos son negativos, el que tenga mayor valor absoluto es menor
        return rhs.absValue < lhs.absValue;
}

// Pre-incremento (++a)
BigInteger& BigInteger::operator++() {
    if (negative) {
        // Para números negativos se "reduce" el valor absoluto
        if (absValue == BigUnsigned(0u)) {
            negative = false; // -0 se convierte en 0
        } else {
            absValue = absValue - BigUnsigned(1);
            if (absValue == BigUnsigned(0u))
                negative = false;
        }
    } else {
        absValue = absValue + BigUnsigned(1);
    }
    return *this;
}

// Post-incremento (a++)
BigInteger BigInteger::operator++(int) {
    BigInteger temp = *this;
    ++(*this);
    return temp;
}

// Pre-decremento (--a)
BigInteger& BigInteger::operator--() {
    if (negative) {
        absValue = absValue + BigUnsigned(1);
    } else {
        // Si es 0, al decrementar se obtiene -1
        if (absValue == BigUnsigned(0u)) {
            absValue = BigUnsigned(1);
            negative = true;
        } else {
            absValue = absValue - BigUnsigned(1);
        }
    }
    normalize();
    return *this;
}

// Post-decremento (a--)
BigInteger BigInteger::operator--(int) {
    BigInteger temp = *this;
    --(*this);
    return temp;
}

// Operador unario menos
BigInteger BigInteger::operator-() const {
    BigInteger result = *this;
    if (!(result.absValue == BigUnsigned(0u)))
        result.negative = !result.negative;
    return result;
}

// Operador de suma
BigInteger operator+(const BigInteger& a, const BigInteger& b) {
    BigInteger result;
    // Si ambos tienen el mismo signo se suman los valores absolutos
    if(a.negative == b.negative) {
        result.absValue = a.absValue + b.absValue;
        result.negative = a.negative;
    } else {
        // Si los signos difieren se resta el menor valor absoluto del mayor
        if(a.absValue == b.absValue) {
            result.absValue = BigUnsigned(0u);
            result.negative = false;
        } else if(a.absValue < b.absValue) {
            result.absValue = b.absValue - a.absValue;
            result.negative = b.negative;
        } else {
            result.absValue = a.absValue - b.absValue;
            result.negative = a.negative;
        }
    }
    result.normalize();
    return result;
}

// Operador de resta
BigInteger BigInteger::operator-(const BigInteger& b) const {
    return *this + (-b);
}

// Operador de multiplicación
BigInteger BigInteger::operator*(const BigInteger& b) const {
    BigInteger result;
    result.absValue = this->absValue * b.absValue;
    // El signo es negativo si y solo si uno de los dos es negativo
    result.negative = (this->negative != b.negative);
    result.normalize();
    return result;
}

// Operador de división
BigInteger operator/(const BigInteger& a, const BigInteger& b) {
    assert(!(b.absValue == BigUnsigned(0u)) && "División por cero");
    BigInteger result;
    result.absValue = a.absValue / b.absValue;
    result.negative = (a.negative != b.negative);
    result.normalize();
    return result;
}

// Operador módulo
BigInteger BigInteger::operator%(const BigInteger& b) const {
    assert(!(b.absValue == BigUnsigned(0u)) && "Módulo con divisor cero");
    BigInteger result;
    result.absValue = this->absValue % b.absValue;
    // Se conserva el signo del dividendo (opcionalmente se podría definir siempre positivo)
    result.negative = this->negative;
    result.normalize();
    return result;
}
