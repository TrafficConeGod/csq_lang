#pragma once
#include <stddef.h>

void catch_array_index_out_of_bounds_exception(const size_t size, size_t index);

/**
 * @brief Returns if an index is inside of array bounds
 */
template<typename T>
inline bool is_in_bounds(const size_t size, T* array, size_t index) {
    return index < size;
}

/**
 * @brief Result for the following function
 */
template<typename T>
struct at_result { 
    T& value;
    bool success;
};
/**
 * @brief Gets the value at a specific index in an array
 * 
 * @return at_result<T> A pair of the result and if it succeeded
 */
template<typename T>
inline at_result<T> at(const size_t size, T* array, size_t index) {
    if (index >= size) {
        T value;
        return { value, false };
    } else {
        return { array[index], true };
    }
}

/**
 * @brief Catches an array index out of bounds exception if the index is out of bounds
 * 
 * @return T& The value at the index
 */
template<typename T>
inline T& caught_at(const size_t size, T* array, size_t index) {
    if (index >= size) {
        catch_array_index_out_of_bounds_exception(size, index);
    }
    return array[index];
}