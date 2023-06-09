/**
 * @file cobs.h
 * @author Mehmet Aslan
 * @brief COBS(Consistent overhead byte stuffing)
 * Basically implementation of COBS on wikipedia :)
 * https://en.wikipedia.org/wiki/Consistent_Overhead_Byte_Stuffing
 * @version 1.0
 * @date 2021-12-31
 *
 * @copyright Copyright (c) 2021(DO whatEVER you want licenced)
 *
 */
#ifndef COBS_HPP_
#define COBS_HPP_

#include <cstdint>
#include <vector>
#include <stdexcept>

#define COBS_OVERHEAD_BYTE_COUNT (2u)

enum class CobsErrors {
    noError,
    emptySrc,
    srcTooLong,
    nullPtr,
    wontFitToDst,
    invalidFrame
};

class Cobs {
public:
    uint64_t encode(uint8_t *dst, uint64_t dstLen, const uint8_t *const src, uint64_t srcLen);

    template <typename data_t>
    void encode(std::vector<uint8_t> &dst, const data_t &src)
    {
        try {
            if(dst.size() != (sizeof(data_t)+COBS_OVERHEAD_BYTE_COUNT)) {
                dst.resize(sizeof(data_t)+COBS_OVERHEAD_BYTE_COUNT);
            }
            encode(reinterpret_cast<uint8_t *>(&dst[0]),
                   dst.size(),
                   reinterpret_cast<const uint8_t *const>(&src),
                   sizeof(data_t));
        } catch(...) {
            throw;
        }
    }

    uint64_t decode(uint8_t *dst, uint64_t dstLen, const uint8_t *const src, uint64_t srcLen);

    template <typename data_t>
    void decode(data_t &dst, const std::vector<uint8_t> &src)
    {
        try {
            if(sizeof(data_t) != (src.size()-COBS_OVERHEAD_BYTE_COUNT)) {
                throw CobsErrors::invalidFrame;
            }
            decode(reinterpret_cast<uint8_t *>(&dst),
                   sizeof(data_t),
                   reinterpret_cast<const uint8_t *const>(&src[0]),
                   src.size());
        } catch(...) {
            throw;
        }
    }
};

#endif //COBS_H_
