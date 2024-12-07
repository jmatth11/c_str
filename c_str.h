#ifndef CUSTOM_C_STR
#define CUSTOM_C_STR

typedef enum c_str_error {
    C_STR_NO_ERROR,
    C_STR_MALLOC_ERROR,
    C_STR_OUT_OF_BOUNDS
} c_str_error;

struct internal_c_str;

typedef struct c_str {
    internal_c_str _internal;
    c_str_error (*append)(struct c_str*, const char *, size_t);
    int (*length)(const struct c_str*);
    c_str_error (*get_str)(const struct c_str*, char **);
    c_str_error (*get_str)(const struct c_str*, const char **);
    c_str_error (*set)(struct c_str*, const char *, size_t);
    c_str_error (*at)(struct c_str*, size_t, char*);
} c_str;

c_str_error new_c_str(struct c_str*, size_t);

#endif
