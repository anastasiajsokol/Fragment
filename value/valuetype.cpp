#include "valuetype.h"

std::string to_string(ValueType type) {
    const char* names[] = {
        "numeric",
        "string",
        "boolean",
        "function"
    };

    return names[(int)type];
}