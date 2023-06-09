#include <gtest/gtest.h>
#include "cobs.h"
#include <iostream>

TEST(RawEncoding, 1)
{
    uint8_t data[] = {0x00};
    uint8_t encodingOutput[1000];
    uint64_t numOfData;
    uint8_t expectedOutput[] = {0x01, 0x01, 0x00};
    Cobs myCobs;

    numOfData = myCobs.encode(encodingOutput, sizeof(encodingOutput), data, sizeof(data));
    
    EXPECT_EQ(sizeof(expectedOutput), numOfData);

    for (int i = 0; i < sizeof(expectedOutput); ++i)
        EXPECT_EQ(encodingOutput[i], expectedOutput[i]);
}

TEST(RawEncoding, 2)
{
    uint8_t data[] = {0x00, 0x00};
    uint8_t encodingOutput[1000];
    uint64_t numOfData;
    uint8_t expectedOutput[] = {0x01, 0x01, 0x01, 0x00};
    Cobs myCobs;

    numOfData = myCobs.encode(encodingOutput, sizeof(encodingOutput), data, sizeof(data));
    
    EXPECT_EQ(sizeof(expectedOutput), numOfData);

    for (int i = 0; i < sizeof(expectedOutput); ++i)
        EXPECT_EQ(encodingOutput[i], expectedOutput[i]);
}

TEST(RawEncoding, 3)
{
    uint8_t data[] = {0x11, 0x22, 0x00, 0x33};
    uint8_t encodingOutput[1000];
    uint64_t numOfData;
    uint8_t expectedOutput[] = {0x03, 0x11, 0x22, 0x02, 0x33, 0x00};
    Cobs myCobs;

    numOfData = myCobs.encode(encodingOutput, sizeof(encodingOutput), data, sizeof(data));
    
    EXPECT_EQ(sizeof(expectedOutput), numOfData);

    for (int i = 0; i < sizeof(expectedOutput); ++i)
        EXPECT_EQ(encodingOutput[i], expectedOutput[i]);
}

TEST(RawEncoding, 4)
{
    uint8_t data[] = {0x11, 0x22, 0x33, 0x44};
    uint8_t encodingOutput[1000];
    uint64_t numOfData;
    uint8_t expectedOutput[] = {0x05, 0x11, 0x22, 0x33, 0x44, 0x00};
    Cobs myCobs;

    numOfData = myCobs.encode(encodingOutput, sizeof(encodingOutput), data, sizeof(data));
    
    EXPECT_EQ(sizeof(expectedOutput), numOfData);

    for (int i = 0; i < sizeof(expectedOutput); ++i)
        EXPECT_EQ(encodingOutput[i], expectedOutput[i]);
}

TEST(RawEncoding, 5)
{
    uint8_t data[] = {0x11, 0x00, 0x00, 0x00};
    uint8_t encodingOutput[1000];
    uint64_t numOfData;
    uint8_t expectedOutput[] = {0x02, 0x11, 0x01, 0x01, 0x01, 0x00};
    Cobs myCobs;

    numOfData = myCobs.encode(encodingOutput, sizeof(encodingOutput), data, sizeof(data));
    
    EXPECT_EQ(sizeof(expectedOutput), numOfData);

    for (int i = 0; i < sizeof(expectedOutput); ++i)
        EXPECT_EQ(encodingOutput[i], expectedOutput[i]);
}

TEST(RawEncoding, 6)
{
    uint8_t data[254]; //0x01, 0x02, .... , 0xfd, 0xfe
    for (int i = 0x01; i <= 0xfe; ++i)
        data[i-1] = i;
    uint8_t encodingOutput[1000];
    uint64_t numOfData;
    uint8_t expectedOutput[256]; //0xff, 0x01, 0x02, ... , 0xfd, 0xfe, 0x00
    expectedOutput[0] = 0xff;
    expectedOutput[255] = 0x00;
    for (int i = 0x01; i <= 0xfe; ++i)
        expectedOutput[i] = i;
    Cobs myCobs;

    numOfData = myCobs.encode(encodingOutput, sizeof(encodingOutput), data, sizeof(data));
    
    EXPECT_EQ(sizeof(expectedOutput), numOfData);

    for (int i = 0; i < sizeof(expectedOutput); ++i)
        EXPECT_EQ(encodingOutput[i], expectedOutput[i]);
}

