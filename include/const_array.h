#pragma once
#include <stdio.h>

template<typename T>
struct const_array {
    const size_t size;
    T* const data;
};