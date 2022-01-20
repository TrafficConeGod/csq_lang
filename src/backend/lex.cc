#include "lex.h"
#include "heap.h"
#include "at.h"

#define CASE_WHITESPACE \
case 0xD: \
case ' ': \
case '\n': \
case '\t' \

#define CASE_SYMBOL \
case '=': \
case '(': \
case ')': \
case '<': \
case '>': \
case '+': \
case '-': \
case '*': \
case '/': \
case '^': \
case '&': \
case ',' \

#define CASE_DOUBLE_SYMBOL \
case '=' \

#define CASE_SINGLE_SYMBOL \
case '(': \
case ')': \
case '<': \
case '>': \
case '+': \
case '-': \
case '*': \
case '/': \
case '^': \
case '&': \
case ',' \

void add_char_to_literal(dynamic_string* literal, char ch) {
    push_to_heap_array(literal, ch);
}

void tokenize(token_type token_type, dynamic_array<token>* tokens, dynamic_string* literal) {
    if (literal->size > 0) {
        push_to_heap_array(tokens, { .type = token_type, .literal = *literal });
        disown_heap_array(literal);
    }
}

dynamic_array<token> lex_source(string source) {
    auto built_literal = create_heap_array<char>();
    auto tokens = create_heap_array<token>();

    enum {
        WORD,
        SYMBOL
    } lex_mode = WORD;

    for (size_t i = 0; i < source.size; ++i) {
        char ch = source.data[i];

        // switch (lex_mode) {
        //     case WORD: {
                
        //     } break;
        //     case SYMBOL: {

        //     } break;
        // }
        if (ch == ' ') {
            tokenize(token_type::TYPE_ID, &tokens, &built_literal);
        } else {
            add_char_to_literal(&built_literal, ch);
        }
    }

    destroy_heap_array(&built_literal);
    return tokens;
}