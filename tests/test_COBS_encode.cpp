#include <gtest/gtest.h>
#include "cobs.h"

TEST(EncodingTests, ResultStructDefaulValTest)
{
    COBS::encode_result result;
    EXPECT_EQ(0, result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_empty_source);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_FALSE(result.status.err_ok);
}

TEST(EncodingTests, SrcNullPtrTest)
{
    uint8_t *data = nullptr;
    uint8_t encoding_output[6];
    COBS::encode_result result;
    COBS myCOBS;

    result = myCOBS.encode((void *) encoding_output, sizeof(encoding_output), (void *)data, 10);
    
    EXPECT_EQ(0, result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_empty_source);
    EXPECT_TRUE(result.status.err_null_ptr);
    EXPECT_FALSE(result.status.err_ok);
}

TEST(EncodingTests, DstNullPtrTest)
{
    uint8_t data[] = {0x11, 0x22, 0x33, 0x44};
    uint8_t *encoding_output = nullptr;
    COBS::encode_result result;
    COBS myCOBS;

    result = myCOBS.encode((void *) encoding_output, 20, (void *)data, sizeof(data));
    
    EXPECT_EQ(0, result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_empty_source);
    EXPECT_TRUE(result.status.err_null_ptr);
    EXPECT_FALSE(result.status.err_ok);
}

TEST(EncodingTests, DstOverflowTest)
{
    uint8_t data[] = {0x11, 0x22, 0x33, 0x44};
    uint8_t encoding_output[4];
    COBS::encode_result result;
    COBS myCOBS;

    result = myCOBS.encode((void *) encoding_output, sizeof(encoding_output), (void *)data, sizeof(data));
    
    EXPECT_EQ(0, result.len);
    EXPECT_TRUE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_empty_source);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_FALSE(result.status.err_ok);
}

