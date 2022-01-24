#pragma once
#include <stddef.h>

void catch_array_index_out_of_bounds_exception(const size_t size, size_t index);

/**
 * @brief Returns if an index is inside of array bounds
 */
template<typename T>
inline bool is_in_bounds(size_t size, size_t index) {
    return index < (size * sizeof(T));
}

/**
 * @brief Returns if an index is inside of array bounds
 */
template<typename T>
inline bool is_in_bounds(size_t size, T* arr, size_t index) {
    return index < (size * sizeof(T));
}

/**
 * @brief Catches an array index out of bounds exception if the index is out of bounds
 * 
 * @return T& The value at the index
 */
template<typename T>
inline T& at(const size_t size, T* array, size_t index) {
    if (index >= (size * sizeof(T))) {
        catch_array_index_out_of_bounds_exception(size, index);
    }
    return array[index];
}