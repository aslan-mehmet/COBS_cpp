#include <gtest/gtest.h>
#include "cobs.h"

TEST(RawDecoding, 1)
{
    uint8_t encodedData[] = {0x01, 0x01, 0x00};
    uint8_t data[1];
    uint64_t numOfData;
    uint8_t expectedData[] = {0x00};
    Cobs myCobs;

    numOfData = myCobs.decode(data, sizeof(data), encodedData, sizeof(encodedData));

    EXPECT_EQ(sizeof(expectedData), numOfData);

    for (int i = 0; i < sizeof(expectedData); ++i)
        EXPECT_EQ(expectedData[i], data[i]);
}

TEST(RawDecoding, 2)
{
    uint8_t encodedData[] = {0x01, 0x01, 0x01, 0x00};
    uint8_t data[2];
    uint64_t numOfData;
    uint8_t expectedData[] = {0x00, 0x00};
    Cobs myCobs;

    numOfData = myCobs.decode(data, sizeof(data), encodedData, sizeof(encodedData));

    EXPECT_EQ(sizeof(expectedData), numOfData);

    for (int i = 0; i < sizeof(expectedData); ++i)
        EXPECT_EQ(expectedData[i], data[i]);
}

TEST(RawDecoding, 3)
{
    uint8_t encodedData[] = {0x03, 0x11, 0x22, 0x02, 0x33, 0x00};
    uint8_t data[4];
    uint64_t numOfData;
    uint8_t expectedData[] = {0x11, 0x22, 0x00, 0x33};
    Cobs myCobs;

    numOfData = myCobs.decode(data, sizeof(data), encodedData, sizeof(encodedData));

    EXPECT_EQ(sizeof(expectedData), numOfData);

    for (int i = 0; i < sizeof(expectedData); ++i)
        EXPECT_EQ(expectedData[i], data[i]);
}

TEST(RawDecoding, 4)
{
    uint8_t encodedData[] = {0x05, 0x11, 0x22, 0x33, 0x44, 0x00};
    uint8_t data[4];
    uint64_t numOfData;
    uint8_t expectedData[] = {0x11, 0x22, 0x33, 0x44};
    Cobs myCobs;

    numOfData = myCobs.decode(data, sizeof(data), encodedData, sizeof(encodedData));

    EXPECT_EQ(sizeof(expectedData), numOfData);

    for (int i = 0; i < sizeof(expectedData); ++i)
        EXPECT_EQ(expectedData[i], data[i]);
}

TEST(RawDecoding, 5)
{
    uint8_t encodedData[] = {0x02, 0x11, 0x01, 0x01, 0x01, 0x00};
    uint8_t data[4];
    uint64_t numOfData;
    uint8_t expectedData[] = {0x11, 0x00, 0x00, 0x00};
    Cobs myCobs;

    numOfData = myCobs.decode(data, sizeof(data), encodedData, sizeof(encodedData));

    EXPECT_EQ(sizeof(expectedData), numOfData);

    for (int i = 0; i < sizeof(expectedData); ++i)
        EXPECT_EQ(expectedData[i], data[i]);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

