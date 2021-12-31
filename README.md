# Consistent Overhead Byte Stuffing(COBS) Library (C++)

## How To Use Library
Just copy and paste cobs.cpp and cobs.h to your project. No dependencies.  

Encoding Example:
```
#include "cobs.h"

int main(void)
{
    uint8_t retVal = 0;
    uint8_t data[] = {0x11, 0x22};
    uint8_t encoded_output[4];
    COBS::encode_result result;
    COBS myCOBS;

    result = myCOBS.encode((void *)encoded_output,
                           sizeof(encoded_output),
                           (void *)data,
                           sizeof(data));
    if (!result.status.err_ok) {
        retVal = 1;
    }
    return retVal;
}
```
Decoding Example:
```
#include "cobs.h"

int main(void)
{
    uint8_t retVal = 0;
    uint8_t encoded_input_data[] = {0x03, 0x11, 0x22, 0x00};
    uint8_t data[2];
    COBS::decode_result result;
    COBS myCOBS;

    result = myCOBS.decode((void *)data,
                            sizeof(data),
                            (void *)encoded_input_data,
                            sizeof(encoded_input_data));
    if (!result.status.err_ok) {
        retVal = 1;
    }
    return retVal;
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