#include <iostream>
#include <sstream>

#include <gtest/gtest.h>

#include "Deserializer.hpp"
#include "Serializer.hpp"
#include "Data.hpp"


class TestDS : public ::testing::Test
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

TEST_F(TestDS, Serializer_Only_uint)
{
    {
        Data2uint x { 10, 20 };

        std::stringstream stream;

        Serializer serializer(stream);
        const Error err = serializer.save(x);
        ASSERT_EQ(err, Error::NoError);

        std::string str;
        stream >> str;
        ASSERT_EQ(str, "10");
        stream >> str;
        ASSERT_EQ(str, "20");
        
    }

    {
        Data3uint x { 10, 20, 30 };

        std::stringstream stream;

        Serializer serializer(stream);
        const Error err = serializer.save(x);
        ASSERT_EQ(err, Error::NoError);

        std::string str;
        stream >> str;
        ASSERT_EQ(str, "10");
        stream >> str;
        ASSERT_EQ(str, "20");
        stream >> str;
        ASSERT_EQ(str, "30");
        
    }
}

TEST_F(TestDS, Serializer_Only_bool)
{
    {
        Data2bool x { true, false };

        std::stringstream stream;

        Serializer serializer(stream);
        const Error err = serializer.save(x);
        ASSERT_EQ(err, Error::NoError);

        std::string str;
        stream >> str;
        ASSERT_EQ(str, "true");
        stream >> str;
        ASSERT_EQ(str, "false");
        
    }

    {
        Data3bool x { true, false, true };

        std::stringstream stream;

        Serializer serializer(stream);
        const Error err = serializer.save(x);
        ASSERT_EQ(err, Error::NoError);

        std::string str;
        stream >> str;
        ASSERT_EQ(str, "true");
        stream >> str;
        ASSERT_EQ(str, "false");
        stream >> str;
        ASSERT_EQ(str, "true");
        
    }
}

TEST_F(TestDS, Serializer_uint_bool)
{
    Data_ibib x { 500, true, 1000, false };

    std::stringstream stream;

    Serializer serializer(stream);
    const Error err = serializer.save(x);
    ASSERT_EQ(err, Error::NoError);

    std::string str;
    stream >> str;
    ASSERT_EQ(str, "500");
    stream >> str;
    ASSERT_EQ(str, "true");
    stream >> str;
    ASSERT_EQ(str, "1000");
    stream >> str;
    ASSERT_EQ(str, "false");
}

TEST_F(TestDS, Serializer_error)
{
    Data_double x { 500, true, 0.56376, false };

    std::stringstream stream;

    Serializer serializer(stream);
    const Error err = serializer.save(x);
    ASSERT_EQ(err, Error::CorruptedArchive);
}

TEST_F(TestDS, Deserializer_Only_uint)
{
    {
        Data2uint x { 10, 20 };
        std::stringstream stream;
        Serializer serializer(stream);
        serializer.save(x);

        Deserializer deserializer(stream);
        Data2uint y { 0, 0 };
        const Error err = deserializer.load(y);

        ASSERT_EQ(err, Error::NoError);

        ASSERT_EQ(y.a, 10);
        ASSERT_EQ(y.b, 20);
        
    }

    {
        Data3uint x { 10, 20, 30 };
        std::stringstream stream;
        Serializer serializer(stream);
        serializer.save(x);

        Deserializer deserializer(stream);
        Data3uint y { 0, 0, 0 };
        const Error err = deserializer.load(y);

        ASSERT_EQ(err, Error::NoError);

        ASSERT_EQ(y.a, 10);
        ASSERT_EQ(y.b, 20);
        ASSERT_EQ(y.c, 30);
        
    }
}

TEST_F(TestDS, Deserializer_Only_bool)
{
    {
        Data2bool x { true, false };
        std::stringstream stream;
        Serializer serializer(stream);
        serializer.save(x);

        Deserializer deserializer(stream);
        Data2bool y { false, false };
        const Error err = deserializer.load(y);

        ASSERT_EQ(err, Error::NoError);

        ASSERT_TRUE(y.a);
        ASSERT_FALSE(y.b);
        
    }

    {
        Data3bool x { true, false, true };
        std::stringstream stream;
        Serializer serializer(stream);
        serializer.save(x);

        Deserializer deserializer(stream);
        Data3bool y { false, false, false };
        const Error err = deserializer.load(y);

        ASSERT_EQ(err, Error::NoError);

        ASSERT_TRUE(y.a);
        ASSERT_FALSE(y.b);
        ASSERT_TRUE(y.c);
        
    }
}

TEST_F(TestDS, Deserializer_uint_bool)
{
    Data_ibib x { 500, true, 1000, false };
    std::stringstream stream;
    Serializer serializer(stream);
    serializer.save(x);

    Deserializer deserializer(stream);
    Data_ibib y { 0, false, 0, false };
    const Error err = deserializer.load(y);

    ASSERT_EQ(err, Error::NoError);

    ASSERT_EQ(y.a, 500);
    ASSERT_TRUE(y.b);
    ASSERT_EQ(y.c, 1000);
    ASSERT_FALSE(y.d);
}

TEST_F(TestDS, Deserializer_error)
{
    {
        std::stringstream stream;
        std::string str = "1023 true 42";

        Deserializer deserializer(stream);
        Data_ibib y { 0, false, 0, false };
        const Error err = deserializer.load(y);

        ASSERT_EQ(err, Error::CorruptedArchive);
    }

    {
        std::stringstream stream;
        std::string str = "1023 true 42 false 43";

        Deserializer deserializer(stream);
        Data_ibib y { 0, false, 0, false };
        const Error err = deserializer.load(y);

        ASSERT_EQ(err, Error::CorruptedArchive);
    }

    {
        std::stringstream stream;
        std::string str = "1023 truth 42 false";

        Deserializer deserializer(stream);
        Data_ibib y { 0, false, 0, false };
        const Error err = deserializer.load(y);

        ASSERT_EQ(err, Error::CorruptedArchive);
    }

    {
        std::stringstream stream;
        std::string str = "102394567369538247562398476532985762 true 42 false";

        Deserializer deserializer(stream);
        Data_ibib y { 0, false, 0, false };
        const Error err = deserializer.load(y);

        ASSERT_EQ(err, Error::CorruptedArchive);
    }
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
