#include <gtest/gtest.h>
#include "cobs.h"

TEST(DecodingTests, DecodeDataTest1)
{
    std::vector<uint8_t> encodedData {0x01, 0x01, 0x00};
    uint8_t data[1];
    uint8_t expectedData[] = {0x00};
    cobs myCobs;

    myCobs.decode(data, sizeof(data), encodedData);

    EXPECT_EQ(sizeof(expectedData), sizeof(data));

    for (int i = 0; i < sizeof(expectedData); ++i)
        EXPECT_EQ(expectedData[i], data[i]);
}

TEST(DecodingTests, DecodeDataTest2)
{
    std::vector<uint8_t> encodedData {0x01, 0x01, 0x01, 0x00};
    uint8_t data[2];
    uint8_t expectedData[] = {0x00, 0x00};
    cobs myCobs;

    myCobs.decode(data, sizeof(data), encodedData);

    EXPECT_EQ(sizeof(expectedData), sizeof(data));

    for (int i = 0; i < sizeof(expectedData); ++i)
        EXPECT_EQ(expectedData[i], data[i]);
}

TEST(DecodingTests, DecodeDataTest3)
{
    std::vector<uint8_t> encodedData {0x03, 0x11, 0x22, 0x02, 0x33, 0x00};
    uint8_t data[4];
    uint8_t expectedData[] = {0x11, 0x22, 0x00, 0x33};
    cobs myCobs;

    myCobs.decode(data, sizeof(data), encodedData);

    EXPECT_EQ(sizeof(expectedData), sizeof(data));

    for (int i = 0; i < sizeof(expectedData); ++i)
        EXPECT_EQ(expectedData[i], data[i]);
}

TEST(DecodingTests, DecodeDataTest4)
{
    std::vector<uint8_t> encodedData {0x05, 0x11, 0x22, 0x33, 0x44, 0x00};
    uint8_t data[4];
    uint8_t expectedData[] = {0x11, 0x22, 0x33, 0x44};
    cobs myCobs;

    myCobs.decode(data, sizeof(data), encodedData);

    EXPECT_EQ(sizeof(expectedData), sizeof(data));

    for (int i = 0; i < sizeof(expectedData); ++i)
        EXPECT_EQ(expectedData[i], data[i]);
}

TEST(DecodingTests, DecodeDataTest5)
{
    std::vector<uint8_t> encodedData {0x02, 0x11, 0x01, 0x01, 0x01, 0x00};
    uint8_t data[4];
    uint8_t expectedData[] = {0x11, 0x00, 0x00, 0x00};
    cobs myCobs;

    myCobs.decode(data, sizeof(data), encodedData);

    EXPECT_EQ(sizeof(expectedData), sizeof(data));

    for (int i = 0; i < sizeof(expectedData); ++i)
        EXPECT_EQ(expectedData[i], data[i]);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

