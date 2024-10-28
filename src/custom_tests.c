#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asserts.h"
// Necessary due to static functions in state.c
#include "state.c"

/* Look at asserts.c for some helpful assert functions */

int greater_than_forty_two(int x) { return x > 42; }

bool is_vowel(char c) {
  char *vowels = "aeiouAEIOU";
  for (int i = 0; i < strlen(vowels); i++) {
    if (c == vowels[i]) {
      return true;
    }
  }
  return false;
}

/*
  Example 1: Returns true if all test cases pass. False otherwise.
    The function greater_than_forty_two(int x) will return true if x > 42. False otherwise.
    Note: This test is NOT comprehensive
*/
bool test_greater_than_forty_two() {
  int testcase_1 = 42;
  bool output_1 = greater_than_forty_two(testcase_1);
  if (!assert_false("output_1", output_1)) {
    return false;
  }

  int testcase_2 = -42;
  bool output_2 = greater_than_forty_two(testcase_2);
  if (!assert_false("output_2", output_2)) {
    return false;
  }

  int testcase_3 = 4242;
  bool output_3 = greater_than_forty_two(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  return true;
}

/*
  Example 2: Returns true if all test cases pass. False otherwise.
    The function is_vowel(char c) will return true if c is a vowel (i.e. c is a,e,i,o,u)
    and returns false otherwise
    Note: This test is NOT comprehensive
*/
bool test_is_vowel() {
  char testcase_1 = 'a';
  bool output_1 = is_vowel(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'e';
  bool output_2 = is_vowel(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 'i';
  bool output_3 = is_vowel(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'o';
  bool output_4 = is_vowel(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'u';
  bool output_5 = is_vowel(testcase_5);
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  char testcase_6 = 'k';
  bool output_6 = is_vowel(testcase_6);
  if (!assert_false("output_6", output_6)) {
    return false;
  }

  return true;
}

/* Task 4.1 */

bool test_is_tail() {
    // 测试用例
    char testcase_1 = 's'; // 预期 true
    char testcase_2 = 'w'; // 预期 true
    char testcase_3 = 'a'; // 预期 true
    char testcase_4 = 'd'; // 预期 true
    char testcase_5 = 'x'; // 预期 false
    char testcase_6 = 'z'; // 预期 false
    char testcase_7 = '1'; // 预期 false
    char testcase_8 = ' '; // 预期 false

    // 测试用例 1
    if (!assert_true("testcase_1 should be true", is_tail(testcase_1))) {
        return false;
    }

    // 测试用例 2
    if (!assert_true("testcase_2 should be true", is_tail(testcase_2))) {
        return false;
    }

    // 测试用例 3
    if (!assert_true("testcase_3 should be true", is_tail(testcase_3))) {
        return false;
    }

    // 测试用例 4
    if (!assert_true("testcase_4 should be true", is_tail(testcase_4))) {
        return false;
    }

    // 测试用例 5
    if (!assert_false("testcase_5 should be false", is_tail(testcase_5))) {
        return false;
    }

    // 测试用例 6
    if (!assert_false("testcase_6 should be false", is_tail(testcase_6))) {
        return false;
    }

    // 测试用例 7
    if (!assert_false("testcase_7 should be false", is_tail(testcase_7))) {
        return false;
    }

    // 测试用例 8
    if (!assert_false("testcase_8 should be false", is_tail(testcase_8))) {
        return false;
    }

    return true;
}


/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
bool test_is_head() {
    // 测试用例
    char testcase_1 = 'W'; // 预期 true
    char testcase_2 = 'A'; // 预期 true
    char testcase_3 = 'S'; // 预期 true
    char testcase_4 = 'D'; // 预期 true
    char testcase_5 = 'x'; // 预期 true
    char testcase_6 = 'w'; // 预期 false
    char testcase_7 = 'a'; // 预期 false
    char testcase_8 = '1'; // 预期 false
    char testcase_9 = ' '; // 预期 false

    // 测试用例 1
    if (!assert_true("testcase_1 should be true", is_head(testcase_1))) {
        return false;
    }

    // 测试用例 2
    if (!assert_true("testcase_2 should be true", is_head(testcase_2))) {
        return false;
    }

    // 测试用例 3
    if (!assert_true("testcase_3 should be true", is_head(testcase_3))) {
        return false;
    }

    // 测试用例 4
    if (!assert_true("testcase_4 should be true", is_head(testcase_4))) {
        return false;
    }

    // 测试用例 5
    if (!assert_true("testcase_5 should be true", is_head(testcase_5))) {
        return false;
    }

    // 测试用例 6
    if (!assert_false("testcase_6 should be false", is_head(testcase_6))) {
        return false;
    }

    // 测试用例 7
    if (!assert_false("testcase_7 should be false", is_head(testcase_7))) {
        return false;
    }

    // 测试用例 8
    if (!assert_false("testcase_8 should be false", is_head(testcase_8))) {
        return false;
    }

    // 测试用例 9
    if (!assert_false("testcase_9 should be false", is_head(testcase_9))) {
        return false;
    }

    return true;
}


/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<v>WASDx"
*/
bool test_is_snake() {
    // 测试用例
    char testcase_1 = 'w'; // 预期 true
    char testcase_2 = 'a'; // 预期 true
    char testcase_3 = 's'; // 预期 true
    char testcase_4 = 'd'; // 预期 true
    char testcase_5 = '^'; // 预期 true
    char testcase_6 = '<'; // 预期 true
    char testcase_7 = 'v'; // 预期 true
    char testcase_8 = '>'; // 预期 true
    char testcase_9 = 'W'; // 预期 true
    char testcase_10 = 'A'; // 预期 true
    char testcase_11 = 'S'; // 预期 true
    char testcase_12 = 'D'; // 预期 true
    char testcase_13 = 'x'; // 预期 true
    char testcase_14 = 'z'; // 预期 false
    char testcase_15 = '1'; // 预期 false
    char testcase_16 = ' '; // 预期 false

    // 测试用例 1 到 13: 应该返回 true
    if (!assert_true("testcase_1 should be true", is_snake(testcase_1))) return false;
    if (!assert_true("testcase_2 should be true", is_snake(testcase_2))) return false;
    if (!assert_true("testcase_3 should be true", is_snake(testcase_3))) return false;
    if (!assert_true("testcase_4 should be true", is_snake(testcase_4))) return false;
    if (!assert_true("testcase_5 should be true", is_snake(testcase_5))) return false;
    if (!assert_true("testcase_6 should be true", is_snake(testcase_6))) return false;
    if (!assert_true("testcase_7 should be true", is_snake(testcase_7))) return false;
    if (!assert_true("testcase_8 should be true", is_snake(testcase_8))) return false;
    if (!assert_true("testcase_9 should be true", is_snake(testcase_9))) return false;
    if (!assert_true("testcase_10 should be true", is_snake(testcase_10))) return false;
    if (!assert_true("testcase_11 should be true", is_snake(testcase_11))) return false;
    if (!assert_true("testcase_12 should be true", is_snake(testcase_12))) return false;
    if (!assert_true("testcase_13 should be true", is_snake(testcase_13))) return false;

    // 测试用例 14 到 16: 应该返回 false
    if (!assert_false("testcase_14 should be false", is_snake(testcase_14))) return false;
    if (!assert_false("testcase_15 should be false", is_snake(testcase_15))) return false;
    if (!assert_false("testcase_16 should be false", is_snake(testcase_16))) return false;

    return true;
}


bool test_body_to_tail() {
 // 测试用例
  char testcase_1 = '^'; // 预期 'w'
  char testcase_2 = '<'; // 预期 'a'
  char testcase_3 = 'v'; // 预期 's'
  char testcase_4 = '>'; // 预期 'd'
  char testcase_5 = 'x'; // 不在字符集中，预期 '?'
  char testcase_6 = ' '; // 不在字符集中，预期 '?'

  // 执行测试用例并检查返回值
  if (body_to_tail(testcase_1) != 'w') {
      printf("testcase_1 failed: expected 'w', got '%c'\n", body_to_tail(testcase_1));
      return false;
  }

  if (body_to_tail(testcase_2) != 'a') {
      printf("testcase_2 failed: expected 'a', got '%c'\n", body_to_tail(testcase_2));
      return false;
  }

  if (body_to_tail(testcase_3) != 's') {
      printf("testcase_3 failed: expected 's', got '%c'\n", body_to_tail(testcase_3));
      return false;
  }

  if (body_to_tail(testcase_4) != 'd') {
      printf("testcase_4 failed: expected 'd', got '%c'\n", body_to_tail(testcase_4));
      return false;
  }

  if (body_to_tail(testcase_5) != '?') {
      printf("testcase_5 failed: expected '?', got '%c'\n", body_to_tail(testcase_5));
      return false;
  }

  if (body_to_tail(testcase_6) != '?') {
      printf("testcase_5 failed: expected '?', got '%c'\n", body_to_tail(testcase_6));
      return false;
  }

  return true;
}

bool test_head_to_body() {
// 测试用例
  char testcase_1 = 'W'; // 预期 '^'
  char testcase_2 = 'A'; // 预期 '<'
  char testcase_3 = 'S'; // 预期 'v'
  char testcase_4 = 'D'; // 预期 '>'
  char testcase_5 = 'x'; // 不在字符集中，预期 '?'
  char testcase_6 = ' '; // 不在字符集中，预期 '?'

  // 执行测试用例并检查返回值
  if (head_to_body(testcase_1) != '^') {
      printf("testcase_1 failed: expected '^', got '%c'\n", head_to_body(testcase_1));
      return false;
  }

  if (head_to_body(testcase_2) != '<') {
      printf("testcase_2 failed: expected '<', got '%c'\n", head_to_body(testcase_2));
      return false;
  }

  if (head_to_body(testcase_3) != 'v') {
      printf("testcase_3 failed: expected 'v', got '%c'\n", head_to_body(testcase_3));
      return false;
  }

  if (head_to_body(testcase_4) != '>') {
      printf("testcase_4 failed: expected '>', got '%c'\n", head_to_body(testcase_4));
      return false;
  }

  if (head_to_body(testcase_5) != '?') {
      printf("testcase_5 failed: expected '?', got '%c'\n", head_to_body(testcase_5));
      return false;
  }

  if (body_to_tail(testcase_6) != '?') {
      printf("testcase_5 failed: expected '?', got '%c'\n", head_to_body(testcase_6));
      return false;
  }
  return true;
}


bool test_get_next_row() {
    // 定义测试用例
    unsigned int cur_row = 5;

    // 测试 'v', 's', 'S' 的情况
    if (get_next_row(cur_row, 'v') != cur_row + 1) {
        printf("Testcase 'v' failed: expected %u, got %u\n", cur_row + 1, get_next_row(cur_row, 'v'));
        return false;
    }

    if (get_next_row(cur_row, 's') != cur_row + 1) {
        printf("Testcase 's' failed: expected %u, got %u\n", cur_row + 1, get_next_row(cur_row, 's'));
        return false;
    }

    if (get_next_row(cur_row, 'S') != cur_row + 1) {
        printf("Testcase 'S' failed: expected %u, got %u\n", cur_row + 1, get_next_row(cur_row, 'S'));
        return false;
    }

    // 测试 '^', 'w', 'W' 的情况
    if (get_next_row(cur_row, '^') != cur_row - 1) {
        printf("Testcase '^' failed: expected %u, got %u\n", cur_row - 1, get_next_row(cur_row, '^'));
        return false;
    }

    if (get_next_row(cur_row, 'w') != cur_row - 1) {
        printf("Testcase 'w' failed: expected %u, got %u\n", cur_row - 1, get_next_row(cur_row, 'w'));
        return false;
    }

    if (get_next_row(cur_row, 'W') != cur_row - 1) {
        printf("Testcase 'W' failed: expected %u, got %u\n", cur_row - 1, get_next_row(cur_row, 'W'));
        return false;
    }

    // 测试其他字符的情况（不应改变行号）
    if (get_next_row(cur_row, 'x') != cur_row) {
        printf("Testcase 'x' failed: expected %u, got %u\n", cur_row, get_next_row(cur_row, 'x'));
        return false;
    }

    if (get_next_row(cur_row, '1') != cur_row) {
        printf("Testcase '1' failed: expected %u, got %u\n", cur_row, get_next_row(cur_row, '1'));
        return false;
    }

    if (get_next_row(cur_row, ' ') != cur_row) {
        printf("Testcase ' ' failed: expected %u, got %u\n", cur_row, get_next_row(cur_row, ' '));
        return false;
    }

    return true;
}


bool test_get_next_col() {
    // 定义测试用例
    unsigned int cur_col = 5;

    // 测试 '>', 'd', 'D' 的情况
    if (get_next_col(cur_col, '>') != cur_col + 1) {
        printf("Testcase '>' failed: expected %u, got %u\n", cur_col + 1, get_next_col(cur_col, '>'));
        return false;
    }

    if (get_next_col(cur_col, 'd') != cur_col + 1) {
        printf("Testcase 'd' failed: expected %u, got %u\n", cur_col + 1, get_next_col(cur_col, 'd'));
        return false;
    }

    if (get_next_col(cur_col, 'D') != cur_col + 1) {
        printf("Testcase 'D' failed: expected %u, got %u\n", cur_col + 1, get_next_col(cur_col, 'D'));
        return false;
    }

    // 测试 '<', 'a', 'A' 的情况
    if (get_next_col(cur_col, '<') != cur_col - 1) {
        printf("Testcase '<' failed: expected %u, got %u\n", cur_col - 1, get_next_col(cur_col, '<'));
        return false;
    }

    if (get_next_col(cur_col, 'a') != cur_col - 1) {
        printf("Testcase 'a' failed: expected %u, got %u\n", cur_col - 1, get_next_col(cur_col, 'a'));
        return false;
    }

    if (get_next_col(cur_col, 'A') != cur_col - 1) {
        printf("Testcase 'A' failed: expected %u, got %u\n", cur_col - 1, get_next_col(cur_col, 'A'));
        return false;
    }

    // 测试其他字符的情况（不应改变列号）
    if (get_next_col(cur_col, 'x') != cur_col) {
        printf("Testcase 'x' failed: expected %u, got %u\n", cur_col, get_next_col(cur_col, 'x'));
        return false;
    }

    if (get_next_col(cur_col, '1') != cur_col) {
        printf("Testcase '1' failed: expected %u, got %u\n", cur_col, get_next_col(cur_col, '1'));
        return false;
    }

    if (get_next_col(cur_col, ' ') != cur_col) {
        printf("Testcase ' ' failed: expected %u, got %u\n", cur_col, get_next_col(cur_col, ' '));
        return false;
    }

    return true;
}


bool test_customs() {
  if (!test_greater_than_forty_two()) {
    printf("%s\n", "test_greater_than_forty_two failed.");
    return false;
  }
  if (!test_is_vowel()) {
    printf("%s\n", "test_is_vowel failed.");
    return false;
  }
  if (!test_is_tail()) {
    printf("%s\n", "test_is_tail failed");
    return false;
  }
  if (!test_is_head()) {
    printf("%s\n", "test_is_head failed");
    return false;
  }
  if (!test_is_snake()) {
    printf("%s\n", "test_is_snake failed");
    return false;
  }
  if (!test_body_to_tail()) {
    printf("%s\n", "test_body_to_tail failed");
    return false;
  }
  if (!test_head_to_body()) {
    printf("%s\n", "test_head_to_body failed");
    return false;
  }
  if (!test_get_next_row()) {
    printf("%s\n", "test_get_next_row failed");
    return false;
  }
  if (!test_get_next_col()) {
    printf("%s\n", "test_get_next_col failed");
    return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  init_colors();

  if (!test_and_print("custom", test_customs)) {
    return 0;
  }

  return 0;
}
