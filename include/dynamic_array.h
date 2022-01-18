#pragma once
#include <stddef.h>
#include "const_array.h"

/**
 * @brief An array with a dynamic size and a dynamic pointer to data
 */
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