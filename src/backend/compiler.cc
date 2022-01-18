#include "backend/compiler.h"

void compile_to_object_file(string code, file* out) {
    fwrite(code.data, 1, code.size, out);
}