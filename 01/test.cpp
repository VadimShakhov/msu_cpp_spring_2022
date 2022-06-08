#include <iostream>

#include <gtest/gtest.h>

#include "Allocator.hpp"

class TestAllocator : public ::testing::Test
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

TEST_F(TestAllocator, makeAllocator)
{
    Allocator data;

    EXPECT_THROW(data.makeAllocator(0), std::invalid_argument);
    
    data.makeAllocator(10);
    ASSERT_EQ(data.get_memory(), data.get_offset());
    ASSERT_EQ(data.get_freeSpace(), 10);
    ASSERT_EQ(data.get_allSpace(), 10);
    
    data.makeAllocator(5);
    ASSERT_EQ(data.get_memory(), data.get_offset());
    ASSERT_EQ(data.get_freeSpace(), 5);
    ASSERT_EQ(data.get_allSpace(), 5);
}

TEST_F(TestAllocator, alloc)
{
    Allocator data;

    EXPECT_THROW(data.alloc(0), std::invalid_argument);

    char *ptr = data.alloc(5);
    ASSERT_EQ(ptr, nullptr);

    data.makeAllocator(10);
    
    ptr = data.alloc(5);
    ASSERT_EQ(data.get_memory(), ptr);
    ASSERT_EQ(data.get_memory()+5, data.get_offset());
    ASSERT_EQ(data.get_freeSpace(), 5);
    ASSERT_EQ(data.get_allSpace(), 10);
    
    ptr = data.alloc(4);
    ASSERT_EQ(data.get_memory()+5, ptr);
    ASSERT_EQ(data.get_memory()+9, data.get_offset());
    ASSERT_EQ(data.get_freeSpace(), 1);
    ASSERT_EQ(data.get_allSpace(), 10);
    
    ptr = data.alloc(5);
    ASSERT_EQ(nullptr, ptr);
    ASSERT_EQ(data.get_freeSpace(), 1);
    ASSERT_EQ(data.get_allSpace(), 10);


    data.makeAllocator(20);
    ASSERT_EQ(data.get_memory(), data.get_offset());
    ASSERT_EQ(data.get_freeSpace(), 20);
    ASSERT_EQ(data.get_allSpace(), 20);

    ptr = data.alloc(10);
    ASSERT_EQ(data.get_memory(), ptr);
    ASSERT_EQ(data.get_memory()+10, data.get_offset());
    ASSERT_EQ(data.get_freeSpace(), 10);
    ASSERT_EQ(data.get_allSpace(), 20);
    
    ptr = data.alloc(10);
    ASSERT_EQ(data.get_memory()+10, ptr);
    ASSERT_EQ(data.get_freeSpace(), 0);
    ASSERT_EQ(data.get_allSpace(), 20);

    ptr = data.alloc(1);
    ASSERT_EQ(nullptr, ptr);
    ASSERT_EQ(data.get_freeSpace(), 0);
    ASSERT_EQ(data.get_allSpace(), 20);
    
}

TEST_F(TestAllocator, reset)
{
    Allocator data;    
    data.makeAllocator(10);    
    data.alloc(5);
    char *memory_old = data.get_memory();
    data.alloc(4);
    
    data.reset();
    ASSERT_EQ(data.get_memory(), memory_old);
    ASSERT_EQ(data.get_memory(), data.get_offset());
    ASSERT_EQ(data.get_freeSpace(), 10);
    ASSERT_EQ(data.get_allSpace(), 10);


    data.makeAllocator(10);
    data.alloc(5);
    data.alloc(5);
    data.alloc(1);

    ASSERT_EQ(data.get_memory()+10, data.get_offset());
    ASSERT_EQ(data.get_freeSpace(), 0);
    ASSERT_EQ(data.get_allSpace(), 10);

    data.reset();
    ASSERT_EQ(data.get_memory(), data.get_offset());
    ASSERT_EQ(data.get_freeSpace(), 10);
    ASSERT_EQ(data.get_allSpace(), 10);

    data.alloc(10);
    ASSERT_EQ(data.get_memory()+10, data.get_offset());
    ASSERT_EQ(data.get_freeSpace(), 0);
    ASSERT_EQ(data.get_allSpace(), 10);
}

TEST_F(TestAllocator, pointer_dif)
{
    Allocator data;    
    data.makeAllocator(10);

    char *ptr1 = data.alloc(3);
    char *ptr2 = data.alloc(6);

    ASSERT_EQ(ptr2 - ptr1, 3);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
