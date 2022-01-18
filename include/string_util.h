#pragma once
#include <stddef.h>
#include <string.h>
#include "const_array.h"
#include "dynamic_array.h"

using string = const_array<const char>;
using mutable_string = const_array<char>;
using dynamic_string = dynamic_array<char>;

inline string construct_string(const char* str) {
    return { .size = strlen(str), .data = str };
}
void print_string(string str);

void remove_parent_dirs(dynamic_string* path);
void strip_file_extension(dynamic_string* path);