#include "cobs.h"

#define COBS_PACKET_DELIM (0u)
#define COBS_DELIM_POINTER_MAX (255u)
#define COBS_MAX_DATA_SIZE (254u)

using namespace std;

void cobs::encode(vector<uint8_t> &dst, const uint8_t *const src, uint64_t srcLen)
{
    uint64_t delimPointer = 1u;
    uint64_t lastPacketDelimIdx = 0u;
    uint64_t packetIdx = 0u;

    if(srcLen > COBS_MAX_DATA_SIZE) {
        throw out_of_range("unsupported data size. decrease size");
    }

    dst.clear();

    dst.push_back(COBS_PACKET_DELIM);
    packetIdx++;

    for(uint64_t i = 0u; i < srcLen; ++i) {
        uint8_t u8 = src[i];

        if(u8 != COBS_PACKET_DELIM) {
            dst.push_back(u8);
            delimPointer++;
        } else {
            delimPointer <= COBS_DELIM_POINTER_MAX ?
            dst[lastPacketDelimIdx] = delimPointer :
            throw runtime_error("delimiter pointer overflow");

            delimPointer = 1u;
            dst.push_back(COBS_PACKET_DELIM);
            lastPacketDelimIdx = packetIdx;
        }

        packetIdx++;
    }

    delimPointer <= COBS_DELIM_POINTER_MAX ?
    dst[lastPacketDelimIdx] = delimPointer :
    throw runtime_error("delimiter pointer overflow");

    dst.push_back(COBS_PACKET_DELIM);
}

void cobs::decode(uint8_t *dst, uint64_t dstLen, const vector<uint8_t> &src)
{
    uint64_t dataIdx = 0u;
    uint64_t delimIdx = src[0];

    if(dstLen != (src.size()-2)) {
        throw out_of_range("data and encoded are not compatible");
    }

    if(dstLen > COBS_MAX_DATA_SIZE) {
        throw out_of_range("unsupported data size. decrease size");
    }

    if(src[src.size()-1] != COBS_PACKET_DELIM) {
        throw runtime_error("invalid encoded data. last item in encoded data should be packet delimiter");
    }

    for(uint64_t srcIdx = 1u; srcIdx < src.size()-1; ++srcIdx) {
        if(delimIdx == srcIdx) {
            dst[dataIdx] = COBS_PACKET_DELIM;
            delimIdx += src[srcIdx];
        } else {
            dst[dataIdx] = src[srcIdx];
        }
        dataIdx++;
    }
}
