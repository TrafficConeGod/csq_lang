#include "lex.h"
#include "heap.h"
#include "at.h"

#define CASE_WHITESPACE \
case 0xD: \
case ' ': \
case '\n': \
case '\t' \

#define CASE_SYMBOL \
case ';': \
case '(': \
case ')': \
case '{': \
case '}': \
case '[': \
case ']': \
case '<': \
case '>': \
case '.': \
case ',': \
case '~': \
case '=': \
case '+': \
case '-': \
case '*': \
case '/': \
case '%': \
case '&': \
case '|': \
case '!': \
case '^' \

#define CHAR_STRING_CASE_IMPL \
case '\'': { \
    tokenize(&tokens, &built_literal); \
    lex_mode = CHAR; \
} break; \
case '\"': { \
    tokenize(&tokens, &built_literal); \
    lex_mode = STRING; \
} break; \

token_type get_token_type(dynamic_string* literal) {
    // switch (literal->size) {
    //     case 1: {

    //     } break;
    // }
    return token_type::INVALID;
}

void tokenize(dynamic_array<token>* tokens, dynamic_string* literal) {
    if (literal->size > 0) {
        push_to_heap_array(tokens, { .type = get_token_type(literal), .literal = *literal });
        disown_heap_array(literal);
    }
}

dynamic_array<token> lex_source(string source) {
    auto built_literal = create_heap_array<char>();
    auto tokens = create_heap_array<token>();

    enum {
        WORD,
        SYMBOL,
        CHAR,
        STRING,
        COMMENT
    } lex_mode = WORD;

    bool escaped = false;

    for (size_t i = 0; i < source.size; ++i) {
        char ch = source.data[i];

        switch (lex_mode) {
            case WORD: {
                switch (ch) {
                    CASE_WHITESPACE: tokenize(&tokens, &built_literal); break;
                    CASE_SYMBOL: {
                        tokenize(&tokens, &built_literal);
                        push_to_heap_array(&built_literal, ch);
                        lex_mode = SYMBOL;
                    } break;
                    CHAR_STRING_CASE_IMPL;
                    default: push_to_heap_array(&built_literal, ch);
                }
            } break;
            case SYMBOL: {
                switch (ch) {
                    CASE_WHITESPACE: {
                        tokenize(&tokens, &built_literal);
                        lex_mode = WORD;
                    } break;
                    CASE_SYMBOL: {
                        tokenize(&tokens, &built_literal);
                        push_to_heap_array(&built_literal, ch);
                    } break;
                    CHAR_STRING_CASE_IMPL;
                    default: {
                        tokenize(&tokens, &built_literal);
                        push_to_heap_array(&built_literal, ch);
                        lex_mode = WORD;
                    } break;
                }
            } break;
            case CHAR:
            case STRING: {
                if (escaped) {
                    switch (ch) {
                        case 'r': push_to_heap_array(&built_literal, '\r'); break;
                        case 'n': push_to_heap_array(&built_literal, '\n'); break;
                        case 't': push_to_heap_array(&built_literal, '\t'); break;
                        case '\'': push_to_heap_array(&built_literal, '\''); break;
                        case '\"': push_to_heap_array(&built_literal, '\"'); break;
                        default: break;
                    }
                    tokenize(&tokens, &built_literal);
                    escaped = false;
                } else {
                    switch (ch) {
                        case '\\': escaped = true; break;
                        case '\'': {
                            if (lex_mode == CHAR) {
                                tokenize(&tokens, &built_literal);
                                lex_mode = WORD;
                            }
                        } break;
                        case '\"': {
                            if (lex_mode == STRING) {
                                tokenize(&tokens, &built_literal);
                                lex_mode = WORD;
                            }
                        } break;
                        default: push_to_heap_array(&built_literal, ch); break;
                    }
                }
            } break;
            default: break;
        }
    }

    destroy_heap_array(&built_literal);
    return tokens;
}