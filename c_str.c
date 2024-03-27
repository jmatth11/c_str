#include "c_str.h"
#include <string.h>

#ifndef C_STR_ARRAY_INC_CONSTANT
#define C_STR_ARRAY_INC_CONSTANT 1.2
#endif

struct internal_c_str {
    char* data;
    size_t len;
    size_t cap;
};

c_str_error append(struct c_str* data, const char* str, size_t len) {
    size_t d_len = data->_internal->len;
    size_t new_len = d_len + len;
    if (new_len > data->_internal->cap) {
        size_t new_cap = ((double)data->_internal->cap * C_STR_ARRAY_INC_CONSTANT);
        data->_internal->data = realloc(
                data->_internal->data, sizeof(char) * new_cap);
        data->_internal->cap = new_cap;
        if (data->_internal->data == NULL) {
            return C_STR_MALLOC_ERROR;
        }
    }
    strncpy(&data->_internal->data[d_len - 1], str, len);
    data->_internal->data[new_len] = '\0';
    return C_STR_NO_ERROR;
}

int length(const struct c_str* data) {
    // subtract null-byte
    return data->_internal->len - 1;
}

c_str_error get_str(const struct c_str* data, char** out) {
    *out = data->_internal->data;
    return C_STR_NO_ERROR;
}

c_str_error get_const_str(const struct c_str* data, const char ** out) {
    *out = data->_internal->data;
    return C_STR_NO_ERROR;
}

c_str_error set(struct c_str* data, const char *str, size_t len) {
    // TODO set the string and account for resizing if needed.
    return C_STR_NO_ERROR;
}

c_str_error at(const struct c_str* data, size_t idx, char* out) {
    const int len = data->_internal->len;
    if (idx > len || idx < 0) {
        return C_STR_OUT_OF_BOUNDS;
    }
    *out = data->_internal->data[idx];
    return C_STR_NO_ERROR;
}

c_str_error new_c_str(struct c_str* data, size_t cap) {
    if (cap < 0) {
        cap = 0;
    }
    // add for null-terminator
    ++cap;
    char *tmp = (char*)malloc(sizeof(char)*cap);
    if (tmp == NULL) {
        return C_STR_MALLOC_ERROR;
    }
    tmp[0] = '\0';
    data->_internal = (struct internal_c_str*)malloc(sizeof(struct internal_c_str));
    if (data->_internal == NULL) {
        return C_STR_MALLOC_ERROR;
    }
    data->_internal->data = tmp;
    data->_internal->len = 1;
    data->_internal->cap = cap;
    return C_STR_NO_ERROR;
}

c_str_error new_c_str_with_string(struct c_str* data, const char* str, size_t len) {
    size_t cap = ((double)len * C_STR_ARRAY_INC_CONSTANT);
    c_str_error err = new_c_str(data, cap);
    if (err!=C_STR_NO_ERROR) {
        return err;
    }
    data->set(data, str, len);
    return C_STR_NO_ERROR;
}

void free_c_str(struct c_str* data) {
    free(data->_internal->data);
    free(data->_internal);
    data->_internal = NULL;
}

