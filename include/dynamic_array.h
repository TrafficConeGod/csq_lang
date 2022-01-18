#pragma once
#include <stddef.h>
#include "const_array.h"

template<typename T>
struct dynamic_array {
    size_t size;
    T* data;

    inline explicit operator const_array<T>() const {
        return *(const_array<T>*)this;
    }

    inline explicit operator const_array<const T>() const {
        return *(const_array<const T>*)this;
    }
};