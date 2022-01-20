#pragma once
#include "file_util.h"
#include "string_util.h"

/**
 * @brief Compiles a source file into an object file.
 */
void make_object_file(string source, string object_path);