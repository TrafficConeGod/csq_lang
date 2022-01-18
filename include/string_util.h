#pragma once
#include <stddef.h>
#include <string.h>
#include "const_array.h"

using string = const_array<const char>;

inline string construct_string(const char* str) {
    return construct_const_array(strlen(str), str);
}

void get_filename(size_t* const size, char* path);
void strip_file_extension(size_t* const size, char* path);