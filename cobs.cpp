#include "cobs.h"

#define COBS_FRAME_DELIM (0u)
#define COBS_DELIM_POINTER_MAX (255u)
#define COBS_MAX_DATA_SIZE (254u)
#define COBS_TEMP_DATA (COBS_FRAME_DELIM)

using namespace std;

namespace cobs {
uint64_t encode(uint8_t *const dst, uint64_t dstLen, const uint8_t *const src, uint64_t srcLen)
{
    struct frame {
        uint64_t insertedCount;
        uint8_t *const buf;

        frame(uint8_t *buf):
            insertedCount{0},
            buf{buf}
        {}

        void insert(uint8_t data)
        {
            buf[insertedCount] = data;
            ++insertedCount;
        }
    };

    uint64_t delimPointer = 1u;
    uint64_t lastDelimIdx = 0u;
    frame f {dst};

    if(dst == nullptr || src == nullptr) {
        throw Exceptions::nullPtr;
    }

    if(srcLen == 0u) {
        throw Exceptions::emptySrcToEncode;
    }

    if(srcLen > COBS_MAX_DATA_SIZE) {
        throw Exceptions::srcTooLong;
    }

    if(srcLen + COBS_OVERHEAD_BYTE_COUNT > dstLen) {
        throw Exceptions::wontFitToDst;
    }

    f.insert(COBS_FRAME_DELIM);

    for(uint64_t i = 0u; i < srcLen; ++i) {
        uint8_t u8 = src[i];

        if(u8 != COBS_FRAME_DELIM) {
            f.insert(u8);
            delimPointer++;
        } else {
            dst[lastDelimIdx] = delimPointer;
            delimPointer = 1u;
            lastDelimIdx = f.insertedCount;
            f.insert(COBS_TEMP_DATA);
        }
    }

    dst[lastDelimIdx] = delimPointer;

    f.insert(COBS_FRAME_DELIM);
    return f.insertedCount;
}

uint64_t decode(uint8_t *const dst, uint64_t dstLen, const uint8_t *const src, uint64_t srcLen)
{
    uint64_t dataIdx = 0u;
    uint64_t delimIdx;

    if(dst == nullptr || src == nullptr) {
        throw Exceptions::nullPtr;
    }

    if((srcLen <= COBS_OVERHEAD_BYTE_COUNT) ||
        (src[srcLen-1] != COBS_FRAME_DELIM) ||
        (src[0] == 0u)) {
        throw Exceptions::invalidFrame;
    }

    if(srcLen > COBS_MAX_DATA_SIZE + COBS_OVERHEAD_BYTE_COUNT) {
        throw Exceptions::srcTooLong;
    }

    if(dstLen < srcLen-COBS_OVERHEAD_BYTE_COUNT) {
        throw Exceptions::wontFitToDst;
    }

    delimIdx = src[0];

    for(uint64_t srcIdx = 1u; srcIdx < srcLen-1; ++srcIdx) {
        if(delimIdx == srcIdx) {
            dst[dataIdx] = COBS_FRAME_DELIM;
            delimIdx += src[srcIdx];
            if(delimIdx >= srcLen) {
                throw Exceptions::invalidFrame;
            }
        } else {
            dst[dataIdx] = src[srcIdx];
        }
        dataIdx++;
    }

    return dataIdx;
}
} // namespace cobs