TEST(RawEncoding, 7)
{
    uint8_t data[254]; //0x01, 0x02, .... , 0xfd, 0xfe
    for (int i = 0x01; i <= 0xfe; ++i)
        data[i-1] = i;
    uint8_t encodingOutput[1000];
    uint64_t numOfData;
    uint8_t expectedOutput[256]; //0xff, 0x01, 0x02, ... , 0xfd, 0xfe, 0x00
    expectedOutput[0] = 0xff;
    expectedOutput[255] = 0x00;
    for (int i = 0x01; i <= 0xfe; ++i)
        expectedOutput[i] = i;
    Cobs myCobs;

    numOfData = myCobs.encode(encodingOutput, sizeof(encodingOutput), data, sizeof(data));
    
    EXPECT_EQ(sizeof(expectedOutput), numOfData);

    for (int i = 0; i < sizeof(expectedOutput); ++i)
        EXPECT_EQ(encodingOutput[i], expectedOutput[i]);
}

TEST(MakeEncodingFail, nullSrc)
{
    uint8_t data[20];
    for(int i = 0; i < sizeof(data); ++i)
        data[i] = 1u;
    uint8_t encodingOutput[1000];
    uint64_t numOfData;
    Cobs myCobs;
    CobsErrors err = CobsErrors::noError;

    try {
        numOfData = myCobs.encode(encodingOutput,
                                  sizeof(encodingOutput),
                                  nullptr,
                                  sizeof(data));
    } catch(CobsErrors &e) {
        err = e;
    }

    EXPECT_EQ(err, CobsErrors::nullPtr);
}

TEST(MakeEncodingFail, nullDst)
{
    uint8_t data[20];
    for(int i = 0; i < sizeof(data); ++i)
        data[i] = 1u;
    uint8_t encodingOutput[1000];
    uint64_t numOfData;
    Cobs myCobs;
    CobsErrors err = CobsErrors::noError;

    try {
        numOfData = myCobs.encode(nullptr,
                                  sizeof(encodingOutput),
                                  data,
                                  sizeof(data));
    } catch(CobsErrors &e) {
        err = e;
    }

    EXPECT_EQ(err, CobsErrors::nullPtr);
}

TEST(MakeEncodingFail, emptySrc)
{
    uint8_t data[20];
    for(int i = 0; i < sizeof(data); ++i)
        data[i] = 1u;
    uint8_t encodingOutput[1000];
    uint64_t numOfData;
    Cobs myCobs;
    CobsErrors err = CobsErrors::noError;

    try {
        numOfData = myCobs.encode(encodingOutput,
                                  sizeof(encodingOutput),
                                  data,
                                  0);
    } catch(CobsErrors &e) {
        err = e;
    }

    EXPECT_EQ(err, CobsErrors::emptySrc);
}

TEST(MakeEncodingFail, srcTooLong)
{
    uint8_t data[255];
    for(int i = 0; i < sizeof(data); ++i)
        data[i] = 1u;
    uint8_t encodingOutput[1000];
    uint64_t numOfData;
    Cobs myCobs;
    CobsErrors err = CobsErrors::noError;

    try {
        numOfData = myCobs.encode(encodingOutput,
                                  sizeof(encodingOutput),
                                  data,
                                  sizeof(data));
    } catch(CobsErrors &e) {
        err = e;
    }

    EXPECT_EQ(err, CobsErrors::srcTooLong);
}

TEST(MakeEncodingFail, wontFitToDst)
{
    uint8_t data[20];
    for(int i = 0; i < sizeof(data); ++i)
        data[i] = 1u;
    uint8_t encodingOutput[10];
    uint64_t numOfData;
    Cobs myCobs;
    CobsErrors err = CobsErrors::noError;

    try {
        numOfData = myCobs.encode(encodingOutput,
                                  sizeof(encodingOutput),
                                  data,
                                  sizeof(data));
    } catch(CobsErrors &e) {
        err = e;
    }

    EXPECT_EQ(err, CobsErrors::wontFitToDst);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

