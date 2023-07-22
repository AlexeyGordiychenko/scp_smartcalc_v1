#ifndef S21_CALC_TESTS_H
#define S21_CALC_TESTS_H

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_smartcalc.h"

// #define MAX_EXP_LEN 255
#define S21_EPS 1e-07
#define PRE_TEST_HEADER "\033[33m**"
#define POST_TEST_HEADER "**\033[0m"

Suite *s21_incorrect_exp_tests(void);
Suite *s21_correct_exp_tests(void);

#endif  // S21_CALC_TESTS_H
