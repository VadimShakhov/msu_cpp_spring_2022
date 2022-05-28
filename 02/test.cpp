#include <gtest/gtest.h>

#include <string>
#include <iostream>

#include "TokenParser.hpp"
#include "Callbacks.hpp"

class TestTokenParser : public ::testing::Test
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

TEST_F(TestTokenParser, WithCallbacks)
{
    TokenParser parser;
    parser.SetStartCallback(StartCallback);
    parser.SetEndCallback(EndCallback);
    parser.SetDigitTokenCallback(DigitCallback);
    parser.SetStringTokenCallback(StringCallback);

    std::string line = "1234 fg356j\t32548723645981654792385765476547\n0000000000000000000000000005";
    parser.Parse(line);

    ASSERT_EQ(parser.log.size(), 6);
    ASSERT_EQ(parser.log[0], 0);
    ASSERT_EQ(parser.log[1], 2);
    ASSERT_EQ(parser.log[2], 3);
    ASSERT_EQ(parser.log[3], 3);
    ASSERT_EQ(parser.log[4], 2);
    ASSERT_EQ(parser.log[5], 1);

    ASSERT_EQ(parser.log_digit.size(), 2);
    ASSERT_EQ(parser.log_digit[0], 1234);
    ASSERT_EQ(parser.log_digit[1], 5);

    ASSERT_EQ(parser.log_string.size(), 2);
    ASSERT_EQ(parser.log_string[0], "fg356j");
    ASSERT_EQ(parser.log_string[1], "32548723645981654792385765476547");
}

TEST_F(TestTokenParser, WithoutCallbacks)
{
    TokenParser parser;

    std::string line = "1234 fg356j\t32548723645981654792385765476547\n0000000000000000000000000005";
    parser.Parse(line);

    ASSERT_EQ(parser.log.size(), 0);

    ASSERT_EQ(parser.log_digit.size(), 2);
    ASSERT_EQ(parser.log_digit[0], 1234);
    ASSERT_EQ(parser.log_digit[1], 5);

    ASSERT_EQ(parser.log_string.size(), 2);
    ASSERT_EQ(parser.log_string[0], "fg356j");
    ASSERT_EQ(parser.log_string[1], "32548723645981654792385765476547");
}

TEST_F(TestTokenParser, EmptyString)
{
    TokenParser parser;
    parser.SetStartCallback(StartCallback);
    parser.SetEndCallback(EndCallback);
    parser.SetDigitTokenCallback(DigitCallback);
    parser.SetStringTokenCallback(StringCallback);

    std::string line = "";
    parser.Parse(line);

    ASSERT_EQ(parser.log.size(), 2);
    ASSERT_EQ(parser.log[0], 0);
    ASSERT_EQ(parser.log[1], 1);

    ASSERT_EQ(parser.log_digit.size(), 0);

    ASSERT_EQ(parser.log_string.size(), 0);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
