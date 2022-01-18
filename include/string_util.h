#pragma once
#include <stddef.h>
#include <string.h>
#include "const_array.h"
#include "dynamic_array.h"

/**
 * @brief String with constant size and data
 */
using string = const_array<const char>;
/**
 * @brief String with constant size and mutable data
 */
using mutable_string = const_array<char>;
/**
 * @brief String with dynamic size and data
 */
using dynamic_string = dynamic_array<char>;

/**
 * @brief Constructs a string from a string literal
 */
inline string construct_string(const char* str) {
    return { .size = strlen(str), .data = str };
}

/**
 * @brief Prints a string
 */
void print_string(string str);

/**
 * @brief Removes parent directories from a path
 * 
 * @param out The out param
 */
void remove_parent_dirs(dynamic_string* out, string path);

/**
 * @brief Strips file extension from a path
 */
void strip_file_extension(dynamic_string* path);