TEST(EncodingTests, EmptySrcTest)
{
    uint8_t data[] = {0x11, 0x22, 0x33, 0x44};
    uint8_t encoding_output[6];
    COBS::encode_result result;
    COBS myCOBS;

    result = myCOBS.encode((void *) encoding_output, sizeof(encoding_output), (void *)data, 0);
    
    EXPECT_EQ(0, result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_TRUE(result.status.err_empty_source);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_FALSE(result.status.err_ok);
}

TEST(EncodingTests, DestinationLengthTest)
{
    uint8_t data[4] = {0x11, 0x22, 0x33, 0x44};
    uint8_t encoding_output[60];
    uint8_t expected_output[6] = {0x05, 0x11, 0x22, 0x33, 0x44, 0x00};
    COBS::encode_result result;
    COBS myCOBS;

    result = myCOBS.encode((void *) encoding_output, sizeof(encoding_output), (void *)data, sizeof(data));
    
    EXPECT_EQ(sizeof(expected_output), result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_empty_source);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_TRUE(result.status.err_ok);

    for (int i = 0; i < sizeof(expected_output); ++i)
        EXPECT_EQ(encoding_output[i], expected_output[i]);
}

TEST(EncodingTests, EncodeDataTest1)
{
    uint8_t data[] = {0x00};
    uint8_t encoding_output[3];
    uint8_t expected_output[3] = {0x01, 0x01, 0x00};
    COBS::encode_result result;
    COBS myCOBS;

    result = myCOBS.encode((void *) encoding_output, sizeof(encoding_output), (void *)data, sizeof(data));
    
    EXPECT_EQ(sizeof(expected_output), result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_empty_source);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_TRUE(result.status.err_ok);

    for (int i = 0; i < sizeof(expected_output); ++i)
        EXPECT_EQ(encoding_output[i], expected_output[i]);
}

TEST(EncodingTests, EncodeDataTest2)
{
    uint8_t data[] = {0x00, 0x00};
    uint8_t encoding_output[4];
    uint8_t expected_output[4] = {0x01, 0x01, 0x01, 0x00};
    COBS::encode_result result;
    COBS myCOBS;

    result = myCOBS.encode((void *) encoding_output, sizeof(encoding_output), (void *)data, sizeof(data));
    
    EXPECT_EQ(sizeof(expected_output), result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_empty_source);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_TRUE(result.status.err_ok);

    for (int i = 0; i < sizeof(expected_output); ++i)
        EXPECT_EQ(encoding_output[i], expected_output[i]);
}

TEST(EncodingTests, EncodeDataTest3)
{
    uint8_t data[4] = {0x11, 0x22, 0x00, 0x33};
    uint8_t encoding_output[6];
    uint8_t expected_output[6] = {0x03, 0x11, 0x22, 0x02, 0x33, 0x00};
    COBS::encode_result result;
    COBS myCOBS;

    result = myCOBS.encode((void *) encoding_output, sizeof(encoding_output), (void *)data, sizeof(data));
    
    EXPECT_EQ(sizeof(expected_output), result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_empty_source);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_TRUE(result.status.err_ok);

    for (int i = 0; i < sizeof(expected_output); ++i)
        EXPECT_EQ(encoding_output[i], expected_output[i]);
}

TEST(EncodingTests, EncodeDataTest4)
{
    uint8_t data[4] = {0x11, 0x22, 0x33, 0x44};
    uint8_t encoding_output[6];
    uint8_t expected_output[6] = {0x05, 0x11, 0x22, 0x33, 0x44, 0x00};
    COBS::encode_result result;
    COBS myCOBS;

    result = myCOBS.encode((void *) encoding_output, sizeof(encoding_output), (void *)data, sizeof(data));
    
    EXPECT_EQ(sizeof(expected_output), result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_empty_source);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_TRUE(result.status.err_ok);

    for (int i = 0; i < sizeof(expected_output); ++i)
        EXPECT_EQ(encoding_output[i], expected_output[i]);
}

TEST(EncodingTests, EncodeDataTest5)
{
    uint8_t data[4] = {0x11, 0x00, 0x00, 0x00};
    uint8_t encoding_output[6];
    uint8_t expected_output[6] = {0x02, 0x11, 0x01, 0x01, 0x01, 0x00};
    COBS::encode_result result;
    COBS myCOBS;

    result = myCOBS.encode((void *) encoding_output, sizeof(encoding_output), (void *)data, sizeof(data));
    
    EXPECT_EQ(sizeof(expected_output), result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_empty_source);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_TRUE(result.status.err_ok);

    for (int i = 0; i < sizeof(expected_output); ++i)
        EXPECT_EQ(encoding_output[i], expected_output[i]);
}

TEST(EncodingTests, EncodeDataTest6)
{
    uint8_t data[254]; //0x01, 0x02, .... , 0xfd, 0xfe
    for (int i = 0x01; i <= 0xfe; ++i)
        data[i-1] = i;
    uint8_t encoding_output[256];
    uint8_t expected_output[256]; //0xff, 0x01, 0x02, ... , 0xfd, 0xfe, 0x00
    expected_output[0] = 0xff;
    expected_output[255] = 0x00;
    for (int i = 0x01; i <= 0xfe; ++i)
        expected_output[i] = i;
    COBS::encode_result result;
    COBS myCOBS;

    result = myCOBS.encode((void *) encoding_output, sizeof(encoding_output), (void *)data, sizeof(data));
    
    EXPECT_EQ(sizeof(expected_output), result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_empty_source);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_TRUE(result.status.err_ok);

    for (int i = 0; i < sizeof(expected_output); ++i)
        EXPECT_EQ(encoding_output[i], expected_output[i]);
}

TEST(EncodingTests, EncodeDataTest7)
{
    uint8_t data[255]; //0x00, 0x01, 0x02, .... , 0xfd, 0xfe
    for (int i = 0x00; i <= 0xfe; ++i)
        data[i] = i;
    uint8_t encoding_output[257];
    uint8_t expected_output[257]; //0x01, 0xff, 0x01, 0x02, ... , 0xfd, 0xfe, 0x00
    expected_output[0] = 0x01;
    expected_output[1] = 0xff;
    expected_output[256] = 0x00;
    for (int i = 0x01; i <= 0xfe; ++i)
        expected_output[i+1] = i;
    COBS::encode_result result;
    COBS myCOBS;

    result = myCOBS.encode((void *) encoding_output, sizeof(encoding_output), (void *)data, sizeof(data));
    
    EXPECT_EQ(sizeof(expected_output), result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_empty_source);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_TRUE(result.status.err_ok);

    for (int i = 0; i < sizeof(expected_output); ++i)
        EXPECT_EQ(encoding_output[i], expected_output[i]);
}

TEST(EncodingTests, EncodeDataTest8)
{
    uint8_t data[255]; //0x01, 0x02, .... , 0xfd, 0xfe, 0xff
    for (int i = 0x01; i <= 0xff; ++i)
        data[i-1] = i;
    uint8_t encoding_output[258];
    uint8_t expected_output[258]; //0xff, 0x01, 0x02, ... , 0xfd, 0xfe, 0x02, 0xff, 0x00
    expected_output[0] = 0xff;
    expected_output[255] = 0x02;
    expected_output[256] = 0xff;
    expected_output[257] = 0x00;
    for (int i = 0x01; i <= 0xfe; ++i)
        expected_output[i] = i;
    COBS::encode_result result;
    COBS myCOBS;

    result = myCOBS.encode((void *) encoding_output, sizeof(encoding_output), (void *)data, sizeof(data));
    
    EXPECT_EQ(sizeof(expected_output), result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_empty_source);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_TRUE(result.status.err_ok);

    for (int i = 0; i < sizeof(expected_output); ++i)
        EXPECT_EQ(encoding_output[i], expected_output[i]);
}

TEST(EncodingTests, EncodeDataTest9)
{
    uint8_t data[255]; //0x02, 0x03, .... , 0xfd, 0xfe, 0xff, 0x00
    data[254] = 0x00;
    for (int i = 0x02; i <= 0xff; ++i)
        data[i-2] = i;
    uint8_t encoding_output[258];
    uint8_t expected_output[258]; //0xff, 0x02, 0x03 ... , 0xfe, 0xff, 0x01, 0x01, 0x00
    expected_output[0] = 0xff;
    expected_output[255] = 0x01;
    expected_output[256] = 0x01;
    expected_output[257] = 0x00;
    for (int i = 0x02; i <= 0xff; ++i)
        expected_output[i-1] = i;
    COBS::encode_result result;
    COBS myCOBS;

    result = myCOBS.encode((void *) encoding_output, sizeof(encoding_output), (void *)data, sizeof(data));
    
    EXPECT_EQ(sizeof(expected_output), result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_empty_source);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_TRUE(result.status.err_ok);

    for (int i = 0; i < sizeof(expected_output); ++i)
        EXPECT_EQ(encoding_output[i], expected_output[i]);
}

TEST(EncodingTests, EncodeDataTest10)
{
    uint8_t data[255]; //0x03, 0x04, .... , 0xfd, 0xfe, 0xff, 0x00, 0x01
    data[253] = 0x00;
    data[254] = 0x01;
    for (int i = 0x03; i <= 0xff; ++i)
        data[i-3] = i;
    uint8_t encoding_output[257];
    uint8_t expected_output[257]; //0xfe, 0x03, 0x04 ... , 0xfe, 0xff, 0x02, 0x01, 0x00
    expected_output[0] = 0xfe;
    expected_output[254] = 0x02;
    expected_output[255] = 0x01;
    expected_output[256] = 0x00;
    for (int i = 0x03; i <= 0xff; ++i)
        expected_output[i-2] = i;
    COBS::encode_result result;
    COBS myCOBS;

    result = myCOBS.encode((void *) encoding_output, sizeof(encoding_output), (void *)data, sizeof(data));
    
    EXPECT_EQ(sizeof(expected_output), result.len);
    EXPECT_FALSE(result.status.err_dst_bfr_ovf);
    EXPECT_FALSE(result.status.err_empty_source);
    EXPECT_FALSE(result.status.err_null_ptr);
    EXPECT_TRUE(result.status.err_ok);

    for (int i = 0; i < sizeof(expected_output); ++i)
        EXPECT_EQ(encoding_output[i], expected_output[i]);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

