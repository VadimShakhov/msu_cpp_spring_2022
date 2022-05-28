#pragma once

#include <iostream>
#include <string>

class BigInt{
public:
    BigInt() = default;
    BigInt(const BigInt&);
    BigInt(const int32_t&);
    BigInt(const std::string&);
    BigInt(BigInt &&);
    ~BigInt();

    BigInt& operator=(const BigInt&);
    BigInt& operator=(const int32_t&);
    BigInt& operator=(BigInt&&);

    // все операции в столбик
    BigInt operator+(const BigInt&) const; 
    BigInt operator+(const int32_t&) const;
    BigInt operator-(const BigInt&) const;
    BigInt operator-(const int32_t&) const;
    BigInt operator*(const BigInt&) const;
    BigInt operator*(const int32_t&) const;

    bool operator==(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    friend std::ostream& operator<<(std::ostream&, const BigInt&);
    
private:
    static const int32_t DIGIT_MAX = 100; // основание системы счисления (10^n)
    static const int32_t DIGIT_MAX_ORDER = 2; // n
    int32_t *number = nullptr; // массив со значениями разрядов, меньшие разряды в начале
    size_t digits = 0; // число разрядов
};
