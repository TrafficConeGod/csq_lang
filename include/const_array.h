#pragma once
#include <stdio.h>

template<typename T>
struct const_array {
    const size_t size;
    T* const data;

    inline explicit operator const_array<const T>() const {
        return *(const_array<const T>*)this;
    }
};