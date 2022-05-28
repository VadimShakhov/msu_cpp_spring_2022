#include <iostream>
#include <sstream>

#include <gtest/gtest.h>

#include "BigInt.hpp"

class TestBigInt : public ::testing::Test
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

TEST_F(TestBigInt, constructors)
{
    BigInt a(12345);
    BigInt b("123456789101112");
    BigInt c(a);
    std::stringstream strm (std::ios_base::in | std::ios_base::out);
    std::string check;

    strm << a;
    getline(strm, check);
    ASSERT_EQ(check, "12345");
    strm.str(std::string());
    strm.clear();

    strm << b;
    getline(strm, check);
    ASSERT_EQ(check, "123456789101112");
    strm.str(std::string());
    strm.clear();

    strm << c;
    getline(strm, check);
    ASSERT_EQ(check, "12345");
    strm.str(std::string());
    strm.clear();

    BigInt m(std::move(b));
    strm << m;
    getline(strm, check);
    ASSERT_EQ(check, "123456789101112");
    strm.str(std::string());
    strm.clear();

    strm << b;
    getline(strm, check);
    ASSERT_EQ(check, "");
    strm.str(std::string());
    strm.clear();
}

TEST_F(TestBigInt, assignment)
{
    {
        BigInt a;
        a = 12345;
        std::stringstream strm (std::ios_base::in | std::ios_base::out);
        std::string check;
        strm << a;
        strm >> check;
        ASSERT_EQ(check, "12345");
    }

    {
        BigInt a("172376534857238562");
        BigInt b;
        b = a;
        std::stringstream strm (std::ios_base::in | std::ios_base::out);
        std::string check;
        strm << b;
        strm >> check;
        ASSERT_EQ(check, "172376534857238562");
    }

    {
        BigInt a("172376534857238562");
        a = a;
        std::stringstream strm (std::ios_base::in | std::ios_base::out);
        std::string check;
        strm << a;
        strm >> check;
        ASSERT_EQ(check, "172376534857238562");
    }

    {
        BigInt a("172376534857238562");
        a = std::move(a);
        std::stringstream strm (std::ios_base::in | std::ios_base::out);
        std::string check;
        strm << a;
        strm >> check;
        ASSERT_EQ(check, "172376534857238562");
    }

    {
        BigInt a("172376534857238562");
        BigInt b;
        b = std::move(a);
        std::stringstream strm (std::ios_base::in | std::ios_base::out);
        std::string check;
        strm << b;
        strm >> check;
        ASSERT_EQ(check, "172376534857238562");
        strm.str(std::string());
        strm.clear();

        strm << a;
        getline(strm, check);
        ASSERT_EQ(check, "");
    }
        
}

TEST_F(TestBigInt, plus)
{
    {
        BigInt a("9999999999");
        BigInt b = 0;
        std::stringstream strm (std::ios_base::in | std::ios_base::out);
        std::string check;
        strm << (a+b);
        strm >> check;
        ASSERT_EQ(check, "9999999999");
    }

    {
        BigInt a("9999999999");
        BigInt b = 100000;
        std::stringstream strm (std::ios_base::in | std::ios_base::out);
        std::string check;
        strm << (a+b);
        strm >> check;
        ASSERT_EQ(check, "10000099999");
    }

    {
        BigInt a("9999999999");
        BigInt b("100000");
        std::stringstream strm (std::ios_base::in | std::ios_base::out);
        std::string check;
        strm << (a+b);
        strm >> check;
        ASSERT_EQ(check, "10000099999");
    }
    
}

TEST_F(TestBigInt, minus)
{
    {
        BigInt a("10000000000");
        BigInt b = 1;
        std::stringstream strm (std::ios_base::in | std::ios_base::out);
        std::string check;
        strm << (a-b);
        strm >> check;
        ASSERT_EQ(check, "9999999999");
    }

    {
        BigInt a("1234567891011");
        BigInt b = 275463;
        std::stringstream strm (std::ios_base::in | std::ios_base::out);
        std::string check;
        strm << (a-b);
        strm >> check;
        ASSERT_EQ(check, "1234567615548");
    }

    {
        BigInt a("1234567891011");
        BigInt b("109876543210");
        std::stringstream strm (std::ios_base::in | std::ios_base::out);
        std::string check;
        strm << (a-b);
        strm >> check;
        ASSERT_EQ(check, "1124691347801");
    }
}

TEST_F(TestBigInt, mult)
{
    {
        BigInt a("293573495283932856737357639842540825");
        BigInt b = 0;
        std::stringstream strm (std::ios_base::in | std::ios_base::out);
        std::string check;
        strm << (a*b);
        strm >> check;
        ASSERT_EQ(check, "0");
    }
    
    {
        BigInt a("1234567891011");
        BigInt b = 275463;
        std::stringstream strm (std::ios_base::in | std::ios_base::out);
        std::string check;
        strm << (a*b);
        strm >> check;
        ASSERT_EQ(check, "340077774961563093");
    }

    {
        BigInt a("1234567891011");
        BigInt b("109876543210");
        std::stringstream strm (std::ios_base::in | std::ios_base::out);
        std::string check;
        strm << (a*b);
        strm >> check;
        ASSERT_EQ(check, "135650052222348712085310");
    }
}

TEST_F(TestBigInt, comparisons)
{
   BigInt big1("123456789101112");
   BigInt big2("123456789101112");
   BigInt small("1234567891011");

   ASSERT_TRUE(big1 == big1);
   ASSERT_TRUE(big1 == big2);
   ASSERT_FALSE(big1 == small);

   ASSERT_FALSE(big1 < big1);
   ASSERT_TRUE(small < big2);
   ASSERT_FALSE(big1 < small);

   ASSERT_FALSE(big1 > big1);
   ASSERT_TRUE(big1 > small);
   ASSERT_FALSE(small > big2);

   ASSERT_TRUE(big1 <= big1);
   ASSERT_TRUE(big1 <= big2);
   ASSERT_TRUE(small <= big2);
   ASSERT_FALSE(big1 <= small);

   ASSERT_TRUE(big1 >= big1);
   ASSERT_TRUE(big1 >= big2);
   ASSERT_TRUE(big1 >= small);
   ASSERT_FALSE(small >= big2);
    
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
