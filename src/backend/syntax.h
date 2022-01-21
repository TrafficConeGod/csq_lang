#pragma once
#include "lex.h"
#include "const_array.h"
#include "dynamic_array.h"

enum class syntax_node_type {
    INVALID,

    // Statements

    // Inside function
    VAR_DECL_ST,
    IF_ST,
    ELSE_ST,
    WHILE_ST,
    FOR_ST,

    // Out of function
    MODULE_ST,
    USING_ST,
    IMPORT_ST,
    USING_IMPORT_ST,
    FUNCTION_DEF_ST,
    FUNCTION_IMPL_ST,

    // Expressions
    FUNCTION_CALL_EXP,

    // Identifiers
    TYPE_ID,
    VAR_ID
};

struct syntax_node {
    syntax_node_type type;

    dynamic_array<syntax_node> children;
};

/**
 * @brief Generates a syntax tree from a token array
 */
void create_syntax_tree(const_array<token> tokens);