#include <gtest/gtest.h>
#include "cobs.h"

TEST(DecodingTests, ResultStructDefaulValTest)
{
    COBS::decode_result result;
    EXPECT_EQ(0, result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_input_too_short);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_FALSE(result.status.err_ok);
}

TEST(DecodingTests, SrcNullPtrTest)
{
    uint8_t data[4];
    COBS::decode_result result;
    COBS myCOBS;

    result = myCOBS.decode((void *)data, sizeof(data), (void *)nullptr, 10);
    EXPECT_EQ(0, result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_input_too_short);
    EXPECT_TRUE(result.status.err_null_ptr);
    EXPECT_FALSE(result.status.err_ok);
}

TEST(DecodingTests, DstNullPtrTest)
{
    uint8_t encoded_data[6] = {0x05, 0x11, 0x22, 0x33, 0x44, 0x00};
    COBS::decode_result result;
    COBS myCOBS;

    result = myCOBS.decode((void *)nullptr, 10, (void *)encoded_data, sizeof(encoded_data));
    EXPECT_EQ(0, result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_input_too_short);
    EXPECT_TRUE(result.status.err_null_ptr);
    EXPECT_FALSE(result.status.err_ok);
}

TEST(DecodingTests, DstBfrOvfTest)
{
    uint8_t encoded_data[6] = {0x05, 0x11, 0x22, 0x33, 0x44, 0x00};
    uint8_t data[3];
    COBS::decode_result result;
    COBS myCOBS;

    result = myCOBS.decode((void *)data, sizeof(data), (void *)encoded_data, sizeof(encoded_data));
    EXPECT_EQ(0, result.len);
    EXPECT_TRUE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_input_too_short);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_FALSE(result.status.err_ok);
}

