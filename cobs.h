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
#include <memory>
#include <stdexcept>

class cobs {
private:
    const uint8_t packetDelim;
    const uint8_t delimPointerMax;
    const uint8_t maxDataSize;
public:
    cobs() :
        packetDelim{0},
        delimPointerMax{255},
        maxDataSize{254}
    {

    }

    void encode(std::vector<uint8_t> &dst, const uint8_t *const src, uint64_t srcLen);

    template <typename data_t>
    void encode(std::vector<uint8_t> &dst, const data_t *const src)
    {
        encode(dst, (uint8_t *)src, sizeof(data_t));
    }

    void decode(uint8_t *dst, uint64_t dstLen, const std::vector<uint8_t> &src);

    template <typename data_t>
    void decode(data_t *dst, const std::vector<uint8_t> &src)
    {
        decode((uint8_t *)dst, sizeof(data_t), src);
    }
};

#endif //COBS_H_
