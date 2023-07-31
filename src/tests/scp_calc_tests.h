#ifndef SCP_CALC_TESTS_H
#define SCP_CALC_TESTS_H

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../scp_credit.h"
#include "../scp_smartcalc.h"

// #define MAX_EXP_LEN 255
#define SCP_EPS 1e-07
#define SCP_TWO_DECIMALS 1e-02
#define PRE_TEST_HEADER "\033[33m**"
#define POST_TEST_HEADER "**\033[0m"

Suite *scp_incorrect_exp_tests(void);
Suite *scp_correct_exp_tests(void);
Suite *scp_credit_tests(void);

#endif  // SCP_CALC_TESTS_H
