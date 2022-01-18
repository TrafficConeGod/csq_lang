#pragma once
#include <stdio.h>

template<typename T>
struct const_array {
    const size_t size;
    T* const data;
};

template<typename T>
const_array<T> construct_const_array(const size_t size, T* const data) {
    return { .size = size, .data = data };
}