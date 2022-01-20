#pragma once
#include "string_util.h"
#include "token.h"

/**
 * @brief Lexes a source into tokens.
 * @return dynamic_array<token> A heap array of the tokens
 */
dynamic_array<token> lex_source(string source);