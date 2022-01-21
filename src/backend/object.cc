#include "backend/object.h"
#include "at.h"
#include "file_util.h"
#include "heap.h"
#include "lex.h"

// #define WRITE_INTERMEDIATE_SOURCE_TO_STDOUT

void write_intermediate_source(string source, file* out) {
    auto tokens = lex_source(source);

    for (size_t i = 0; i < tokens.size; ++i) {
        print_string((string)tokens.data[i].literal);
        printf(" %d\n", tokens.data[i].type);
    }

    for (size_t i = 0; i < tokens.size; ++i) {
        destroy_heap_array(&tokens.data[i].literal);
    }
    destroy_heap_array(&tokens);
}

void make_object_file(string source, string object_path) {
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

    #ifdef WRITE_INTERMEDIATE_SOURCE_TO_STDOUT
        write_intermediate_source(source, stdout);
    #else
        auto file = popen(command_data, "w");
        write_intermediate_source(source, file);
        pclose(file);
    #endif

}