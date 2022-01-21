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

    EQUALS_SY,
    PLUS_SY,
    MINUS_SY,
    STAR_SY,
    SLASH_SY,
    PERCENT_SY,
    AND_SY,
    LINE_SY,
    EXCLAMATION_SY,
    CARROT_SY,
    
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
    MODULE_KW,
    USING_KW,
    IMPORT_KW,
    AUTO_KW
};

struct token {
    token_type type;
    dynamic_string literal;
};