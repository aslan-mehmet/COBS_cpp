#include "cobs.h"


void cobs::encode(std::vector<uint8_t> &dst, const uint8_t *const src, uint64_t srcLen)
{
    uint64_t delimPointer = 1u;
    uint64_t lastPacketDelimIdx = 0u;
    uint64_t packetIdx = 0u;

    if(srcLen > maxDataSize) {
        throw std::out_of_range("unsupported data size. decrease size");
    }

    dst.push_back(packetDelim);
    packetIdx++;

    for(uint64_t i = 0u; i < srcLen; ++i) {
        uint8_t u8 = src[i];

        if(u8 != packetDelim) {
            dst.push_back(u8);
            delimPointer++;
        } else {
            delimPointer <= delimPointerMax ?
            dst[lastPacketDelimIdx] = delimPointer :
            throw std::runtime_error("delimiter pointer overflow");

            delimPointer = 1u;
            dst.push_back(packetDelim);
            lastPacketDelimIdx = packetIdx;
        }

        packetIdx++;
    }

    delimPointer <= delimPointerMax ?
    dst[lastPacketDelimIdx] = delimPointer :
    throw std::runtime_error("delimiter pointer overflow");

    dst.push_back(packetDelim);
}

void cobs::decode(uint8_t *dst, uint64_t dstLen, const std::vector<uint8_t> &src)
{
    uint64_t dataIdx = 0u;
    uint64_t delimIdx = src[0];

    if(dstLen != (src.size()-2)) {
        throw std::out_of_range("data and encoded are not compatible");
    }

    if(dstLen > maxDataSize) {
        throw std::out_of_range("unsupported data size. decrease size");
    }

    if(src[src.size()-1] != packetDelim) {
        throw std::runtime_error("invalid encoded data. last item in encoded data should be packet delimiter");
    }

    for(uint64_t srcIdx = 1u; srcIdx < src.size()-1; ++srcIdx) {
        if(delimIdx == srcIdx) {
            dst[dataIdx] = packetDelim;
            delimIdx += src[srcIdx];
        } else {
            dst[dataIdx] = src[srcIdx];
        }
        dataIdx++;
    }
}
