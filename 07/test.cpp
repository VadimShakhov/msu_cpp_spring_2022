#include <gtest/gtest.h>

#include "Vector.hpp"


struct foo{
    int a, b;

    foo() : a(0), b(0) {}

    foo(int x, int y) : a(x), b(y) {}

    bool operator==(const foo& other) const{
        return (a == other.a) && (b == other.b);
    }
};

class TestVector : public ::testing::Test
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

TEST_F(TestVector, Constructors)
{
    {
        Vector<int> vec;
        ASSERT_EQ(vec.size(), 0);
        ASSERT_EQ(vec.capacity(), 0);
    }

    {
        Vector<int> vec(10);
        ASSERT_EQ(vec.size(), 10);
        ASSERT_EQ(vec.capacity(), 10);
        for (size_t i=0; i<10; i++){
            ASSERT_EQ(vec[i], 0);
        }
    }

    {
        Vector<int> vec(10, 5);
        ASSERT_EQ(vec.size(), 10);
        ASSERT_EQ(vec.capacity(), 10);
        for (size_t i=0; i<10; i++){
            ASSERT_EQ(vec[i], 5);
        }
    }

    {
        Vector<int> vec {0, 1, 2, 3, 4, 5};
        ASSERT_EQ(vec.size(), 6);
        ASSERT_EQ(vec.capacity(), 6);
        for (size_t i=0; i<6; i++){
            ASSERT_EQ(vec[i], i);
        }
    }
}

TEST_F(TestVector, PushPop_Back)
{
    Vector<int> vec;

    ASSERT_TRUE(vec.empty());
    vec.push_back(1);
    ASSERT_FALSE(vec.empty());
    ASSERT_EQ(vec.size(), 1);
    ASSERT_EQ(vec.capacity(), 1);
    ASSERT_EQ(vec[0], 1);

    vec.push_back(2);
    ASSERT_EQ(vec.size(), 2);
    ASSERT_EQ(vec.capacity(), 3);
    ASSERT_EQ(vec[1], 2);

    vec.push_back(3);
    ASSERT_EQ(vec.size(), 3);
    ASSERT_EQ(vec.capacity(), 3);
    ASSERT_EQ(vec[2], 3);

    vec.pop_back();
    ASSERT_EQ(vec.size(), 2);
    ASSERT_EQ(vec.capacity(), 3);
    ASSERT_EQ(vec[0], 1);
    ASSERT_EQ(vec[1], 2);

    vec.pop_back();
    ASSERT_EQ(vec.size(), 1);
    ASSERT_EQ(vec.capacity(), 3);
    ASSERT_EQ(vec[0], 1);

    vec.pop_back();
    ASSERT_TRUE(vec.empty());
    ASSERT_EQ(vec.size(), 0);
    ASSERT_EQ(vec.capacity(), 3);

    vec.pop_back();
    ASSERT_EQ(vec.size(), 0);
    ASSERT_EQ(vec.capacity(), 3);
}

TEST_F(TestVector, Resize)
{
    {
        Vector<int> vec {1, 2, 3, 4, 5};
        for (size_t i=0; i<5; i++)
            ASSERT_EQ(vec[i], i+1);

        ASSERT_EQ(vec.size(), 5);
        ASSERT_EQ(vec.capacity(), 5);

        vec.resize(2);
        ASSERT_EQ(vec.size(), 2);
        ASSERT_EQ(vec.capacity(), 5);
        for (size_t i=0; i<2; i++)
            ASSERT_EQ(vec[i], i+1);

        vec.resize(10);
        ASSERT_EQ(vec.size(), 10);
        ASSERT_EQ(vec.capacity(), 10);
        for (size_t i=0; i<2; i++)
            ASSERT_EQ(vec[i], i+1);
        for (size_t i=2; i<10; i++)
            ASSERT_EQ(vec[i], 0);

        vec.resize(20);
        ASSERT_EQ(vec.size(), 20);
        ASSERT_EQ(vec.capacity(), 20);
        for (size_t i=0; i<2; i++)
            ASSERT_EQ(vec[i], i+1);
        for (size_t i=2; i<20; i++)
            ASSERT_EQ(vec[i], 0);
    }

    {
        Vector<int> vec {1, 2, 3, 4, 5};

        vec.resize(2, 5);
        ASSERT_EQ(vec.size(), 2);
        ASSERT_EQ(vec.capacity(), 5);
        for (size_t i=0; i<2; i++)
            ASSERT_EQ(vec[i], i+1);

        vec.resize(10, 5);
        ASSERT_EQ(vec.size(), 10);
        ASSERT_EQ(vec.capacity(), 10);
        for (size_t i=0; i<2; i++)
            ASSERT_EQ(vec[i], i+1);
        for (size_t i=2; i<10; i++)
            ASSERT_EQ(vec[i], 5);

        vec.resize(20, 5);
        ASSERT_EQ(vec.size(), 20);
        ASSERT_EQ(vec.capacity(), 20);
        for (size_t i=0; i<2; i++)
            ASSERT_EQ(vec[i], i+1);
        for (size_t i=2; i<20; i++)
            ASSERT_EQ(vec[i], 5);
    }
}

TEST_F(TestVector, Emplace_Back)
{
    Vector<foo> vec;
    vec.emplace_back(1, 2);
    vec.emplace_back(3, 4);
    vec.emplace_back(5, 6);
    ASSERT_EQ(vec.size(), 3);
    ASSERT_EQ(vec.capacity(), 3);
    ASSERT_EQ(vec[0], foo(1, 2));
    ASSERT_EQ(vec[1], foo(3, 4));
    ASSERT_EQ(vec[2], foo(5, 6));
}

TEST_F(TestVector, Iterators_Reserve_Clear)
{
    Vector<int> vec;
    auto begin = vec.begin();
    auto end = vec.end();
    auto rbegin = vec.rbegin();
    auto rend = vec.rend();
    ASSERT_EQ(begin, end);
    ASSERT_EQ(rbegin, rend);

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    begin = vec.begin();
    end = vec.end();
    size_t i = 0;
    while (begin != end){
        ASSERT_EQ(*begin, vec[i]);
        ++i;
        ++begin;
    }
    ASSERT_EQ(i, 4);

    i = 0;
    rbegin = vec.rbegin();
    rend = vec.rend();
    while (rbegin != rend){
        ASSERT_EQ(*rbegin, vec[3 - i]);
        ++i;
        ++rbegin;
    }
    ASSERT_EQ(i, 4);

    begin = vec.begin();
    end = vec.end();
    rbegin = vec.rbegin();
    rend = vec.rend();
    ASSERT_EQ(vec.capacity(), 7);

    vec.reserve(6);
    ASSERT_EQ(vec.capacity(), 7);
    ASSERT_EQ(vec.size(), 4);
    ASSERT_EQ(vec.begin(), begin);
    ASSERT_EQ(vec.end(), end);
    ASSERT_EQ(vec.rbegin(), rbegin);
    ASSERT_EQ(vec.rend(), rend);

    vec.reserve(10);
    ASSERT_EQ(vec.capacity(), 10);
    ASSERT_EQ(vec.size(), 4);
    ASSERT_NE(vec.begin(), begin);
    ASSERT_NE(vec.end(), end);
    ASSERT_NE(vec.rbegin(), rbegin);
    ASSERT_NE(vec.rend(), rend);

    vec.clear();
    ASSERT_EQ(vec.capacity(), 10);
    ASSERT_EQ(vec.size(), 0);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
