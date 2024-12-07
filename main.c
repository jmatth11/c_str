#include "c_str.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define TEST_STR "test string\0"
#define TEST_STR_LEN 12

static char* test_str() {
  char* tmp = malloc(sizeof(char) * TEST_STR_LEN);
  strcpy(tmp, TEST_STR);
  return tmp;
}

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

int main(int argc, char *argv[]) {

  test_new_c_str_normal();
  test_new_c_str_less_than_zero();
  test_new_c_str_greater_than_one();

  test_new_c_str_with_string_normal();

  return 0;
}