TEST(DecodingTests, InputTooShortTest)
{
    uint8_t encoded_data[2] = {0x01, 0x00};
    uint8_t data[4];
    COBS::decode_result result;
    COBS myCOBS;

    result = myCOBS.decode((void *)data, sizeof(data), (void *)encoded_data, sizeof(encoded_data));
    EXPECT_EQ(0, result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_TRUE(result.status.err_input_too_short);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_FALSE(result.status.err_ok);
}

TEST(DecodingTests, DestinationLengthTest)
{
    uint8_t encoded_data[6] = {0x05, 0x11, 0x22, 0x33, 0x44, 0x00};
    uint8_t data[40];
    uint8_t expected_data[4] = {0x11, 0x22, 0x33, 0x44};
    COBS::decode_result result;
    COBS myCOBS;

    result = myCOBS.decode((void *)data, sizeof(data), (void *)encoded_data, sizeof(encoded_data));
    EXPECT_EQ(sizeof(expected_data), result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_input_too_short);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_TRUE(result.status.err_ok);

    for (int i = 0; i < sizeof(expected_data); ++i)
        EXPECT_EQ(expected_data[i], data[i]);
}

TEST(DecodingTests, DecodeDataTest1)
{
    uint8_t encoded_data[] = {0x01, 0x01, 0x00};
    uint8_t data[1];
    uint8_t expected_data[1] = {0x00};
    COBS::decode_result result;
    COBS myCOBS;

    result = myCOBS.decode((void *)data, sizeof(data), (void *)encoded_data, sizeof(encoded_data));
    EXPECT_EQ(sizeof(expected_data), result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_input_too_short);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_TRUE(result.status.err_ok);

    for (int i = 0; i < sizeof(expected_data); ++i)
        EXPECT_EQ(expected_data[i], data[i]);
}

TEST(DecodingTests, DecodeDataTest2)
{
    uint8_t encoded_data[4] = {0x01, 0x01, 0x01, 0x00};
    uint8_t data[2];
    uint8_t expected_data[2] = {0x00, 0x00};
    COBS::decode_result result;
    COBS myCOBS;

    result = myCOBS.decode((void *)data, sizeof(data), (void *)encoded_data, sizeof(encoded_data));
    EXPECT_EQ(sizeof(expected_data), result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_input_too_short);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_TRUE(result.status.err_ok);

    for (int i = 0; i < sizeof(expected_data); ++i)
        EXPECT_EQ(expected_data[i], data[i]);
}

TEST(DecodingTests, DecodeDataTest3)
{
    uint8_t encoded_data[6] = {0x03, 0x11, 0x22, 0x02, 0x33, 0x00};
    uint8_t data[4];
    uint8_t expected_data[4] = {0x11, 0x22, 0x00, 0x33};
    COBS::decode_result result;
    COBS myCOBS;

    result = myCOBS.decode((void *)data, sizeof(data), (void *)encoded_data, sizeof(encoded_data));
    EXPECT_EQ(sizeof(expected_data), result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_input_too_short);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_TRUE(result.status.err_ok);

    for (int i = 0; i < sizeof(expected_data); ++i)
        EXPECT_EQ(expected_data[i], data[i]);
}

TEST(DecodingTests, DecodeDataTest4)
{
    uint8_t encoded_data[6] = {0x05, 0x11, 0x22, 0x33, 0x44, 0x00};
    uint8_t data[4];
    uint8_t expected_data[4] = {0x11, 0x22, 0x33, 0x44};
    COBS::decode_result result;
    COBS myCOBS;

    result = myCOBS.decode((void *)data, sizeof(data), (void *)encoded_data, sizeof(encoded_data));
    EXPECT_EQ(sizeof(expected_data), result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_input_too_short);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_TRUE(result.status.err_ok);

    for (int i = 0; i < sizeof(expected_data); ++i)
        EXPECT_EQ(expected_data[i], data[i]);
}

TEST(DecodingTests, DecodeDataTest5)
{
    uint8_t encoded_data[6] = {0x02, 0x11, 0x01, 0x01, 0x01, 0x00};
    uint8_t data[4];
    uint8_t expected_data[4] = {0x11, 0x00, 0x00, 0x00};
    COBS::decode_result result;
    COBS myCOBS;

    result = myCOBS.decode((void *)data, sizeof(data), (void *)encoded_data, sizeof(encoded_data));
    EXPECT_EQ(sizeof(expected_data), result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_input_too_short);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_TRUE(result.status.err_ok);

    for (int i = 0; i < sizeof(expected_data); ++i)
        EXPECT_EQ(expected_data[i], data[i]);
}

TEST(DecodingTests, DecodeDataTest6)
{
    uint8_t encoded_data[256]; //0xff, 0x01, 0x02, ... , 0xfd, 0xfe, 0x00
    encoded_data[0] = 0xff;
    encoded_data[255] = 0x00;
    for (int i = 0x01; i <= 0xfe; ++i)
        encoded_data[i] = i;
    uint8_t data[254];
    uint8_t expected_data[254]; //0x01, 0x02, .... , 0xfd, 0xfe
    for (int i = 0x01; i <= 0xfe; ++i)
        expected_data[i-1] = i;
    COBS::decode_result result;
    COBS myCOBS;

    result = myCOBS.decode((void *)data, sizeof(data), (void *)encoded_data, sizeof(encoded_data));
    EXPECT_EQ(sizeof(expected_data), result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_input_too_short);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_TRUE(result.status.err_ok);

    for (int i = 0; i < sizeof(expected_data); ++i)
        EXPECT_EQ(expected_data[i], data[i]);
}

TEST(DecodingTests, DecodeDataTest7)
{
    uint8_t encoded_data[257]; //0x01, 0xff, 0x01, 0x02, ... , 0xfd, 0xfe, 0x00
    encoded_data[0] = 0x01;
    encoded_data[1] = 0xff;
    encoded_data[256] = 0x00;
    for (int i = 0x01; i <= 0xfe; ++i)
        encoded_data[i+1] = i;
    uint8_t data[255];
    uint8_t expected_data[255]; //0x00, 0x01, 0x02, .... , 0xfd, 0xfe
    for (int i = 0x00; i <= 0xfe; ++i)
        expected_data[i] = i;
    COBS::decode_result result;
    COBS myCOBS;

    result = myCOBS.decode((void *)data, sizeof(data), (void *)encoded_data, sizeof(encoded_data));
    EXPECT_EQ(sizeof(expected_data), result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_input_too_short);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_TRUE(result.status.err_ok);

    for (int i = 0; i < sizeof(expected_data); ++i)
        EXPECT_EQ(expected_data[i], data[i]);
}

TEST(DecodingTests, DecodeDataTest8)
{
    uint8_t encoded_data[258]; //0xff, 0x01, 0x02, ... , 0xfd, 0xfe, 0x02, 0xff, 0x00
    encoded_data[0] = 0xff;
    encoded_data[255] = 0x02;
    encoded_data[256] = 0xff;
    encoded_data[257] = 0x00;
    for (int i = 0x01; i <= 0xfe; ++i)
        encoded_data[i] = i;
    uint8_t data[255];
    uint8_t expected_data[255]; //0x01, 0x02, .... , 0xfd, 0xfe, 0xff
    for (int i = 0x01; i <= 0xff; ++i)
        expected_data[i-1] = i;
    COBS::decode_result result;
    COBS myCOBS;

    result = myCOBS.decode((void *)data, sizeof(data), (void *)encoded_data, sizeof(encoded_data));
    EXPECT_EQ(sizeof(expected_data), result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_input_too_short);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_TRUE(result.status.err_ok);

    for (int i = 0; i < sizeof(expected_data); ++i)
        EXPECT_EQ(expected_data[i], data[i]);
}

TEST(DecodingTests, DecodeDataTest9)
{
    uint8_t encoded_data[258]; //0xff, 0x02, 0x03 ... , 0xfe, 0xff, 0x01, 0x01, 0x00
    encoded_data[0] = 0xff;
    encoded_data[255] = 0x01;
    encoded_data[256] = 0x01;
    encoded_data[257] = 0x00;
    for (int i = 0x02; i <= 0xff; ++i)
        encoded_data[i-1] = i;
    uint8_t data[255];
    uint8_t expected_data[255]; //0x02, 0x03, .... , 0xfd, 0xfe, 0xff, 0x00
    expected_data[254] = 0x00;
    for (int i = 0x02; i <= 0xff; ++i)
        expected_data[i-2] = i;
    COBS::decode_result result;
    COBS myCOBS;

    result = myCOBS.decode((void *)data, sizeof(data), (void *)encoded_data, sizeof(encoded_data));
    EXPECT_EQ(sizeof(expected_data), result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_input_too_short);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_TRUE(result.status.err_ok);

    for (int i = 0; i < sizeof(expected_data); ++i)
        EXPECT_EQ(expected_data[i], data[i]);
}

TEST(DecodingTests, DecodeDataTest10)
{
    uint8_t encoded_data[257]; //0xfe, 0x03, 0x04 ... , 0xfe, 0xff, 0x02, 0x01, 0x00
    encoded_data[0] = 0xfe;
    encoded_data[254] = 0x02;
    encoded_data[255] = 0x01;
    encoded_data[256] = 0x00;
    for (int i = 0x03; i <= 0xff; ++i)
        encoded_data[i-2] = i;
    uint8_t data[255];
    uint8_t expected_data[255]; //0x03, 0x04, .... , 0xfd, 0xfe, 0xff, 0x00, 0x01
    expected_data[253] = 0x00;
    expected_data[254] = 0x01;
    for (int i = 0x03; i <= 0xff; ++i)
        expected_data[i-3] = i;
    COBS::decode_result result;
    COBS myCOBS;

    result = myCOBS.decode((void *)data, sizeof(data), (void *)encoded_data, sizeof(encoded_data));
    EXPECT_EQ(sizeof(expected_data), result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_input_too_short);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_TRUE(result.status.err_ok);

    for (int i = 0; i < sizeof(expected_data); ++i)
        EXPECT_EQ(expected_data[i], data[i]);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

