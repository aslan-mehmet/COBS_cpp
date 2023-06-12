# Consistent Overhead Byte Stuffing(COBS) Library (C++)

## How To Use Library
Just copy and paste cobs.cpp and cobs.h to your project. No dependencies.  

Encoding Example:
```
#include <cstring>
#include "cobs.h"

using namespace cobs;

int main(void) {
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
    return isSame;
}
```
## How Implementation Works

![Encoded output examples and explanation](./docs/encoding_examples.png)
[Original link to wikipedia article](https://en.wikipedia.org/wiki/Consistent_Overhead_Byte_Stuffing)

## How To Run Tests
Tests use testing framework(gtest) by google. Install gtest. Run:  
```
$ cd tests 
$ make
```