#include "c_str.h"

struct internal_c_str {
    char* data;
    size_t len;
    size_t cap;
};


c_str_error append(struct c_str* data, const char* str, size_t len) {
    // TODO append string and appropriately set null-terminator
    // adjust cap if needed
    return C_STR_NO_ERROR;
}

int length(const struct c_str* data) {
    // subtract null-byte
    return data->_internal.len - 1;
}

c_str_error get_const_str(const struct c_str* data, const char ** out) {
    *out = data->_internal.data;
    return C_STR_NO_ERROR;
}

c_str_error get_str(const struct c_str* data, char** out) {
    *out = data->_internal.data;
    return C_STR_NO_ERROR;
}

c_str_error set(struct c_str* data, const char *str, size_t len) {
    return C_STR_NO_ERROR;
}

c_str_error at(const struct c_str* data, size_t idx, char* out) {
    const int len = data->_internal.len;
    if (idx > len || idx < 0) {
        return C_STR_OUT_OF_BOUNDS;
    }
    *char = data->_internal.data[idx];
    return C_STR_NO_ERROR;
}

c_str_error new_c_str_error(struct c_str* data, size_t cap) {
    // TODO malloc internal data structure with cap
    return C_STR_NO_ERROR;
}

