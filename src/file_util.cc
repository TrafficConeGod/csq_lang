#include "file_util.h"
#include "string_util.h"
#include <sys/stat.h>
#include <unistd.h>

bool file_exists(string path) {
    char path_cstr[path.size + 1] = {0};
    memcpy(path_cstr, path.data, path.size);
    return access(path_cstr, F_OK) != -1;
}

size_t get_size_of_file(string path) {
    char path_cstr[path.size + 1] = {0};
    memcpy(path_cstr, path.data, path.size);
    struct stat st;
    stat(path_cstr, &st);
    return st.st_size + 1;
}

file* custom_fopen(string path, string mode) {
    char path_cstr[path.size + 1] = {0};
    memcpy(path_cstr, path.data, path.size);
    char mode_cstr[mode.size + 1] = {0};
    memcpy(mode_cstr, mode.data, mode.size);
    return fopen(path_cstr, mode_cstr);
}