#include "Matrix.hpp"

int32_t& Matrix::ProxyRow::operator[](size_t j) const{
    if (j >= columns)
        throw std::out_of_range("Выход за границы матрицы (столбцы)");

    return data[j];
}

Matrix::ProxyRow::~ProxyRow(){
    delete[] data;
}

Matrix::Matrix(size_t rows, size_t columns){
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

Matrix::~Matrix(){
    delete[] data_rows_;
}

Matrix::ProxyRow& Matrix::operator[](size_t i) const{
    if (i >= rows_)
        throw std::out_of_range("Выход за границы матрицы (строчки)");

    return data_rows_[i];
}

size_t Matrix::rows() const{
    return rows_;
}

size_t Matrix::columns() const {
    return columns_;
}

void Matrix::operator*= (int32_t lambda){
    for (size_t i=0; i < rows_; i++){
        for (size_t j=0; j < columns_; j++){
            (*this)[i][j] *= lambda;
        }
    }
}

std::ostream& operator<< (std::ostream& output, const Matrix& matrix){
    for (size_t i=0; i < matrix.rows(); i++){
        for (size_t j=0; j < matrix.columns()-1; j++){
            output << matrix[i][j] << " ";
        }
        output << matrix[i][matrix.columns()-1];
        output << std::endl;
    }
    return output;
}

Matrix Matrix::operator+ (const Matrix& matrix) const{
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

bool Matrix::operator== (const Matrix& matrix) const{
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

bool Matrix::operator!= (const Matrix& matrix) const{
    return !(*this == matrix);
}
