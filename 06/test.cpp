#include <gtest/gtest.h>

#include <vector>
#include "format.hpp"


class TestFormat : public ::testing::Test
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

TEST_F(TestFormat, NoExceptions)
{
    auto text = format("{1} + {1} = {0}", 2, "one");
    ASSERT_EQ(text, "one + one = 2");

    text = format("one + one = 2");
    ASSERT_EQ(text, "one + one = 2");

    text = format("");
    ASSERT_EQ(text, "");

    text = format("{1} + {1} = {0}", 2, "one", "two");
    ASSERT_EQ(text, "one + one = 2");

    text = format("{2} + {2} = {1}", "two", 2, "one");
    ASSERT_EQ(text, "one + one = 2");

    text = format("{2} + {2} = {0}", 2, "two", "one");
    ASSERT_EQ(text, "one + one = 2");

    text = format("{1} + {000000000000000000000000000000000000000000000001} = {0}", 2, "one");
    ASSERT_EQ(text, "one + one = 2");
}

TEST_F(TestFormat, BigIndex)
{
    EXPECT_THROW({
        try{
            auto text = format("{10} + {1} = {0}", 2, "one");
        }
        catch (const BigIndex& err){
            ASSERT_EQ(err.get_message(), "Нет аргумента с номером, указанным по индексу 1");
            ASSERT_EQ(err.get_index(), 1);
            throw;
        }
    }, BigIndex);

    EXPECT_THROW({
        try{
            auto text = format("{1} + {10} = {0}", 2, "one");
        }
        catch (const BigIndex& err){
            ASSERT_EQ(err.get_message(), "Нет аргумента с номером, указанным по индексу 7");
            ASSERT_EQ(err.get_index(), 7);
            throw;
        }
    }, BigIndex);

    EXPECT_THROW({
        try{
            auto text = format("{1} + {1} = {10}", 2, "one");
        }
        catch (const BigIndex& err){
            ASSERT_EQ(err.get_message(), "Нет аргумента с номером, указанным по индексу 13");
            ASSERT_EQ(err.get_index(), 13);
            throw;
        }
    }, BigIndex);

    EXPECT_THROW({
        try{
            auto text = format("{1} + {20} = {10}", 2, "one");
        }
        catch (const BigIndex& err){
            ASSERT_EQ(err.get_message(), "Нет аргумента с номером, указанным по индексу 7");
            ASSERT_EQ(err.get_index(), 7);
            throw;
        }
    }, BigIndex);
}

TEST_F(TestFormat, HugeIndex)
{
    EXPECT_THROW({
        try{
            auto text = format("{999999999999999999999999999} + {1} = {0}", 2, "one");
        }
        catch (const HugeIndex& err){
            ASSERT_EQ(err.get_message(), "Номер аргумента по индексу 1 не влезает в size_t");
            ASSERT_EQ(err.get_index(), 1);
            throw;
        }
    }, HugeIndex);

    EXPECT_THROW({
        try{
            auto text = format("{1} + {999999999999999999999999999} = {0}", 2, "one");
        }
        catch (const HugeIndex& err){
            ASSERT_EQ(err.get_message(), "Номер аргумента по индексу 7 не влезает в size_t");
            ASSERT_EQ(err.get_index(), 7);
            throw;
        }
    }, HugeIndex);

    EXPECT_THROW({
        try{
            auto text = format("{1} + {1} = {999999999999999999999999999}", 2, "one");
        }
        catch (const HugeIndex& err){
            ASSERT_EQ(err.get_message(), "Номер аргумента по индексу 13 не влезает в size_t");
            ASSERT_EQ(err.get_index(), 13);
            throw;
        }
    }, HugeIndex);

    EXPECT_THROW({
        try{
            auto text = format("{1} + {999999999999999999999999999} = {999999999999999999999999999}", 2, "one");
        }
        catch (const HugeIndex& err){
            ASSERT_EQ(err.get_message(), "Номер аргумента по индексу 7 не влезает в size_t");
            ASSERT_EQ(err.get_index(), 7);
            throw;
        }
    }, HugeIndex);
}

TEST_F(TestFormat, BadUseBracket){
    EXPECT_THROW({
        try{
            auto text = format("{1} +{ {1} = {0}", 2, "one");
        }
        catch (const BadUseBracket& err){
            ASSERT_EQ(err.get_message(), "Некорректное использование фигурной скобки по индексу 5");
            ASSERT_EQ(err.get_index(), 5);
            throw;
        }
    }, BadUseBracket);

    EXPECT_THROW({
        try{
            auto text = format("{1} +} {1} = {0}", 2, "one");
        }
        catch (const BadUseBracket& err){
            ASSERT_EQ(err.get_message(), "Некорректное использование фигурной скобки по индексу 5");
            ASSERT_EQ(err.get_index(), 5);
            throw;
        }
    }, BadUseBracket);

    EXPECT_THROW({
        try{
            auto text = format("{1} + {1} = {0", 2, "one");
        }
        catch (const BadUseBracket& err){
            ASSERT_EQ(err.get_message(), "Некорректное использование фигурной скобки по индексу 12");
            ASSERT_EQ(err.get_index(), 12);
            throw;
        }
    }, BadUseBracket);

    EXPECT_THROW({
        try{
            auto text = format("{", 2, "one");
        }
        catch (const BadUseBracket& err){
            ASSERT_EQ(err.get_message(), "Некорректное использование фигурной скобки по индексу 0");
            ASSERT_EQ(err.get_index(), 0);
            throw;
        }
    }, BadUseBracket);

    EXPECT_THROW({
        try{
            auto text = format("}", 2, "one");
        }
        catch (const BadUseBracket& err){
            ASSERT_EQ(err.get_message(), "Некорректное использование фигурной скобки по индексу 0");
            ASSERT_EQ(err.get_index(), 0);
            throw;
        }
    }, BadUseBracket);

    EXPECT_THROW({
        try{
            auto text = format("{1} + {} = {0}", 2, "one", 2, "one");
        }
        catch (const BadUseBracket& err){
            ASSERT_EQ(err.get_message(), "Некорректное использование фигурной скобки по индексу 6");
            ASSERT_EQ(err.get_index(), 6);
            throw;
        }
    }, BadUseBracket);
}

TEST_F(TestFormat, BadInBrackets){
    EXPECT_THROW({
        try{
            auto text = format("{1} + {one} = {0}", 2, "one");
        }
        catch (const BadInBrackets& err){
            ASSERT_EQ(err.get_message(), "Некорректный символ в фигурных скобках по индексу 7");
            ASSERT_EQ(err.get_index(), 7);
            throw;
        }
    }, BadInBrackets);
}

TEST_F(TestFormat, BadStream){
    EXPECT_THROW({
        try{
            std::vector<int> vec(10);
            auto text = format("{1} + {1} = {0}", 2, vec);
        }
        catch (const BadStream& err){
            ASSERT_EQ(err.get_message(), "Аргумент с номером 1 не поддержиает вывод в поток");
            ASSERT_EQ(err.get_number(), 1);
            throw;
        }
    }, BadStream);
}

TEST_F(TestFormat, CombinedExceptions){
    EXPECT_THROW({
        try{
            std::vector<int> vec(10);
            auto text = format("{1} + {10} {99abc} }= {1372645298457125376142424526253274962745}", 2, vec);
        }
        catch (const BadStream& err){
            ASSERT_EQ(err.get_message(), "Аргумент с номером 1 не поддержиает вывод в поток");
            ASSERT_EQ(err.get_number(), 1);
            throw;
        }
    }, BadStream);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
