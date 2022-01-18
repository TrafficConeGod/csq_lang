#pragma once
#include <stddef.h>

void catch_array_index_out_of_bounds_exception(const size_t size, size_t index);

template<typename T>
struct at_result { 
    T& value;
    bool success;
};

template<typename T>
inline at_result<T> at(const size_t size, T* array, size_t index) {
    if (index >= size) {
        T value;
        return { value, false };
    } else {
        return { array[index], true };
    }
}

template<typename T>
inline T& caught_at(const size_t size, T* array, size_t index) {
    if (index >= size) {
        catch_array_index_out_of_bounds_exception(size, index);
    }
    return array[index];
}