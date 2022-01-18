#pragma once
#include <stddef.h>
#include <string.h>
#include "const_array.h"
#include "mutable_array.h"

using string = const_array<const char>;
using mutable_string = mutable_array<char>;

inline string construct_string(const char* str) {
    return { .size = strlen(str), .data = str };
}

void remove_parent_dirs(mutable_string* path);
void strip_file_extension(mutable_string* path);