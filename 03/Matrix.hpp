#pragma once

#include <iostream>

class Matrix
{
    class ProxyRow
    {
    public:
        int32_t *data;
        size_t columns;
    public:
        int32_t& operator[](size_t j) const;
        ~ProxyRow();
    };

private:
    size_t rows_, columns_;
    ProxyRow *data_rows_;

public:
    Matrix(size_t rows, size_t columns);

    ~Matrix();

    ProxyRow& operator[](size_t i) const;

    size_t rows() const;
    size_t columns() const;
    
    void operator*= (int32_t lambda);

    friend std::ostream& operator<< (std::ostream& output, const Matrix& matrix);

    Matrix operator+ (const Matrix& matrix) const;

    bool operator== (const Matrix& matrix) const;

    bool operator!= (const Matrix& matrix) const;
};
