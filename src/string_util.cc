#include "string_util.h"
#include <stdio.h>

void print_string(string str) {
    for (size_t i = 0; i < str.size; i++) {
        putchar(str.data[i]);
    }
}

void remove_parent_dirs(dynamic_string* path) {
    size_t slash_index = path->size;
    for (size_t i = path->size - 1; i > 0; i--) {
        if (path->data[i] == '/') {
            slash_index = i;
            break;
        }
    }
    path->data = path->data + (sizeof(char) * slash_index);
    path->size = path->size - slash_index;
}