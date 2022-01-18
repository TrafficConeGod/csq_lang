#pragma once
#include "file_util.h"

/**
 * @brief Compiles a source file into an object file.
 */
void compile_to_object_file(const size_t code_size, const char* code, file* out);