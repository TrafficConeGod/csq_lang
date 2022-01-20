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
    COMMA_SY,
    OPEN_BRACKET_SY,
    CLOSE_BRACKET_SY,
    OPEN_ANGLE_SY,
    CLOSE_ANGLE_SY,
    TILDE_SY,

    // Math symbols

    EQUALS_SY,
    PLUS_SY,
    MINUS_SY,
    STAR_SY,
    SLASH_SY,
    AND_SY,
    OR_SY,
    NOT_SY,
    XOR_SY,
    
    // Logic symbols

    NOT_EQUALS_SY,
    GREATER_THAN_SY,
    LESS_THAN_SY,
    GREATER_THAN_EQUALS_SY,
    LESS_THAN_EQUALS_SY,

    // Identifiers
    VAR_ID,
    TYPE_ID,

    // Literals
    INT_LIT,
    FLOAT_LIT,
    CHAR_LIT,
    STRING_LIT,
    BOOL_LIT,

    // Keywords
    IF_KW,
    ELSE_KW,
    WHILE_KW,
    FOR_KW,
    USING_KW,
    IMPORT_KW,
    AUTO_KW
};

struct token {
    token_type type;
    dynamic_string literal;
};