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
        int32_t& operator[](size_t j) const
        {
            if (j >= columns){
                throw std::out_of_range("Выход за границы матрицы (столбцы)");
            }
            return data[j];
        }

        ~ProxyRow(){
            delete[] data;
        }
    };

private:
    size_t rows_, columns_;
    ProxyRow *data_rows_;

public:
    Matrix(size_t rows, size_t columns){
        rows_ = rows;
        columns_ = columns;
        data_rows_ = new ProxyRow[rows_];
        for (size_t i=0; i < rows_; i++){
            data_rows_[i].data = new int32_t[columns_];
            data_rows_[i].columns = columns_;
            for (size_t j=0; j < columns_; j++){
                data_rows_[i][j] = 0;
            }
        }
    }

    ~Matrix(){
        delete[] data_rows_;
    }

    ProxyRow& operator[](size_t i) const
    {
        if (i >= rows_){
            throw std::out_of_range("Выход за границы матрицы (строчки)");
        }
        return data_rows_[i];
    }

    size_t rows() const {return rows_;}
    size_t columns() const {return columns_;}
    
    void operator*= (int32_t lambda){
        for (size_t i=0; i < rows_; i++){
            for (size_t j=0; j < columns_; j++){
                (*this)[i][j] *= lambda;
            }
        }
    }

    friend std::ostream& operator<< (std::ostream& output, const Matrix& matrix){
        for (size_t i=0; i < matrix.rows(); i++){
            for (size_t j=0; j < matrix.columns(); j++){
                output << matrix[i][j] << " ";
            }
            output << std::endl;
        }
        return output;
    }

    Matrix operator+ (const Matrix& matrix) const{
        if (matrix.rows() != rows_ || matrix.columns() != columns_){
            throw std::invalid_argument("Размеры матриц не совпадают");
        }
        Matrix sum(rows_, columns_);
        for (size_t i=0; i < rows_; i++){
            for (size_t j=0; j < columns_; j++){
                sum[i][j] = (*this)[i][j] + matrix[i][j];
            }
        }
        return sum;
    }

    bool operator== (const Matrix& matrix) const{
        if (matrix.rows() != rows_ || matrix.columns() != columns_){
            return false;
        }
        for (size_t i=0; i < rows_; i++){
            for (size_t j=0; j < columns_; j++){
                if ((*this)[i][j] != matrix[i][j]){
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!= (const Matrix& matrix) const{
        return !(*this == matrix);
    }
};
