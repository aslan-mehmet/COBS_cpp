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
#include <cstdint>

#ifndef COBS_H_FILE_
#define COBS_H_FILE_

class COBS {
    private:
        struct encode_error_status {
            bool err_ok: 1; //!< everything is okay
            bool err_null_ptr: 1; //!< null ptr error
            bool err_dst_bfr_ovf: 1; //!< destination buffer overflow
            bool err_empty_source: 1; //!< empty source error, no data to encode
        };

        struct decode_error_status {
            bool err_ok: 1; //!< everything is okay
            bool err_null_ptr: 1; //!< null ptr error
            bool err_dst_bfr_ovf: 1; //!< destination buffer overflowed
            bool err_input_too_short: 1; //!< input does not contain any data error
        };

    public:
        struct encode_result {
            encode_error_status status; //!< bitfield
            uint64_t len; //!< length that is written to destination buffer

            encode_result() { //! initializer
                status = {false, false, false, false};
                len = 0;
            }
        };

        struct decode_result {
            decode_error_status status; //!< bitfield
            uint64_t len; //!< length that is written to destination buffer

            decode_result() { //! initializer
                status = {false, false, false, false};
                len = 0;
            }
        };

        /**
         * @brief Takes source data and encodes with COBS algorithm.  
         * Encoded bytes written to destination. Example:  
         * Input Data: 0x11 0x22  
         * Output Encoded Data: 0x03 0x11 0x22 0x00
         * 
         * @param dst_ptr[out] Encoded data output
         * @param dst_len[in] Destination buffer length
         * @param src_ptr[in] Source data input
         * @param src_len[in] Source buffer length
         * @return encode_result 
         */
        encode_result encode(void *dst_ptr, uint64_t dst_len, const void *src_ptr, uint64_t src_len);
        /**
         * @brief Takes encoded source data and decodes with COBS algorithm.  
         * Decoded bytes written to destination. Example:  
         * Input Encoded Data: 0x03 0x11 0x22 0x00  
         * Output Data: 0x11 0x22
         * 
         * @param dst_ptr[out] Decoded data output
         * @param dst_len[in] Destination buffer length
         * @param src_ptr[in] Encoded source data input
         * @param src_len[in] Source buffer length
         * @return decode_result 
         */
        decode_result decode(void *dst_ptr, uint64_t dst_len, const void *src_ptr, uint64_t src_len);
};

#endif //COBS_H_FILE_