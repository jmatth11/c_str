#include "c_str.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define TEST_STR "test string\0"

/**
 * function to generate test string.
 */
static char* test_str() {
  size_t len = strlen(TEST_STR);
  char* tmp = malloc(sizeof(char) * len);
  strncpy(tmp, TEST_STR, len);
  return tmp;
}

/**
 * Testing creating a c_str normally.
 */
static void test_new_c_str_normal() {
  c_str value;
  char* result;
  c_str_error err = new_c_str(&value, 0);
  assert(err == C_STR_NO_ERROR);
  assert(value.length(&value) == 0);
  value.get_str(&value, &result);
  assert(strcmp(result, "\0") == 0);
  free_c_str(&value);
}
/**
 * Testing creating a c_str with less than zero value.
 */
static void test_new_c_str_less_than_zero() {
  c_str value;
  char* result;
  c_str_error err = new_c_str(&value, -1);
  assert(err == C_STR_NO_ERROR);
  assert(value.length(&value) == 0);
  value.get_str(&value, &result);
  assert(strcmp(result, "\0") == 0);
  free_c_str(&value);
}
/**
 * Testing creating a c_str with greater than one value.
 */
static void test_new_c_str_greater_than_one() {
  c_str value;
  char* result;
  c_str_error err = new_c_str(&value, 10);
  assert(err == C_STR_NO_ERROR);
  assert(value.length(&value) == 0);
  value.get_str(&value, &result);
  assert(strcmp(result, "\0") == 0);
  free_c_str(&value);
}

/**
 * Testing creating a c_str with a given string.
 */
static void test_new_c_str_with_string_normal() {
  c_str value;
  char* test = test_str();
  size_t test_len = strlen(test);
  c_str_error err = new_c_str_with_string(&value, test, test_len);
  assert(err == C_STR_NO_ERROR);
  assert(value.length(&value) == test_len);
  char* result;
  value.get_str(&value, &result);
  assert(strcmp(test, result) == 0);
  free(test);
  free_c_str(&value);
}

/**
 * Testing creating a c_str with a given string and less than or equal to zero.
 */
static void test_new_c_str_with_string_less_than_or_equal_to_zero() {
  c_str value;
  char* test = test_str();
  size_t test_len = 0;
  c_str_error err = new_c_str_with_string(&value, test, test_len);
  assert(err == C_STR_NO_ERROR);
  assert(value.length(&value) == 1);
  char* result;
  value.get_str(&value, &result);
  assert(strcmp("t", result) == 0);
  free(test);
  free_c_str(&value);
}

/**
 * Testing freeing c_str.
 */
static void test_free_c_str() {
  c_str value;
  c_str_error err = new_c_str(&value, 1);
  assert(err == C_STR_NO_ERROR);
  free_c_str(&value);
  assert(value._internal == NULL);
}

/**
 * Testing pointer functions:
 * - append
 * - length
 * - get_str
 */
static void test_append_length_get_str() {
  c_str value;
  char* test = test_str();
  char* test_append = " append";
  size_t test_len = strlen(test);
  size_t test_append_len = strlen(test_append);
  c_str_error err = new_c_str_with_string(&value, test, test_len);
  assert(err == C_STR_NO_ERROR);
  // testing append
  err = value.append(&value, test_append, test_append_len);
  assert(err == C_STR_NO_ERROR);
  size_t expected_len = test_len + test_append_len;
  char* expected = malloc(sizeof(char)*expected_len);
  sprintf(expected, "%s%s", test, test_append);
  // testing length
  size_t value_len = value.length(&value);
  assert(value_len == expected_len);
  // testing get_str
  char* result;
  err = value.get_str(&value, &result);
  assert(err == C_STR_NO_ERROR);
  assert(strcmp(expected, result) == 0);
  free(test);
  free_c_str(&value);
}

/**
 * Testing pointer functions:
 * - get_const_str
 */
static void test_get_const_str() {
  c_str value;
  char* test = "test";
  size_t test_len = 4;
  c_str_error err = new_c_str_with_string(&value, test, test_len);
  assert(err == C_STR_NO_ERROR);
  const char* result;
  err = value.get_const_str(&value, &result);
  assert(err == C_STR_NO_ERROR);
  assert(strcmp(test, result) == 0);
  free_c_str(&value);
}

/**
 * Testing pointer functions:
 * - set
 * - at
 */
static void test_set_at() {
  c_str value;
  char* test = "test";
  size_t test_len = 4;
  c_str_error err = new_c_str(&value, test_len);
  assert(err == C_STR_NO_ERROR);
  // tesing set
  err = value.set(&value, test, test_len);
  assert(err == C_STR_NO_ERROR);
  char* result;
  err = value.get_str(&value, &result);
  assert(err == C_STR_NO_ERROR);
  assert(strcmp(test, result) == 0);
  // testing at
  char result_char;
  err = value.at(&value, 1, &result_char);
  assert(err == C_STR_NO_ERROR);
  assert('e' == result_char);
  free_c_str(&value);
}

int main(int argc, char *argv[]) {

  test_new_c_str_normal();
  test_new_c_str_less_than_zero();
  test_new_c_str_greater_than_one();

  test_new_c_str_with_string_normal();
  test_new_c_str_with_string_less_than_or_equal_to_zero();

  test_free_c_str();

  test_append_length_get_str();

  test_get_const_str();

  test_set_at();

  return 0;
}
