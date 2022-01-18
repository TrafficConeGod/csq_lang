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
        string source_file_path = { .size = arg_sizes[i], .data = args[i] };

        if (!file_exists(source_file_path)) {
            printf("File not found: ");
            print_string(source_file_path);
            printf("\n");
            continue;
        }

        auto source_size = get_size_of_file(source_file_path);
        char source_data[source_size + 1];

        auto source_file = custom_fopen(source_file_path, construct_string("rb"));
        fread(source_data, 1, source_size, source_file);
        fclose(source_file);

        char name_data[arg_sizes[i] + 2] = {0};
        memcpy(name_data, args[i], arg_sizes[i]);
        dynamic_string name = { .size = arg_sizes[i] + 2, .data = name_data };
    
        remove_parent_dirs(&name, source_file_path);
        strip_file_extension(&name);

        name.size += 2;
        name.data[name.size - 2] = '.';
        name.data[name.size - 1] = 'o';

        auto object_file = custom_fopen((string)name, construct_string("wb"));

        compile_to_object_file({ .size = source_size, .data = source_data }, object_file);
        fclose(object_file);
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