#ifndef S21_CALC_TESTS_H
#define S21_CALC_TESTS_H

#include <check.h>

#include "../s21_smartcalc.h"
#include "../s21_utils.h"
#include "../s21_validation.h"

#define PRE_TEST_HEADER "\033[33m**"
#define POST_TEST_HEADER "**\033[0m"

Suite *s21_incorrect_exp_tests(void);

#endif  // S21_CALC_TESTS_H
