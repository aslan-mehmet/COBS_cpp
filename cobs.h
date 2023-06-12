/**
 * @file cobs.h
 * @author Mehmet Aslan
 * @brief COBS(Consistent overhead byte stuffing)
 * Basically implementation of COBS on wikipedia :)
 * https://en.wikipedia.org/wiki/Consistent_Overhead_Byte_Stuffing
 * @details Design Limitations
 * 1. Empty data section in a frame is not allowed
 * 2. Max data size allowed to encoder or decode is 254.
 * @version 2.0
 * @date 2023-06-12
 *
 * @copyright Copyright (c) 2021(DO whatEVER you want licenced)
 *
 */
#ifndef COBS_H_
#define COBS_H_

#include <cstdint>
#include <vector>

#define COBS_OVERHEAD_BYTE_COUNT (2u)

namespace cobs {
//! Exceptions cobs functions can throw
enum class Exceptions {
    okay,
    emptySrcToEncode, //!< empty source to encode
    srcTooLong, //!< source is too long
    nullPtr,
    wontFitToDst, //!< wont fit to destination
    invalidFrame
};

/*!
 * @brief Encode source buffer to destination buffer
 * @param [out] dst    - destination buffer
 * @param [in]  dstLen - size of the destination buffer
 * @param [in]  src    - source buffer
 * @param [in]  srcLen - size of the source buffer
 * @throw cobs::Exceptions
 * @return Number of bytes written to destination buffer
 */
uint64_t encode(uint8_t *const dst, uint64_t dstLen, const uint8_t *const src, uint64_t srcLen);

/*!
 * @brief Encode source data to destination vector
 * @param [out] dst - destination vector. vector will be auto resized
 * @param [in]  src - source data
 * @throw cobs::Exceptions
 */
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

/*!
 * @brief Decode source buffer to destination buffer
 * @param [out] dst    - destination buffer
 * @param [in]  dstLen - size of the destination buffer
 * @param [in]  src    - source buffer
 * @param [in]  srcLen - size of the source buffer
 * @throw cobs::Exceptions
 * @return Number of bytes written to destination buffer
 */
uint64_t decode(uint8_t *const dst, uint64_t dstLen, const uint8_t *const src, uint64_t srcLen);

/*!
 * @brief Decode source vector to destination data
 * @param [out] dst - destination data
 * @param [in]  src - source vector
 * @throw cobs::Exceptions
 */
template <typename data_t>
void decode(data_t &dst, const std::vector<uint8_t> &src)
{
    try {
        if(sizeof(data_t) != (src.size()-COBS_OVERHEAD_BYTE_COUNT)) {
            throw Exceptions::invalidFrame;
        }
        decode(reinterpret_cast<uint8_t *>(&dst),
               sizeof(data_t),
               reinterpret_cast<const uint8_t *const>(&src[0]),
               src.size());
    } catch(...) {
        throw;
    }
}
} // namespace Cobs

#endif //COBS_H_
