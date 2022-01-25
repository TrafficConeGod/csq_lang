#include "lex.h"
#include "heap.h"
#include "at.h"
#include <ctype.h>

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

#define CHAR_STRING_CASE_IMPL(get_token_type) \
case '\'': { \
    tokenize(&tokens, get_token_type((string)built_literal), &built_literal); \
    lex_mode = CHAR; \
} break; \
case '\"': { \
    tokenize(&tokens, get_token_type((string)built_literal), &built_literal); \
    lex_mode = STRING; \
} break; \

#define COMMENT_IMPL(get_token_type) \
if (ch == '/' && is_in_bounds(source.size, i + 1) && (source.data[i + 1] == '/' || source.data[i + 1] == '*')) { \
    tokenize(&tokens, get_token_type((string)built_literal), &built_literal); \
    lex_mode = source.data[i + 1] == '/' ? COMMENT : MULTILINE_COMMENT; \
    break; \
} \

auto true_lit = construct_string("true");
auto false_lit = construct_string("false");
auto auto_kw = construct_string("auto");
auto if_kw = construct_string("if");
auto else_kw = construct_string("else");
auto while_kw = construct_string("while");
auto for_kw = construct_string("for");
auto return_kw = construct_string("return");
auto module_kw = construct_string("module");
auto using_kw = construct_string("using");
auto import_kw = construct_string("import");

token_type get_word_token_type(string literal) {
    switch (literal.size) {
        case 2: {
            if (compare_string(literal, if_kw)) { return token_type::IF_KW; }
        } break;
        case 3: {
            if (compare_string(literal, for_kw)) { return token_type::FOR_KW; }
        } break;
        case 4: {
            if (compare_string(literal, true_lit)) { return token_type::BOOL_LIT; }
            else if (compare_string(literal, auto_kw)) { return token_type::AUTO_KW; }
            else if (compare_string(literal, else_kw)) { return token_type::ELSE_KW; }
        } break;
        case 5: {
            if (compare_string(literal, false_lit)) { return token_type::BOOL_LIT; }
            if (compare_string(literal, while_kw)) { return token_type::WHILE_KW; }
            if (compare_string(literal, using_kw)) { return token_type::USING_KW; }
        } break;
        case 6: {
            if (compare_string(literal, return_kw)) { return token_type::RETURN_KW; }
            if (compare_string(literal, module_kw)) { return token_type::MODULE_KW; }
            if (compare_string(literal, import_kw)) { return token_type::IMPORT_KW; }
        } break;
        default: break;
    }
    for (size_t i = 0; i < literal.size; ++i) {
        if (isdigit(literal.data[i])) {
            return token_type::NUMBER_LIT;
        }
    }
    return token_type::ID;
}

token_type get_symbol_token_type(string literal) {
    if (literal.size == 1) {
        switch (literal.data[0]) {
            case ';': return token_type::SEMICOLON_SY;
            case '(': return token_type::OPEN_PAREN_SY;
            case ')': return token_type::CLOSE_PAREN_SY;
            case '{': return token_type::OPEN_BRACE_SY;
            case '}': return token_type::CLOSE_BRACE_SY;
            case '[': return token_type::OPEN_BRACKET_SY;
            case ']': return token_type::CLOSE_BRACKET_SY;
            case '<': return token_type::OPEN_ANGLE_SY;
            case '>': return token_type::CLOSE_ANGLE_SY;
            case '.': return token_type::DOT_SY;
            case ',': return token_type::COMMA_SY;
            case '~': return token_type::TILDE_SY;
            case '=': return token_type::EQUAL_SY;
            case '+': return token_type::PLUS_SY;
            case '-': return token_type::MINUS_SY;
            case '*': return token_type::STAR_SY;
            case '/': return token_type::SLASH_SY;
            case '%': return token_type::PERCENT_SY;
            case '&': return token_type::AMPERSAND_SY;
            case '|': return token_type::PIPE_SY;
            case '!': return token_type::BANG_SY;
            case '^': return token_type::CARET_SY;
            default: return token_type::INVALID;
        }
    } else {
        return token_type::INVALID;
    }
}

void tokenize(dynamic_array<token>* tokens, token_type type, dynamic_string* literal) {
    if (literal->size > 0) {
        push_to_heap_array(tokens, { .type = type, .literal = *literal });
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
        COMMENT,
        MULTILINE_COMMENT
    } lex_mode = WORD;

    bool escaped = false;

    for (size_t i = 0; i < source.size; ++i) {
        char ch = source.data[i];

        switch (lex_mode) {
            case WORD: {
                COMMENT_IMPL(get_word_token_type)
                switch (ch) {
                    CASE_WHITESPACE: tokenize(&tokens, get_word_token_type((string)built_literal), &built_literal); break;
                    CASE_SYMBOL: {
                        tokenize(&tokens, get_word_token_type((string)built_literal), &built_literal);
                        push_to_heap_array(&built_literal, ch);
                        lex_mode = SYMBOL;
                    } break;
                    CHAR_STRING_CASE_IMPL(get_word_token_type);
                    default: push_to_heap_array(&built_literal, ch);
                }
            } break;
            case SYMBOL: {
                COMMENT_IMPL(get_word_token_type)
                switch (ch) {
                    CASE_WHITESPACE: {
                        tokenize(&tokens, get_symbol_token_type((string)built_literal), &built_literal);
                        lex_mode = WORD;
                    } break;
                    CASE_SYMBOL: {
                        tokenize(&tokens, get_symbol_token_type((string)built_literal), &built_literal);
                        push_to_heap_array(&built_literal, ch);
                    } break;
                    CHAR_STRING_CASE_IMPL(get_symbol_token_type);
                    default: {
                        tokenize(&tokens, get_symbol_token_type((string)built_literal), &built_literal);
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
                    escaped = false;
                } else {
                    switch (ch) {
                        case '\\': escaped = true; break;
                        case '\'': {
                            if (lex_mode == CHAR) {
                                tokenize(&tokens, token_type::CHAR_LIT, &built_literal);
                                lex_mode = WORD;
                            }
                        } break;
                        case '\"': {
                            if (lex_mode == STRING) {
                                tokenize(&tokens, token_type::STRING_LIT, &built_literal);
                                lex_mode = WORD;
                            }
                        } break;
                        default: push_to_heap_array(&built_literal, ch); break;
                    }
                }
            } break;
            case COMMENT: {
                if (ch == '\n') { lex_mode = WORD; }
            } break;
            case MULTILINE_COMMENT: {
                if (ch == '*' && is_in_bounds(source.size, i + 1) && source.data[i + 1] == '/') {
                    i++;
                    lex_mode = WORD;
                }
            } break;
            default: break;
        }
    }

    destroy_heap_array(&built_literal);
    return tokens;
}