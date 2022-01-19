#include "backend/compiler.h"
#include "at.h"
#include "file_util.h"
#include <stdlib.h>

void compile_to_object_file(string source, string object_path) {
    size_t command_size = object_path.size + 18;
    char command_data[command_size + 1];
    command_data[command_size] = '\0';
    
    {
        size_t i = 0;
        caught_at(command_size, command_data, i++) = 'g';
        caught_at(command_size, command_data, i++) = 'c';
        caught_at(command_size, command_data, i++) = 'c';
        caught_at(command_size, command_data, i++) = ' ';
        caught_at(command_size, command_data, i++) = '-';
        caught_at(command_size, command_data, i++) = 'x';
        caught_at(command_size, command_data, i++) = ' ';
        caught_at(command_size, command_data, i++) = 'c';
        caught_at(command_size, command_data, i++) = ' ';
        caught_at(command_size, command_data, i++) = '-';
        caught_at(command_size, command_data, i++) = 'c';
        caught_at(command_size, command_data, i++) = ' ';
        caught_at(command_size, command_data, i++) = '-';
        caught_at(command_size, command_data, i++) = 'o';
        caught_at(command_size, command_data, i++) = ' ';

        for (size_t j = 0; j < object_path.size; ++j) {
            caught_at(command_size, command_data, i++) = object_path.data[j];
        }

        caught_at(command_size, command_data, i++) = ' ';
        caught_at(command_size, command_data, i++) = '-';
    }

    auto file = popen(command_data, "w");
    fwrite(source.data, 1, source.size * sizeof(char), file);
    pclose(file);
}