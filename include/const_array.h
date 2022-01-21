#pragma once
#include <stdio.h>
#include "at.h"

/**
 * @brief An array with constant size and constant pointer to data
 */
template<typename T>
struct const_array {
    const size_t size;
    T* const data;

    inline explicit operator const_array<const T>() const {
        return *(const_array<const T>*)this;
    }
};

template<typename T, typename U>
void copy_array_range(const_array<T> arr, U* out, size_t size) {
    if (!is_in_bounds(arr.size, arr.data, size - 1)) { catch_array_index_out_of_bounds_exception(arr.size, size); }
    if (!is_in_bounds(out->size, out->data, size - 1)) { catch_array_index_out_of_bounds_exception(out->size, size); }
    
    memcpy(out->data, arr.data, size * sizeof(T));
}

template<typename T, typename U>
void copy_array_range(const_array<T> arr, size_t arr_start, U* out, size_t out_start, size_t size) {
    if (!is_in_bounds(arr.size, arr.data, arr_start)) { catch_array_index_out_of_bounds_exception(arr.size, arr_start); }
    if (!is_in_bounds(out->size, out->data, out_start)) { catch_array_index_out_of_bounds_exception(out->size, out_start); }
    if (!is_in_bounds(arr.size, arr.data, arr_start + size - 1)) { catch_array_index_out_of_bounds_exception(arr.size, arr_start + size - 1); }
    if (!is_in_bounds(out->size, out->data, out_start + size - 1)) { catch_array_index_out_of_bounds_exception(out->size, out_start + size - 1); }
    
    memcpy(&out->data[out_start], &arr.data[arr_start], size * sizeof(T));
}