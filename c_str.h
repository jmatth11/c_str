#ifndef CUSTOM_C_STR
#define CUSTOM_C_STR

#include <stdlib.h>

/**
 * Enums for error c_str error codes.
 */
typedef enum c_str_error {
    /* success */
    C_STR_NO_ERROR,
    /* malloc error */
    C_STR_MALLOC_ERROR,
    /* out of bounds */
    C_STR_OUT_OF_BOUNDS
} c_str_error;

/**
 * Internal c_str structure.
 */
struct internal_c_str;

/**
 * Structure to handle dealing with strings in a more convenient way.
 */
typedef struct c_str {
    /* internal */
    struct internal_c_str *_internal;
    /**
     * Append the given string to this string.
     * @param[in] struct c_str* The c_str object.
     * @param[in] const char* The string to append.
     * @param[in] size_t The size of the string to copy.
     * @returns c_str_error.
     */
    c_str_error (*append)(struct c_str*, const char *, size_t);
    /**
     * Get the length of the string. (does not include null-terminator
     * @param[in] const struct c_str* The c_str structure.
     * @returns The length.
     */
    int (*length)(const struct c_str*);
    /**
     * Get the underlying string.
     * @param[in] const struct c_str* The c_str structure.
     * @param[out] char** The pointer to return out the string to.
     * @returns c_str_error.
     */
    c_str_error (*get_str)(const struct c_str*, char **);
    /**
     * Get the underlying string as a const char*.
     * @param[in] const struct c_str* The c_str structure.
     * @param[out] const char** The pointer to return out the string to.
     * @returns c_str_error.
     */
    c_str_error (*get_const_str)(const struct c_str*, const char **);
    /**
     * Set the underlying string with the given string.
     * @param[in] struct c_str* The c_str structure.
     * @param[in] const char* The string data.
     * @param[in] size_t The size of the given string.
     * @returns c_str_error.
     */
    c_str_error (*set)(struct c_str*, const char *, const size_t);
    /**
     * Get the character at the given index.
     * @param[in] struct c_str* The c_str structure.
     * @param[in] size_t The index value.
     * @param[out] char* The out param.
     * @returns c_str_error.
     */
    c_str_error (*at)(const struct c_str*, const size_t, char*);
} c_str;

/**
 * Initializes a new c_str structure with a certain size.
 * @param[in] struct c_str* The c_str structure to initialize.
 * @param[in] size_t The size to initialize to.
 * @returns c_str_error.
 */
c_str_error new_c_str(struct c_str*, size_t);

/**
 * Initializes a new c_str structure with a given string.
 * @param[in] struct c_str* The c_str structure to initialize.
 * @param[in] const char* The string to copy.
 * @param[in] size_t The size of the given string.
 * @returns c_str_error.
 */
c_str_error new_c_str_with_string(struct c_str*, const char*, size_t);

/**
 * Frees the internals of the c_str.
 * @param[in] struct c_str* The c_str to free.
 */
void free_c_str(struct c_str*);

#endif
