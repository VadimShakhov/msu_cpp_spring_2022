#include <gtest/gtest.h>

#include <vector>
#include "ThreadSort.hpp"


class TestThreadSort : public ::testing::Test
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

TEST_F(TestThreadSort, Sorting)
{
    size_t count = 100000;
    FILE *nums = fopen("numbers.bin", "w+b");
    for (size_t i=0; i<count; i++){
        num_type num = static_cast<num_type>(rand());
        fwrite(&num, sizeof(num_type), 1, nums);
    }
    rewind(nums);
    
    std::vector<num_type> sorted;
    sorted.reserve(count);
    for (size_t i=0; i<count; i++){
        num_type num;
        fread(&num, sizeof(num_type), 1, nums);
        sorted.push_back(num);
    }
    std::sort(sorted.begin(), sorted.end());
    fclose(nums);

    two_thread_sort("numbers.bin", "sorted.bin");
    FILE *my_sorted = fopen("sorted.bin", "rb");

    num_type num;
    for (size_t i=0; i<count; i++){
        fread(&num, sizeof(num_type), 1, my_sorted);
        ASSERT_EQ(sorted[i], num);
    }
    ASSERT_EQ(fread(&num, sizeof(num_type), 1, my_sorted), 0);

    fclose(my_sorted);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
 
