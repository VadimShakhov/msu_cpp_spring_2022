#include <gtest/gtest.h>

#include<string>
#include<sstream>

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


void mult(size_t rows, size_t cols){
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

void range(size_t rows, size_t cols){
    Matrix m(rows, cols);

    EXPECT_THROW(m[rows+10][cols-1], std::out_of_range);
    EXPECT_THROW(m[rows-1][cols+10], std::out_of_range);
    EXPECT_THROW(m[rows+10][cols+10], std::out_of_range);

    EXPECT_THROW(m[rows][1], std::out_of_range);
    EXPECT_THROW(m[1][cols], std::out_of_range);
    EXPECT_THROW(m[rows][cols], std::out_of_range);
}

void eq(size_t rows, size_t cols){
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
    m1[rows-1][cols-1] = 235423;
    ASSERT_TRUE(m1 != m);
    ASSERT_FALSE(m1 == m);
        
    Matrix m2(rows*2, cols*2);
    ASSERT_TRUE(m2 != m);
    ASSERT_FALSE(m2 == m);
}

void sum(size_t rows, size_t cols){
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

    Matrix m3(rows+1, cols);
    EXPECT_THROW(m3 + m, std::invalid_argument);
    Matrix m4(rows, cols+1);
    EXPECT_THROW(m4 + m, std::invalid_argument);
    Matrix m5(rows+1, cols+1);
    EXPECT_THROW(m5 + m, std::invalid_argument);
}

TEST_F(TestMatrix, RowColumnCount){
    const size_t rows = 5;
    const size_t cols = 3;
    Matrix m(rows, cols);

    ASSERT_EQ(m.rows(), rows);
    ASSERT_EQ(m.columns(), cols);

    Matrix m1x1(1, 1);
    ASSERT_EQ(m1x1.rows(), 1);
    ASSERT_EQ(m1x1.columns(), 1);


    const size_t N = 5;

    Matrix m1xN(1, N);
    ASSERT_EQ(m1xN.rows(), 1);
    ASSERT_EQ(m1xN.columns(), N);

    Matrix mNx1(N, 1);
    ASSERT_EQ(mNx1.rows(), N);
    ASSERT_EQ(mNx1.columns(), 1);
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


    const size_t N = 5;

    Matrix m1x1(1, 1);
    m1x1[0][0] = 5;
    ASSERT_EQ(m1x1[0][0], 5);

    Matrix m1xN(1, N);
    m1xN[0][1] = 4;
    m1xN[0][3] = 5;
    ASSERT_EQ(m1xN[0][1], 4);
    ASSERT_EQ(m1xN[0][3], 5);

    Matrix mNx1(N, 1);
    mNx1[1][0] = 4;
    mNx1[3][0] = 5;
    ASSERT_EQ(mNx1[1][0], 4);
    ASSERT_EQ(mNx1[3][0], 5);
}

TEST_F(TestMatrix, Product){
    mult(5, 3);
    mult(1, 1);
    mult(1, 5);
    mult(5, 1);
}

TEST_F(TestMatrix, OutOfRange){
    range(5, 3);
    range(1, 1);
    range(1, 5);
    range(5, 1);
}


TEST_F(TestMatrix, Equality){
    eq(5,3);
    eq(1,1);
    eq(1,5);
    eq(5,1);
}

TEST_F(TestMatrix, Sum){
    sum(5, 3);
    sum(1, 1);
    sum(1, 5);
    sum(5, 1);
}

TEST_F(TestMatrix, OStream){
    {
        const size_t rows = 5;
        const size_t cols = 3;
        Matrix m(rows, cols);
        for (size_t i=0; i<rows; i++){
            for (size_t j=0; j<cols; j++){
                m[i][j] = (rows-i)*cols - j;
            }
        }

        std::stringstream stream;
        stream << m;

        std::string row;
        std::getline(stream, row);
        ASSERT_EQ(row, "15 14 13");
        std::getline(stream, row);
        ASSERT_EQ(row, "12 11 10");
        std::getline(stream, row);
        ASSERT_EQ(row, "9 8 7");
        std::getline(stream, row);
        ASSERT_EQ(row, "6 5 4");
        std::getline(stream, row);
        ASSERT_EQ(row, "3 2 1");
        std::getline(stream, row);
        ASSERT_EQ(row, "");
    }

    {
        Matrix m(1, 1);
        m[0][0] = 2;
        std::stringstream stream;
        stream << m;
        std::string row;
        std::getline(stream, row);
        ASSERT_EQ(row, "2");
        std::getline(stream, row);
        ASSERT_EQ(row, "");
    }

    {
        const size_t rows = 1;
        const size_t cols = 3;
        Matrix m(rows, cols);
        for (size_t i=0; i<rows; i++){
            for (size_t j=0; j<cols; j++){
                m[i][j] = (rows-i)*cols - j;
            }
        }

        std::stringstream stream;
        stream << m;

        std::string row;
        std::getline(stream, row);
        ASSERT_EQ(row, "3 2 1");
        std::getline(stream, row);
        ASSERT_EQ(row, "");
    }

    {
        const size_t rows = 3;
        const size_t cols = 1;
        Matrix m(rows, cols);
        for (size_t i=0; i<rows; i++){
            for (size_t j=0; j<cols; j++){
                m[i][j] = (rows-i)*cols - j;
            }
        }

        std::stringstream stream;
        stream << m;

        std::string row;
        std::getline(stream, row);
        ASSERT_EQ(row, "3");
        std::getline(stream, row);
        ASSERT_EQ(row, "2");
        std::getline(stream, row);
        ASSERT_EQ(row, "1");
        std::getline(stream, row);
        ASSERT_EQ(row, "");
    }
}

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
