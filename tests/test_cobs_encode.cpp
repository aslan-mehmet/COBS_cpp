#include <gtest/gtest.h>
#include "cobs.h"

TEST(EncodingTests, EncodeDataTest1)
{
    uint8_t data[] = {0x00};
    std::vector<uint8_t> encodingOutput;
    uint8_t expectedOutput[] = {0x01, 0x01, 0x00};
    cobs myCobs;

    myCobs.encode(encodingOutput, data, sizeof(data));
    
    EXPECT_EQ(sizeof(expectedOutput), encodingOutput.size());

    for (int i = 0; i < sizeof(expectedOutput); ++i)
        EXPECT_EQ(encodingOutput[i], expectedOutput[i]);
}

TEST(EncodingTests, EncodeDataTest2)
{
    uint8_t data[] = {0x00, 0x00};
    std::vector<uint8_t> encodingOutput;
    uint8_t expectedOutput[] = {0x01, 0x01, 0x01, 0x00};
    cobs myCobs;

    myCobs.encode(encodingOutput, data, sizeof(data));
    
    EXPECT_EQ(sizeof(expectedOutput), encodingOutput.size());

    for (int i = 0; i < sizeof(expectedOutput); ++i)
        EXPECT_EQ(encodingOutput[i], expectedOutput[i]);
}

TEST(EncodingTests, EncodeDataTest3)
{
    uint8_t data[] = {0x11, 0x22, 0x00, 0x33};
    std::vector<uint8_t> encodingOutput;
    uint8_t expectedOutput[] = {0x03, 0x11, 0x22, 0x02, 0x33, 0x00};
    cobs myCobs;

    myCobs.encode(encodingOutput, data, sizeof(data));
    
    EXPECT_EQ(sizeof(expectedOutput), encodingOutput.size());

    for (int i = 0; i < sizeof(expectedOutput); ++i)
        EXPECT_EQ(encodingOutput[i], expectedOutput[i]);
}

TEST(EncodingTests, EncodeDataTest4)
{
    uint8_t data[] = {0x11, 0x22, 0x33, 0x44};
    std::vector<uint8_t> encodingOutput;
    uint8_t expectedOutput[] = {0x05, 0x11, 0x22, 0x33, 0x44, 0x00};
    cobs myCobs;

    myCobs.encode(encodingOutput, data, sizeof(data));
    
    EXPECT_EQ(sizeof(expectedOutput), encodingOutput.size());

    for (int i = 0; i < sizeof(expectedOutput); ++i)
        EXPECT_EQ(encodingOutput[i], expectedOutput[i]);
}

TEST(EncodingTests, EncodeDataTest5)
{
    uint8_t data[] = {0x11, 0x00, 0x00, 0x00};
    std::vector<uint8_t> encodingOutput;
    uint8_t expectedOutput[] = {0x02, 0x11, 0x01, 0x01, 0x01, 0x00};
    cobs myCobs;

    myCobs.encode(encodingOutput, data, sizeof(data));
    
    EXPECT_EQ(sizeof(expectedOutput), encodingOutput.size());

    for (int i = 0; i < sizeof(expectedOutput); ++i)
        EXPECT_EQ(encodingOutput[i], expectedOutput[i]);
}

TEST(EncodingTests, EncodeDataTest6)
{
    uint8_t data[254]; //0x01, 0x02, .... , 0xfd, 0xfe
    for (int i = 0x01; i <= 0xfe; ++i)
        data[i-1] = i;
    std::vector<uint8_t> encodingOutput;
    uint8_t expectedOutput[256]; //0xff, 0x01, 0x02, ... , 0xfd, 0xfe, 0x00
    expectedOutput[0] = 0xff;
    expectedOutput[255] = 0x00;
    for (int i = 0x01; i <= 0xfe; ++i)
        expectedOutput[i] = i;
    cobs myCobs;

    myCobs.encode(encodingOutput, data, sizeof(data));
    
    EXPECT_EQ(sizeof(expectedOutput), encodingOutput.size());

    for (int i = 0; i < sizeof(expectedOutput); ++i)
        EXPECT_EQ(encodingOutput[i], expectedOutput[i]);
}

TEST(EncodingTests, EncodeDataTest7)
{
    uint8_t data[254]; //0x01, 0x02, .... , 0xfd, 0xfe
    for (int i = 0x01; i <= 0xfe; ++i)
        data[i-1] = i;
    std::vector<uint8_t> encodingOutput;
    uint8_t expectedOutput[256]; //0xff, 0x01, 0x02, ... , 0xfd, 0xfe, 0x00
    expectedOutput[0] = 0xff;
    expectedOutput[255] = 0x00;
    for (int i = 0x01; i <= 0xfe; ++i)
        expectedOutput[i] = i;
    cobs myCobs;

    myCobs.encode(encodingOutput, data, sizeof(data));
    
    EXPECT_EQ(sizeof(expectedOutput), encodingOutput.size());

    for (int i = 0; i < sizeof(expectedOutput); ++i)
        EXPECT_EQ(encodingOutput[i], expectedOutput[i]);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

