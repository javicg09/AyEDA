#include "BigUnsigned.hpp"
#include <iostream>
#include <cassert>
#include <cctype>  // Para isdigit

// Función auxiliar: elimina ceros innecesarios en los dígitos de mayor peso
void BigUnsigned::removeLeadingZeros() {
    while (digits.size() > 1 && digits.back() == 0)
        digits.pop_back();
}

// Constructor a partir de un entero sin signo
BigUnsigned::BigUnsigned(unsigned n) {
    if(n == 0)
        digits.push_back(0);
    else {
        while(n > 0) {
            digits.push_back(n % 10);
            n /= 10;
        }
    }
}

// Constructor a partir de una cadena de caracteres (null-terminated)
// Se asume que la cadena contiene únicamente dígitos ASCII.
BigUnsigned::BigUnsigned(const unsigned char* str) {
    // Determinar la longitud
    int len = 0;
    while(str[len] != '\0')
        len++;

    // Se recorre la cadena desde el final para almacenar en orden inverso
    for(int i = len - 1; i >= 0; i--) {
        if (!std::isdigit(str[i]))
            continue; // Se ignoran caracteres no numéricos
        digits.push_back(str[i] - '0');
    }
    if (digits.empty())
        digits.push_back(0);
    removeLeadingZeros();
}

// Constructor de copia
BigUnsigned::BigUnsigned(const BigUnsigned& other)
    : digits(other.digits)
{ }

// Operador de asignación
BigUnsigned& BigUnsigned::operator=(const BigUnsigned& other) {
    if (this != &other)
        digits = other.digits;
    return *this;
}

// Operador de inserción en flujo (salida)
std::ostream& operator<<(std::ostream& os, const BigUnsigned& num) {
    // Se imprime desde el dígito de mayor peso al de menor peso
    for (int i = num.digits.size() - 1; i >= 0; i--)
        os << static_cast<char>(num.digits[i] + '0');
    return os;
}

// Operador de extracción en flujo (entrada)
std::istream& operator>>(std::istream& is, BigUnsigned& num) {
    std::string input;
    is >> input;
    num.digits.clear();
    // Usar size_t en lugar de int para la variable start
    std::string::size_type start = 0;
    while(start < input.size() && input[start] == '0')
        start++;
    if(start == input.size()) {
        num.digits.push_back(0);
    } else {
        // Se almacena en orden inverso
        for (int i = input.size() - 1; i >= static_cast<int>(start); i--) {
            if(std::isdigit(input[i]))
                num.digits.push_back(input[i] - '0');
        }
    }
    num.removeLeadingZeros();
    return is;
}


// Comparación de igualdad
bool BigUnsigned::operator==(const BigUnsigned& other) const {
    return digits == other.digits;
}

// Operador "menor que" (friend)
bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs) {
    if(lhs.digits.size() != rhs.digits.size())
        return lhs.digits.size() < rhs.digits.size();
    for (int i = lhs.digits.size() - 1; i >= 0; i--) {
        if(lhs.digits[i] != rhs.digits[i])
            return lhs.digits[i] < rhs.digits[i];
    }
    return false;
}

// Operador pre-incremento (++a)
BigUnsigned& BigUnsigned::operator++() {
    unsigned carry = 1;
    for (size_t i = 0; i < digits.size() && carry; i++) {
        unsigned sum = digits[i] + carry;
        digits[i] = sum % 10;
        carry = sum / 10;
    }
    if(carry)
        digits.push_back(carry);
    return *this;
}

// Operador post-incremento (a++)
BigUnsigned BigUnsigned::operator++(int) {
    BigUnsigned temp = *this;
    ++(*this);
    return temp;
}

// Operador pre-decremento (--a)
// Se asume que el número es mayor que 0.
BigUnsigned& BigUnsigned::operator--() {
    assert(!(digits.size() == 1 && digits[0] == 0) && "No se puede decrementar cero");
    // Usar size_t en lugar de int para la variable i
    std::vector<unsigned char>::size_type i = 0;
    while(i < digits.size()) {
        if(digits[i] > 0) {
            digits[i]--;
            break;
        } else {
            digits[i] = 9;
            i++;
        }
    }
    removeLeadingZeros();
    return *this;
}


// Operador post-decremento (a--)
BigUnsigned BigUnsigned::operator--(int) {
    BigUnsigned temp = *this;
    --(*this);
    return temp;
}

// Operador de suma
BigUnsigned operator+(const BigUnsigned& a, const BigUnsigned& b) {
    BigUnsigned result;
    result.digits.clear();
    size_t maxSize = std::max(a.digits.size(), b.digits.size());
    unsigned carry = 0;
    for (size_t i = 0; i < maxSize || carry; i++) {
        unsigned sum = carry;
        if(i < a.digits.size())
            sum += a.digits[i];
        if(i < b.digits.size())
            sum += b.digits[i];
        result.digits.push_back(sum % 10);
        carry = sum / 10;
    }
    result.removeLeadingZeros();
    return result;
}

// Operador de resta (se asume que *this >= b)
BigUnsigned BigUnsigned::operator-(const BigUnsigned& b) const {
    assert(!(*this < b) && "La resta daría resultado negativo");
    BigUnsigned result(*this);
    unsigned borrow = 0;
    for (size_t i = 0; i < b.digits.size() || borrow; i++) {
        int sub = result.digits[i] - borrow - (i < b.digits.size() ? b.digits[i] : 0);
        if(sub < 0) {
            sub += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits[i] = sub;
    }
    result.removeLeadingZeros();
    return result;
}

// Operador de multiplicación (realizado mediante sumas sucesivas)
BigUnsigned BigUnsigned::operator*(const BigUnsigned& b) const {
    BigUnsigned result(0u);
    // Se recorre cada dígito de b; para cada dígito se suma el valor de *this (desplazado)
    for (size_t i = 0; i < b.digits.size(); i++) {
        BigUnsigned temp;
        // Se agregan i ceros (correspondientes al desplazamiento decimal)
        temp.digits.assign(i, 0);
        // Se multiplica *this por el dígito b.digits[i] sumándolo repetidamente
        BigUnsigned addend = *this;
        unsigned times = b.digits[i];
        BigUnsigned partial(0u);
        for (unsigned j = 0; j < times; j++) {
            partial = partial + addend;
        }
        // Se concatena la suma desplazada
        temp.digits.insert(temp.digits.end(), partial.digits.begin(), partial.digits.end());
        result = result + temp;
    }
    result.removeLeadingZeros();
    return result;
}

// Operador de división (realizado mediante restas sucesivas)
BigUnsigned operator/(const BigUnsigned& a, const BigUnsigned& b) {
    assert(!(b.digits.size() == 1 && b.digits[0] == 0) && "División por cero");
    BigUnsigned quotient(0u);
    BigUnsigned remainder = a;
    while (!(remainder < b)) {
        remainder = remainder - b;
        ++quotient;
    }
    return quotient;
}

// Operador módulo
BigUnsigned BigUnsigned::operator%(const BigUnsigned& b) const {
    assert(!(b.digits.size() == 1 && b.digits[0] == 0) && "Módulo con divisor cero");
    BigUnsigned remainder = *this;
    while (!(remainder < b))
        remainder = remainder - b;
    return remainder;
}
