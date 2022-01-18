#pragma once
#include <stdio.h>
#include "string_util.h"

using file = FILE;

/**
 * @brief Checks if a file exists
 */
bool file_exists(string path);

/**
 * @brief Get the size of a file
 */
size_t get_size_of_file(string path);

/**
 * @brief Open a file with string type
 */
file* custom_fopen(string path, string mode);