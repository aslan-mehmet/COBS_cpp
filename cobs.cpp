/**
 * @file cobs.cpp
 * @author Mehmet Aslan
 * @brief Implementation of interfaces in cobs.h
 * @version 1.0
 * @date 2021-12-31
 * 
 * @copyright Copyright (c) 2021(DO whatEVER you want licenced)
 * 
 */
#include "cobs.h"

//! COBS entry overhead index to point next data zero
#define ENCODED_FIRST_OVERHEAD_BYTE_INDEX ((uint64_t)0u)
//! COBS first data index after entry overhead
#define ENCODED_FIRST_DATA_INDEX ((uint64_t)1u)
//! Relative location size 1 unsigned byte so max 255
#define ENCODED_DATA_ZERO_MAX_RELATIVE_LOCATION ((uint8_t)255u)
//! Entry overhead index and cobs delimeter so 2
#define ENCODED_ARRAY_MIN_SIZE ((uint8_t)2u)
//! Data zero  pointed by overhead bytes
#define COBS_DATA_ZERO ((uint8_t)0u)
//! COBS uses zero as delimeter in encoded output
#define COBS_DELIMETER ((uint8_t)0u)

COBS::decode_result COBS::decode(void *dst_ptr, uint64_t dst_len, const void *src_ptr, uint64_t src_len)
{
    decode_result result;
    uint8_t *u8_dst_arr = (uint8_t *) dst_ptr;
    uint8_t *u8_src_arr = (uint8_t *) src_ptr;
    uint64_t src_remember_index = ENCODED_FIRST_OVERHEAD_BYTE_INDEX;
    uint64_t src_index = ENCODED_FIRST_DATA_INDEX;
    uint64_t dst_index = 0u;

    if ((u8_dst_arr == nullptr) || (u8_src_arr == nullptr)) {
        result.status.err_null_ptr = true;
    } else if (src_len <= ENCODED_ARRAY_MIN_SIZE) { // it is just consist of overhead and delimeter byte dont bother
        result.status.err_input_too_short = true;
    } else {
        // iterate over encoded data, ignore first(overhead) and last(delimeter) byte
        for (; src_index < (src_len - 1); ++src_index) {

            if (dst_index >= dst_len) { //overflow
                result.status.err_dst_bfr_ovf = true;
                break;
            }

            // does relative data zero point to this index
            if (u8_src_arr[src_remember_index] + src_remember_index == src_index) {
                // if relative pointer is not max(which is used point actually another data zero like in 0x1ff)
                if (u8_src_arr[src_remember_index] != ENCODED_DATA_ZERO_MAX_RELATIVE_LOCATION) {
                    u8_dst_arr[dst_index] = COBS_DATA_ZERO; // store the data
                    dst_index++;
                }
                src_remember_index = src_index; // remember relative data zero point index
            } else {
                // not a cobs delimeter just fill it
                u8_dst_arr[dst_index] = u8_src_arr[src_index];
                dst_index++;
            }

        }

        if (result.status.err_dst_bfr_ovf == false) {
            result.status.err_ok = true;
            result.len = dst_index;
        }
    }

    return result;
}

COBS::encode_result COBS::encode(void *dst_ptr, uint64_t dst_len, const void *src_ptr, uint64_t src_len)
{
    encode_result result;
    uint8_t *u8_dst_arr = (uint8_t *) dst_ptr;
    uint8_t *u8_src_arr = (uint8_t *) src_ptr;
    uint64_t dst_remember_index = ENCODED_FIRST_OVERHEAD_BYTE_INDEX;
    uint64_t dst_index = ENCODED_FIRST_DATA_INDEX;
    uint64_t src_index = 0u;
    uint64_t zero_location = 0u;

    if ((u8_dst_arr == nullptr) || (u8_src_arr == nullptr)) {
        result.status.err_null_ptr = true;

    } else if (src_len == 0) { // nothing to encode dont bother
        result.status.err_empty_source = true;

    } else if (dst_len <= ENCODED_ARRAY_MIN_SIZE) { // it is just consist of overhead and delimeter byte dont bother
        result.status.err_dst_bfr_ovf = true;

    } else {
        for (; src_index < src_len; src_index++) {
            uint8_t src_val = u8_src_arr[src_index];
            zero_location++;

            if (dst_index >= dst_len) { // check against overflows
                result.status.err_dst_bfr_ovf = true;
                break;
            }

            // there were 0xfe non-zero data values, to address next relative zero data put 0xff
            if (zero_location == ENCODED_DATA_ZERO_MAX_RELATIVE_LOCATION) {
                u8_dst_arr[dst_remember_index] = zero_location; // store 0xff
                dst_remember_index = dst_index; // last relative data zero point index
                dst_index++;
                zero_location = 1;
            }

            if (src_val != COBS_DELIMETER) { // non cobs delimeter val just fill it
                u8_dst_arr[dst_index] = src_val;
                dst_index++;
            } else {
                u8_dst_arr[dst_remember_index] = zero_location; // fill relative index to data zero
                zero_location = 0;
                dst_remember_index = dst_index; // last relative data zero point index
                dst_index++;
            }


        }

        if (dst_index >= dst_len) { //did it overflow
            result.status.err_dst_bfr_ovf = true;
        } else {
            // packaging of src data successfully finished in for loop
            // just fill end of dst array and relative data zero index
            u8_dst_arr[dst_index] = COBS_DELIMETER;
            dst_index++;
            zero_location++;
            u8_dst_arr[dst_remember_index] = zero_location;
            result.len = dst_index;
            result.status.err_ok = true;
        }

    }
    return result;
}
