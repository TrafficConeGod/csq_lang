#pragma once
#include "string_util.h"

enum class token_type {
    INVALID,

    // Symbols

    // Structure symbols

    SEMICOLON_SY,
    OPEN_PAREN_SY,
    CLOSE_PAREN_SY,
    OPEN_BRACE_SY,
    CLOSE_BRACE_SY,
    OPEN_BRACKET_SY,
    CLOSE_BRACKET_SY,
    OPEN_ANGLE_SY,
    CLOSE_ANGLE_SY,
    DOT_SY,
    COMMA_SY,
    TILDE_SY,

    // Math symbols

    EQUAL_SY,
    PLUS_SY,
    MINUS_SY,
    STAR_SY,
    SLASH_SY,
    PERCENT_SY,
    AMPERSAND_SY,
    PIPE_SY,
    BANG_SY,
    CARET_SY,
    
    // Identifier
    ID,

    // Literals
    NUMBER_LIT,
    CHAR_LIT,
    STRING_LIT,
    BOOL_LIT,

    // Keywords
    AUTO_KW,
    IF_KW,
    ELSE_KW,
    WHILE_KW,
    FOR_KW,
    RETURN_KW,
    MODULE_KW,
    IMPORT_KW,
    INTO_KW,
    TYPE_KW,
    STRUCT_KW
};

struct token {
    token_type type;
    dynamic_string literal;
};

/**
 * @brief Lexes a source into tokens.
 * @return dynamic_array<token> A heap array of the tokens
 */
dynamic_array<token> lex_source(string source);