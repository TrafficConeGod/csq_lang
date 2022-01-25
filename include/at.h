#pragma once
#include <stddef.h>

void catch_array_index_out_of_bounds_exception(const size_t size, size_t index);

/**
 * @brief Returns if an index is inside of array bounds
 */
inline bool is_in_bounds(size_t size, size_t index) {
    return index < size;
}

/**
 * @brief Catches an array index out of bounds exception if the index is out of bounds
 * 
 * @return T& The value at the index
 */
template<typename T>
inline T& at(const size_t size, T* array, size_t index) {
    if (!is_in_bounds(size, index)) {
        catch_array_index_out_of_bounds_exception(size, index);
    }
    return array[index];
}