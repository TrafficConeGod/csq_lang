#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "at.h"
#include "string_util.h"
#include "file_util.h"
#include "backend/compiler.h"

void catch_array_index_out_of_bounds_exception(size_t size, size_t index) {
    printf("Array index out of bounds: %zu >= %zu\n", index, size);
    exit(EXIT_FAILURE);
}

int custom_main(const size_t args_count, const size_t* arg_sizes, char** args) {
    // Create object files for each input file.
    for (size_t i = 1; i < args_count; ++i) {
        size_t name_size = arg_sizes[i] + 2;
        char name[name_size];

        get_filename(&name_size, name);
        strip_file_extension(&name_size, args[i]);

        name_size += 2;
        name[name_size - 2] = '.';
        name[name_size - 1] = 'o';
        
        auto file = custom_fopen({ .size = name_size, .data = name }, construct_string("w"));

        compile_to_object_file(arg_sizes[i], args[i], file);
        fclose(file);
    }
    return 0;
}

int main(int arg_count, char** args) {
    size_t arg_sizes[arg_count];
    for (size_t i = 0; i < (size_t)arg_count; ++i) {
        arg_sizes[i] = strlen(args[i]);
    }
    return custom_main(arg_count, (const size_t*)arg_sizes, args);
}