#include <iostream>

#include <gtest/gtest.h>

#include "Matrix.hpp"


class TestMatrix : public ::testing::Test
{
protected:
    void SetUp()
    {
        std::cout << "SetUp" << std::endl;
    }
    void TearDown()
    {
        std::cout << "TearDown" << std::endl;
    }
};

TEST_F(TestMatrix, RowColumnCount){
    const size_t rows = 5;
    const size_t cols = 3;
    Matrix m(rows, cols);

    ASSERT_EQ(m.rows(), 5);
    ASSERT_EQ(m.columns(), 3);
}

TEST_F(TestMatrix, ItemAccess){
    const size_t rows = 5;
    const size_t cols = 3;
    Matrix m(rows, cols);

    m[1][2] = 5; 
    m[2][1] = 10;
    ASSERT_EQ(m[1][2], 5);
    ASSERT_EQ(m[2][1], 10);
    
    double x = m[4][1];
    ASSERT_EQ(x, double(0));
}

TEST_F(TestMatrix, Product){
    const size_t rows = 5;
    const size_t cols = 3;
    Matrix m(rows, cols);
    for (size_t i=0; i<rows; i++){
        for (size_t j=0; j<cols; j++){
            m[i][j] = i*cols + j;
        }
    }

    m *= 3;
    for (size_t i=0; i<rows; i++){
        for (size_t j=0; j<cols; j++){
            ASSERT_EQ(m[i][j], 3*(i*cols + j));
        }
    }
}

TEST_F(TestMatrix, OutOfRange){
    const size_t rows = 5;
    const size_t cols = 3;
    Matrix m(rows, cols);

    EXPECT_THROW(m[7][2], std::out_of_range);
    EXPECT_THROW(m[1][10], std::out_of_range);
    EXPECT_THROW(m[20][20], std::out_of_range);
}


TEST_F(TestMatrix, Equality){
    const size_t rows = 5;
    const size_t cols = 3;
    
    Matrix m(rows, cols);
    for (size_t i=0; i<rows; i++){
        for (size_t j=0; j<cols; j++){
            m[i][j] = i*cols + j;
        }
    }

    Matrix m1(rows, cols);
    for (size_t i=0; i<rows; i++){
        for (size_t j=0; j<cols; j++){
            m1[i][j] = m[i][j];
        }
    }
    
    ASSERT_TRUE(m1 == m);
    ASSERT_FALSE(m1 != m);
    m1[3][1] = 235423;
    ASSERT_TRUE(m1 != m);
    ASSERT_FALSE(m1 == m);
    
    Matrix m2(10, 20);
    ASSERT_TRUE(m2 != m);
    ASSERT_FALSE(m2 == m);
}

TEST_F(TestMatrix, Sum){
    const size_t rows = 5;
    const size_t cols = 3;
    
    Matrix m(rows, cols);
    for (size_t i=0; i<rows; i++){
        for (size_t j=0; j<cols; j++){
            m[i][j] = (rows-i)*cols - j;
        }
    }
    
    Matrix m1(rows, cols);
    for (size_t i=0; i<rows; i++){
        for (size_t j=0; j<cols; j++){
            m1[i][j] = i*cols + j;
        }
    }
    
    Matrix m2 = m1 + m;
    for (size_t i=0; i<rows; i++){
        for (size_t j=0; j<cols; j++){
            ASSERT_EQ(m2[i][j], m1[i][j] + m[i][j]);
        }
    }
    
    Matrix m3(6, 3);
    EXPECT_THROW(m3 + m, std::invalid_argument);
    Matrix m4(5, 7);
    EXPECT_THROW(m4 + m, std::invalid_argument);
    Matrix m5(1, 1);
    EXPECT_THROW(m5 + m, std::invalid_argument);
}

TEST_F(TestMatrix, OStream){
    const size_t rows = 5;
    const size_t cols = 3;
    Matrix m(rows, cols);
    for (size_t i=0; i<rows; i++){
        for (size_t j=0; j<cols; j++){
            m[i][j] = (rows-i)*cols - j;
        }
    }
    std::cout << m << std::endl;
}

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
