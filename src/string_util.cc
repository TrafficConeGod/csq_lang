#include "string_util.h"
#include "at.h"
#include <stdio.h>

void print_string(string str) {
    for (size_t i = 0; i < str.size; i++) {
        putchar(str.data[i]);
    }
}

void remove_parent_dirs(dynamic_string* out, string path) {
    bool has_slash = false;
    size_t slash_index;
    for (size_t i = 0; i < path.size; i++) {
        size_t back_index = (path.size - 1) - i;
        if (at(path.size, path.data, back_index) == '/') {
            if (is_in_bounds(path.size, back_index + 1)) {
                has_slash = true;
                slash_index = back_index + 1;
            }
            break;
        }
    }
    if (has_slash) {
        out->size = path.size - slash_index;
        for (size_t i = slash_index; i < path.size; i++) {
            at(out->size, out->data, i - slash_index) = path.data[i];
        }
    } else {
        out->size = path.size;
        copy_array_range(path, out, out->size);
    }
}

void strip_file_extension(dynamic_string* path) {
    for (size_t i = 0; i < path->size; i++) {
        size_t back_index = (path->size - 1) - i;
        if (at(path->size, path->data, back_index) == '.') {
            path->size -= (path->size - back_index);
            return;
        }
    }
}