#pragma once
#include <stdio.h>
#include "string_util.h"

using file = FILE;

bool file_exists(string path);
size_t get_size_of_file(string path);
file* custom_fopen(string path, string mode);