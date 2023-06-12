#include <gtest/gtest.h>
#include "cobs.h"
#include <cstring>

using namespace cobs;

TEST(High, 1)
{
    bool isSame;
    struct __attribute__((__packed__)) myStruct{
        int i;
        double d;
        float f;
        uint16_t u16;
    };
    myStruct mineTx {
        .i = -1,
        .d = 0.212354,
        .f = 234.124,
        .u16 = 0xffff
    };
    myStruct mineRx;
    std::vector<uint8_t> encoded;

    encode(encoded, mineTx);
    decode(mineRx, encoded);
    isSame = memcmp(&mineRx, &mineTx, sizeof(myStruct)) == 0;
    EXPECT_TRUE(isSame);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

