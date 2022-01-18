#include "file_util.h"
#include "string_util.h"

file* custom_fopen(string path, string mode) {
    size_t end_char = path.data[path.size];
    const_cast<char*>(path.data)[path.size] = '\0';
    file* file = fopen(path.data, mode.data);
    const_cast<char*>(path.data)[path.size] = end_char;
    return file;
}