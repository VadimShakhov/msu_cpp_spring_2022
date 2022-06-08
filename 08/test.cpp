#include <gtest/gtest.h>

#include "ThreadPool.hpp"


struct foo{
    int a = 1;
    int b = 2;

    foo(int x, int y) : a(x), b(y) {}
};

int func1(foo f, int i){
    return f.a + f.b + i;
}

double func2(){
    return 0.1;
}

bool func3(int x, int y){
    return x > y;
}

void func4(int* x){
    *x = 0;
}

class TestTreadPool : public ::testing::Test
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

TEST_F(TestTreadPool, Constructors)
{
    auto pool = ThreadPool(2);

    int i = 1;
    auto task1 = pool.exec(func1, foo(7, 8), i);
    auto task2 = pool.exec(func2);
    auto task3 = pool.exec(func3, 3, 4);
    auto task4 = pool.exec(func4, &i);
    auto task5 = pool.exec([]() { return 1; });

    ASSERT_EQ(task1.get(), 16);
    ASSERT_EQ(task2.get(), 0.1);
    ASSERT_FALSE(task3.get());
    task4.wait();
    ASSERT_EQ(i, 0);
    ASSERT_EQ(task5.get(), 1);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
