/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "scp_correct_exp_tests.tc" instead.
 */

#include "scp_calc_tests.h"
START_TEST(scp_correct_0) {
  struct token* rpn = scp_exp_to_rpn("2+2");
  double res = 0;
  double res_correct = 4;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_1) {
  struct token* rpn = scp_exp_to_rpn("3*5+15-4");
  double res = 0;
  double res_correct = 26;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_2) {
  struct token* rpn = scp_exp_to_rpn("4/2");
  double res = 0;
  double res_correct = 2.0;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_3) {
  struct token* rpn = scp_exp_to_rpn("10^2");
  double res = 0;
  double res_correct = 100;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_4) {
  struct token* rpn = scp_exp_to_rpn("(-1)");
  double res = 0;
  double res_correct = -1;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_5) {
  struct token* rpn = scp_exp_to_rpn("+3");
  double res = 0;
  double res_correct = 3;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_6) {
  struct token* rpn = scp_exp_to_rpn("-3");
  double res = 0;
  double res_correct = -3;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_7) {
  struct token* rpn = scp_exp_to_rpn("5mod2");
  double res = 0;
  double res_correct = 1;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_8) {
  struct token* rpn = scp_exp_to_rpn("cos(0.7853981633974483)");
  double res = 0;
  double res_correct = 0.7071067811865476;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_9) {
  struct token* rpn = scp_exp_to_rpn("sin(0.5235987755982988)");
  double res = 0;
  double res_correct = 0.49999999999999994;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_10) {
  struct token* rpn = scp_exp_to_rpn("tan(0.7853981633974483)");
  double res = 0;
  double res_correct = 0.9999999999999999;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_11) {
  struct token* rpn = scp_exp_to_rpn("acos(0.5)");
  double res = 0;
  double res_correct = 1.0471975511965979;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_12) {
  struct token* rpn = scp_exp_to_rpn("asin(0.5)");
  double res = 0;
  double res_correct = 0.5235987755982989;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_13) {
  struct token* rpn = scp_exp_to_rpn("atan(1)");
  double res = 0;
  double res_correct = 0.7853981633974483;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_14) {
  struct token* rpn = scp_exp_to_rpn("sqrt(16)");
  double res = 0;
  double res_correct = 4.0;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_15) {
  struct token* rpn = scp_exp_to_rpn("ln(2)");
  double res = 0;
  double res_correct = 0.6931471805599453;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_16) {
  struct token* rpn = scp_exp_to_rpn("log(10)");
  double res = 0;
  double res_correct = 1.0;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_17) {
  struct token* rpn = scp_exp_to_rpn("(2+3)*(5-2)");
  double res = 0;
  double res_correct = 15;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_18) {
  struct token* rpn = scp_exp_to_rpn("2*3^2");
  double res = 0;
  double res_correct = 18;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_19) {
  struct token* rpn = scp_exp_to_rpn("ln(2^5)");
  double res = 0;
  double res_correct = 3.4657359027997265;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_20) {
  struct token* rpn = scp_exp_to_rpn("2+2*3+(4/2)^2");
  double res = 0;
  double res_correct = 12.0;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_21) {
  struct token* rpn = scp_exp_to_rpn(
      "sin(0.5235987755982988)+cos(1.0471975511965979)-tan(0."
      "7853981633974483)");
  double res = 0;
  double res_correct = -1.1102230246251565e-16;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_22) {
  struct token* rpn = scp_exp_to_rpn("sqrt(16)+sqrt(9)*2");
  double res = 0;
  double res_correct = 10.0;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_23) {
  struct token* rpn = scp_exp_to_rpn("ln(2)+log(10)-log(2)");
  double res = 0;
  double res_correct = 1.3921171848959641;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_24) {
  struct token* rpn = scp_exp_to_rpn("(2+3)*(5-2)+(3+4)*(2-1)");
  double res = 0;
  double res_correct = 22;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_25) {
  struct token* rpn = scp_exp_to_rpn("23^2+45^2");
  double res = 0;
  double res_correct = 2554;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_26) {
  struct token* rpn = scp_exp_to_rpn("ln(2^5)+log(10^2)");
  double res = 0;
  double res_correct = 5.465735902799727;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_27) {
  struct token* rpn = scp_exp_to_rpn("acos(0.5)+asin(0.5)+atan(1)");
  double res = 0;
  double res_correct = 2.356194490192345;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_28) {
  struct token* rpn =
      scp_exp_to_rpn("(2+sin(0.5235987755982988))*(2-cos(1.0471975511965979))");
  double res = 0;
  double res_correct = 3.75;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_29) {
  struct token* rpn = scp_exp_to_rpn("sqrt(16+9*2)");
  double res = 0;
  double res_correct = 5.830951894845301;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_30) {
  struct token* rpn = scp_exp_to_rpn(
      "cos(0.5235987755982988)+sin(0.7853981633974483)*tan(1."
      "0471975511965979)");
  double res = 0;
  double res_correct = 2.0907702751760278;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_31) {
  struct token* rpn = scp_exp_to_rpn("sqrt(16+92)+45-2");
  double res = 0;
  double res_correct = 53.392304845413264;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_32) {
  struct token* rpn = scp_exp_to_rpn("ln(2)+log(10)-acos(0.5)");
  double res = 0;
  double res_correct = 0.6459496293633475;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_33) {
  struct token* rpn = scp_exp_to_rpn("(2+3)+((5-2)+(3+4)*(2-1))");
  double res = 0;
  double res_correct = 15;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_34) {
  struct token* rpn = scp_exp_to_rpn("23^2+45^2-sqrt(9)mod16");
  double res = 0;
  double res_correct = 2551.0;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_35) {
  struct token* rpn = scp_exp_to_rpn("ln((2^3)^2)+log(10^2)");
  double res = 0;
  double res_correct = 6.1588830833596715;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_36) {
  struct token* rpn = scp_exp_to_rpn("sqrt((16+9)*2^3)");
  double res = 0;
  double res_correct = 14.142135623730951;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_37) {
  struct token* rpn = scp_exp_to_rpn("asin(0.5)^2+atan(1)^2");
  double res = 0;
  double res_correct = 0.8910059528761227;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_38) {
  struct token* rpn = scp_exp_to_rpn("(2+sin(0.5235987755982988))*2");
  double res = 0;
  double res_correct = 5.0;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_39) {
  struct token* rpn = scp_exp_to_rpn("sqrt(16+9*2)*3");
  double res = 0;
  double res_correct = 17.492855684535904;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_40) {
  struct token* rpn = scp_exp_to_rpn("(2+3)*5+x-4mod2");
  double res = 0;
  double res_correct = 2921;
  if (rpn) {
    res = scp_calculate(rpn, 2896);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_41) {
  struct token* rpn =
      scp_exp_to_rpn("sqrt(16)+cos(x)+sin(3.14159/2)+tan(3.14159/4)");
  double res = 0;
  double res_correct = 5.42235654692368;
  if (rpn) {
    res = scp_calculate(rpn, 9339);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_42) {
  struct token* rpn = scp_exp_to_rpn("acos(1)+asin(1)+atan(1)+ln(1)+log(10)");
  double res = 0;
  double res_correct = 3.356194490192345;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_43) {
  struct token* rpn = scp_exp_to_rpn("2^3*5+15-x+sqrt(16)");
  double res = 0;
  double res_correct = -8336.0;
  if (rpn) {
    res = scp_calculate(rpn, 8395);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_44) {
  struct token* rpn =
      scp_exp_to_rpn("cos(0)+sin(3.14159/2)-tan(3.14159/x)+acos(1)");
  double res = 0;
  double res_correct = 1.9996851167572804;
  if (rpn) {
    res = scp_calculate(rpn, 9977);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_45) {
  struct token* rpn = scp_exp_to_rpn("asin(0)*atan(1)/5mod4+log(x)");
  double res = 0;
  double res_correct = 3.8042076050820413;
  if (rpn) {
    res = scp_calculate(rpn, 6371);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_46) {
  struct token* rpn =
      scp_exp_to_rpn("sqrt(x)+cos(0)-sin(3.14159/2)*tan(3.14159/4)");
  double res = 0;
  double res_correct = 86.729465754981;
  if (rpn) {
    res = scp_calculate(rpn, 7522);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_47) {
  struct token* rpn = scp_exp_to_rpn("acos(1)+asin(0)^atan(1)+ln(1)+x");
  double res = 0;
  double res_correct = 3443.0;
  if (rpn) {
    res = scp_calculate(rpn, 3443);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_48) {
  struct token* rpn = scp_exp_to_rpn("log(10)*2^3*5+x-x");
  double res = 0;
  double res_correct = 40.0;
  if (rpn) {
    res = scp_calculate(rpn, 2065);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_49) {
  struct token* rpn = scp_exp_to_rpn("sqrt(16)modx+cos(0)+sin(3.14159/2)");
  double res = 0;
  double res_correct = 5.99999999999912;
  if (rpn) {
    res = scp_calculate(rpn, 4641);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_50) {
  struct token* rpn = scp_exp_to_rpn("tan(3.14159/4)+acos(1)-asin(0)*x");
  double res = 0;
  double res_correct = 0.9999986732059836;
  if (rpn) {
    res = scp_calculate(rpn, 4033);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_51) {
  struct token* rpn = scp_exp_to_rpn("atan(1)+ln(1)*log(10)/x");
  double res = 0;
  double res_correct = 0.7853981633974483;
  if (rpn) {
    res = scp_calculate(rpn, 1924);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_52) {
  struct token* rpn = scp_exp_to_rpn("x^3*5+15-x+sqrt(16)");
  double res = 0;
  double res_correct = 29648703209.0;
  if (rpn) {
    res = scp_calculate(rpn, 1810);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_53) {
  struct token* rpn =
      scp_exp_to_rpn("cos(x)-1modx+sin(3.14159/2)*tan(3.14159/4)");
  double res = 0;
  double res_correct = 0.359324287215802;
  if (rpn) {
    res = scp_calculate(rpn, 3398);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_54) {
  struct token* rpn = scp_exp_to_rpn("acos(1)+asin(0)^atan(1)+ln(1)");
  double res = 0;
  double res_correct = 0.0;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_55) {
  struct token* rpn = scp_exp_to_rpn("log(10)*2^3*5+x-4");
  double res = 0;
  double res_correct = 198.0;
  if (rpn) {
    res = scp_calculate(rpn, 162);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_56) {
  struct token* rpn = scp_exp_to_rpn("sqrt(16)-cos(0)+sin(3.14159/2)");
  double res = 0;
  double res_correct = 3.99999999999912;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_57) {
  struct token* rpn = scp_exp_to_rpn("tan(3.14159/4)+acos(1)*asin(0)");
  double res = 0;
  double res_correct = 0.9999986732059836;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_58) {
  struct token* rpn = scp_exp_to_rpn("atan(1)+ln(1)/log(10)");
  double res = 0;
  double res_correct = 0.7853981633974483;
  if (rpn) {
    res = scp_calculate(rpn, 0);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

START_TEST(scp_correct_59) {
  struct token* rpn = scp_exp_to_rpn("2^3*5+x-4+sqrt(16)");
  double res = 0;
  double res_correct = 4339.0;
  if (rpn) {
    res = scp_calculate(rpn, 4299);
    free(rpn);
  }
  ck_assert_double_eq_tol(res, res_correct, SCP_EPS);
}
END_TEST

Suite* scp_correct_exp_tests(void) {
  Suite* s1 = suite_create(PRE_TEST_HEADER "SCP_CORRECT" POST_TEST_HEADER);
  TCase* tc1_1 = tcase_create("SCP_CORRECT");

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, scp_correct_0);
  tcase_add_test(tc1_1, scp_correct_1);
  tcase_add_test(tc1_1, scp_correct_2);
  tcase_add_test(tc1_1, scp_correct_3);
  tcase_add_test(tc1_1, scp_correct_4);
  tcase_add_test(tc1_1, scp_correct_5);
  tcase_add_test(tc1_1, scp_correct_6);
  tcase_add_test(tc1_1, scp_correct_7);
  tcase_add_test(tc1_1, scp_correct_8);
  tcase_add_test(tc1_1, scp_correct_9);
  tcase_add_test(tc1_1, scp_correct_10);
  tcase_add_test(tc1_1, scp_correct_11);
  tcase_add_test(tc1_1, scp_correct_12);
  tcase_add_test(tc1_1, scp_correct_13);
  tcase_add_test(tc1_1, scp_correct_14);
  tcase_add_test(tc1_1, scp_correct_15);
  tcase_add_test(tc1_1, scp_correct_16);
  tcase_add_test(tc1_1, scp_correct_17);
  tcase_add_test(tc1_1, scp_correct_18);
  tcase_add_test(tc1_1, scp_correct_19);
  tcase_add_test(tc1_1, scp_correct_20);
  tcase_add_test(tc1_1, scp_correct_21);
  tcase_add_test(tc1_1, scp_correct_22);
  tcase_add_test(tc1_1, scp_correct_23);
  tcase_add_test(tc1_1, scp_correct_24);
  tcase_add_test(tc1_1, scp_correct_25);
  tcase_add_test(tc1_1, scp_correct_26);
  tcase_add_test(tc1_1, scp_correct_27);
  tcase_add_test(tc1_1, scp_correct_28);
  tcase_add_test(tc1_1, scp_correct_29);
  tcase_add_test(tc1_1, scp_correct_30);
  tcase_add_test(tc1_1, scp_correct_31);
  tcase_add_test(tc1_1, scp_correct_32);
  tcase_add_test(tc1_1, scp_correct_33);
  tcase_add_test(tc1_1, scp_correct_34);
  tcase_add_test(tc1_1, scp_correct_35);
  tcase_add_test(tc1_1, scp_correct_36);
  tcase_add_test(tc1_1, scp_correct_37);
  tcase_add_test(tc1_1, scp_correct_38);
  tcase_add_test(tc1_1, scp_correct_39);
  tcase_add_test(tc1_1, scp_correct_40);
  tcase_add_test(tc1_1, scp_correct_41);
  tcase_add_test(tc1_1, scp_correct_42);
  tcase_add_test(tc1_1, scp_correct_43);
  tcase_add_test(tc1_1, scp_correct_44);
  tcase_add_test(tc1_1, scp_correct_45);
  tcase_add_test(tc1_1, scp_correct_46);
  tcase_add_test(tc1_1, scp_correct_47);
  tcase_add_test(tc1_1, scp_correct_48);
  tcase_add_test(tc1_1, scp_correct_49);
  tcase_add_test(tc1_1, scp_correct_50);
  tcase_add_test(tc1_1, scp_correct_51);
  tcase_add_test(tc1_1, scp_correct_52);
  tcase_add_test(tc1_1, scp_correct_53);
  tcase_add_test(tc1_1, scp_correct_54);
  tcase_add_test(tc1_1, scp_correct_55);
  tcase_add_test(tc1_1, scp_correct_56);
  tcase_add_test(tc1_1, scp_correct_57);
  tcase_add_test(tc1_1, scp_correct_58);
  tcase_add_test(tc1_1, scp_correct_59);

  return s1;
}
