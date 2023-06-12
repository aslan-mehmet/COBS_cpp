#include <gtest/gtest.h>
#include "cobs.h"

using namespace cobs;
using namespace std;

TEST(RawDecoding, 1)
{
    uint8_t encodedData[] = {0x01, 0x01, 0x00};
    uint8_t data[1];
    uint64_t numOfData;
    uint8_t expectedData[] = {0x00};

    numOfData = decode(data, sizeof(data), encodedData, sizeof(encodedData));

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

    numOfData = decode(data, sizeof(data), encodedData, sizeof(encodedData));

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

    numOfData = decode(data, sizeof(data), encodedData, sizeof(encodedData));

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

    numOfData = decode(data, sizeof(data), encodedData, sizeof(encodedData));

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

    numOfData = decode(data, sizeof(data), encodedData, sizeof(encodedData));

    EXPECT_EQ(sizeof(expectedData), numOfData);

    for (int i = 0; i < sizeof(expectedData); ++i)
        EXPECT_EQ(expectedData[i], data[i]);
}

TEST(MakeDecodingFail, srcTooLong) {
    uint8_t encodedData[257] {};
    // a valid encoded data
    for(int i = 0; i < sizeof(encodedData) - 1; ++i) {
        encodedData[i] = 1;
    }
    uint64_t numOfData;
    uint8_t data[500];
    Exceptions err = Exceptions::okay;

    try {
        numOfData = decode(data, sizeof(data), encodedData, sizeof(encodedData));
    } catch(Exceptions &e) {
        err = e;
    }
    EXPECT_EQ(err, Exceptions::srcTooLong);
}

TEST(MakeDecodingFail, dstNullPtr) {
    uint8_t encodedData[] = {1,1,0};
    Exceptions err = Exceptions::okay;

    try {
        decode(nullptr, 10, encodedData, sizeof(encodedData));
    } catch(Exceptions &e) {
        err = e;
    }

    EXPECT_EQ(err, Exceptions::nullPtr);
}

TEST(MakeDecodingFail, srcNullPtr) {
    uint8_t data[4];
    Exceptions err = Exceptions::okay;

    try {
        decode(data, sizeof(data), nullptr, 6);
    } catch(Exceptions &e) {
        err = e;
    }

    EXPECT_EQ(err, Exceptions::nullPtr);
}

TEST(MakeDecodingFail, wontFitToDst)
{
    uint8_t encodedData[] = {0x02, 0x11, 0x01, 0x01, 0x01, 0x00};
    uint64_t numOfData;
    uint8_t data[2];
    Exceptions err = Exceptions::okay;
    try {
        numOfData = decode(data, sizeof(data), encodedData, sizeof(encodedData));
    } catch(Exceptions &e) {
        err = e;
    }
    EXPECT_EQ(err, Exceptions::wontFitToDst);
}

TEST(MakeDecodingFail, invalidFrameStartByte)
{
    uint8_t encodedData[] = {1,1,1,0};
    encodedData[0] = 0; // invalid frame now
    uint8_t data[500];
    Exceptions err = Exceptions::okay;
    try {
        decode(data, sizeof(data), encodedData, sizeof(encodedData));
    } catch(Exceptions &e) {
        err = e;
    }
    EXPECT_EQ(err, Exceptions::invalidFrame);
}

TEST(MakeDecodingFail, invalidFrameEmptyData)
{
    uint8_t encodedData[] = {1, 0}; // empty data in frame not allowed
    uint8_t data[500];
    Exceptions err = Exceptions::okay;
    try {
        decode(data, sizeof(data), encodedData, sizeof(encodedData));
    } catch(Exceptions &e) {
        err = e;
    }
    EXPECT_EQ(err, Exceptions::invalidFrame);
}

TEST(MakeDecodingFail, invalidFrameLastNotDelim)
{
    uint8_t encodedData[] = {1,1,1,1,6}; // last item is not delimiter
    uint8_t data[500];
    Exceptions err = Exceptions::okay;
    try {
        decode(data, sizeof(data), encodedData, sizeof(encodedData));
    } catch(Exceptions &e) {
        err = e;
    }
    EXPECT_EQ(err, Exceptions::invalidFrame);
}

TEST(MakeDecodingFail, delimAtOutOfBound)
{
    uint8_t encodedData[] = {1,4,1,1,0};
    uint8_t data[500];
    Exceptions err = Exceptions::okay;
    try {
        decode(data, sizeof(data), encodedData, sizeof(encodedData));
    } catch(Exceptions &e) {
        err = e;
    }
    EXPECT_EQ(err, Exceptions::invalidFrame);
}

TEST(MakeDecodingFail, dataSrcNotCompatible)
{
    vector<uint8_t> encodedData {1,1,1,1,0};
    struct dataStruct {
        uint8_t a;
        uint8_t b;
        // encodedData has 3 uint8, when 'c' commented out not compatible
        //uint8_t c;
    };
    dataStruct data;
        Exceptions err = Exceptions::okay;
    try {
        decode(data, encodedData);
    } catch(Exceptions &e) {
        err = e;
    }
    EXPECT_EQ(err, Exceptions::invalidFrame);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

