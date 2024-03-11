#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "back.h"

#define LIMIT 9e-7
#define PRECISION 9e-1

START_TEST(calc_1) {
  char *input = "2+3";
  long double x = 0;
  long double result = 0;
  long double correct = 5;
  int return_code = parser(input, x, &result);
  ck_assert_int_eq(OK, return_code);
  ck_assert_ldouble_eq_tol(correct, result, LIMIT);
}
END_TEST

START_TEST(calc_2) {
  char *input = "2+(-5+1)";
  long double x = 0;
  long double result = 0;
  long double correct = -2;
  int return_code = parser(input, x, &result);
  ck_assert_int_eq(OK, return_code);
  ck_assert_ldouble_eq_tol(correct, result, LIMIT);
  ;
}
END_TEST

START_TEST(calc_3) {
  char *input = "-(-5+1)";
  long double x = 0;
  long double result = 0;
  long double correct = 4;
  int return_code = parser(input, x, &result);
  ck_assert_int_eq(OK, return_code);
  ck_assert_ldouble_eq_tol(correct, result, LIMIT);
}
END_TEST

START_TEST(calc_4) {
  char *input = "(-(-5+1)*3)";
  long double x = 0;
  long double result = 0;
  long double correct = 12;
  int return_code = parser(input, x, &result);
  ck_assert_int_eq(OK, return_code);
  ck_assert_ldouble_eq_tol(correct, result, LIMIT);
}
END_TEST

START_TEST(calc_5) {
  char *input = "6/(7-7)";
  long double x = 0;
  long double result = 0;
  int return_code = parser(input, x, &result);
  ck_assert_int_eq(OK, return_code);
  ck_assert_ldouble_eq(INFINITY, result);
}
END_TEST

START_TEST(calc_6) {
  char *input = "(((+2+2)*2))";
  long double x = 0;
  long double result = 0;
  long double correct = 8;
  int return_code = parser(input, x, &result);
  ck_assert_int_eq(OK, return_code);
  ck_assert_ldouble_eq_tol(correct, result, LIMIT);
}
END_TEST

START_TEST(calc_7) {
  char *input = "(2+3/4)";
  long double x = 0;
  long double result = 0;
  long double correct = 2.7500000;
  int return_code = parser(input, x, &result);
  ck_assert_int_eq(OK, return_code);
  ck_assert_ldouble_eq_tol(correct, result, LIMIT);
}
END_TEST

START_TEST(calc_8) {
  char *input = "2^(2^3))";
  long double x = 0;
  long double result = 0;
  long double correct = 256;
  int return_code = parser(input, x, &result);
  ck_assert_int_eq(OK, return_code);
  ck_assert_ldouble_eq_tol(correct, result, LIMIT);
}
END_TEST

START_TEST(calc_9) {
  char *input = "2^(2)^(3)";
  long double x = 0;
  long double result = 0;
  long double correct = 64;
  int return_code = parser(input, x, &result);
  ck_assert_int_eq(OK, return_code);
  ck_assert_ldouble_eq_tol(correct, result, LIMIT);
}
END_TEST

START_TEST(calc_10) {
  char *input = NULL;
  long double x = 0;
  long double result = 0;
  int return_code = parser(input, x, &result);
  ck_assert_ldouble_eq(INCORRECT, return_code);
}
END_TEST

START_TEST(calc_11) {
  char *input = "cos(1)+X/2";
  long double x = 6;
  long double result = 0;
  long double correct = 3.5403023;
  int return_code = parser(input, x, &result);
  ck_assert_int_eq(OK, return_code);
  ck_assert_double_eq_tol(correct, result, LIMIT);
}
END_TEST

START_TEST(calc_12) {
  char *input = "-1+(3*2)-2";
  long double x = 0;
  long double result = 0;
  long double correct = 3;
  int return_code = parser(input, x, &result);
  ck_assert_int_eq(OK, return_code);
  ck_assert_ldouble_eq_tol(correct, result, LIMIT);
}
END_TEST

START_TEST(calc_13) {
  char *input = "-1+3*2-2+cos(0)";
  long double x = 0;
  long double result = 0;
  long double correct = 4;
  int return_code = parser(input, x, &result);
  ck_assert_int_eq(OK, return_code);
  ck_assert_ldouble_eq_tol(correct, result, LIMIT);
}
END_TEST

START_TEST(calc_14) {
  char *input = "5%0";
  long double x = 0;
  long double result = 0;
  int return_code = parser(input, x, &result);
  ck_assert_int_eq(OK, return_code);
  ck_assert_ldouble_nan(result);
}
END_TEST

START_TEST(calc_15) {
  char *input = "2*X^(2)+3*X-5";
  long double x = 2;
  long double result = 0;
  long double correct = 9;
  int return_code = parser(input, x, &result);
  ck_assert_int_eq(OK, return_code);
  ck_assert_ldouble_eq_tol(correct, result, LIMIT);
}
END_TEST

START_TEST(calc_16) {
  char *input = "log(X^(2)+1)";
  long double x = 3;
  long double result = 0;
  long double correct = 1;
  int return_code = parser(input, x, &result);
  ck_assert_int_eq(OK, return_code);
  ck_assert_ldouble_eq_tol(correct, result, LIMIT);
}
END_TEST

START_TEST(calc_17) {
  char *input = "(2*X+5)*(3*X-4)";
  long double x = 3;
  long double result = 0;
  long double correct = 55;
  int return_code = parser(input, x, &result);
  ck_assert_int_eq(OK, return_code);
  ck_assert_ldouble_eq_tol(correct, result, LIMIT);
}
END_TEST

START_TEST(calc_18) {
  char *input = "sin(45)+cos(30)*tan(60)";
  long double x = 0;
  long double result = 0;
  long double correct = 0.9002702;
  int return_code = parser(input, x, &result);
  ck_assert_int_eq(OK, return_code);
  ck_assert_ldouble_eq_tol(correct, result, LIMIT);
}
END_TEST

START_TEST(calc_19) {
  char *input = "ln(2)/log(10)";
  long double x = 0;
  long double result = 0;
  long double correct = 0.6931472;
  int return_code = parser(input, x, &result);
  ck_assert_int_eq(OK, return_code);
  ck_assert_ldouble_eq_tol(correct, result, LIMIT);
}
END_TEST

START_TEST(calc_20) {
  char *input =
      "((3+5)*(7-2))/4^(2)+sin(60)-log(100)*2^(3)+acos(0.5)-atan("
      "1)";  //-13.8048106211+1.0471982-0.7853982
  long double x = 0;
  long double result = 0;
  long double correct = -13.5430112;
  int return_code = parser(input, x, &result);
  ck_assert_int_eq(OK, return_code);
  ck_assert_ldouble_eq_tol(correct, result, LIMIT);

  // CREDIT CALC
}
END_TEST

START_TEST(credit_an_1) {
  double summ = 300000;
  double period = 18;
  double interest = 15;
  double payment = 0;
  double correct_payment = 18715.44;
  double overpay = 0;
  double correct_overpay = 36877.85;
  double total = 0;
  double correct_total = 336877.85;
  annuity(summ, interest, period, &payment, &overpay, &total);
  ck_assert_double_eq_tol(correct_payment, payment, PRECISION);
  ck_assert_double_eq_tol(correct_overpay, overpay, PRECISION);
  ck_assert_double_eq_tol(correct_total, total, PRECISION);
}
END_TEST

START_TEST(credit_an_2) {
  double summ = 300000;
  double period = 10;
  double interest = 10.5;
  double payment = 0;
  double correct_payment = 31462.61;
  double overpay = 0;
  double correct_overpay = 14626.14;
  double total = 0;
  double correct_total = 314626.14;
  annuity(summ, interest, period, &payment, &overpay, &total);
  ck_assert_double_eq_tol(correct_payment, payment, PRECISION);
  ck_assert_double_eq_tol(correct_overpay, overpay, PRECISION);
  ck_assert_double_eq_tol(correct_total, total, PRECISION);
}
END_TEST

START_TEST(credit_an_3) {
  double summ = 0;
  double period = 10;
  double interest = 10.5;
  double payment = 0;
  double correct_payment = 0;
  double overpay = 0;
  double correct_overpay = 0;
  double total = 0;
  double correct_total = 0;
  annuity(summ, interest, period, &payment, &overpay, &total);
  ck_assert_double_eq_tol(correct_payment, payment, PRECISION);
  ck_assert_double_eq_tol(correct_overpay, overpay, PRECISION);
  ck_assert_double_eq_tol(correct_total, total, PRECISION);
}
END_TEST

START_TEST(credit_an_4) {
  double summ = 300000;
  double period = 10;
  double interest = 0;
  double payment = 0;
  double correct_payment = 30000;
  double overpay = 0;
  double correct_overpay = 0;
  double total = 0;
  double correct_total = 300000;
  annuity(summ, interest, period, &payment, &overpay, &total);
  ck_assert_double_eq_tol(correct_payment, payment, PRECISION);
  ck_assert_double_eq_tol(correct_overpay, overpay, PRECISION);
  ck_assert_double_eq_tol(correct_total, total, PRECISION);
}
END_TEST

START_TEST(credit_diff_1) {
  int flag_1 = 0;
  int flag_2 = 0;
  int flag_3 = 0;
  int flag_4 = 0;
  double summ = 300000;
  double period = 18;
  double interest = 15;
  double first_payment = 0;
  double last_payment = 0;
  double overpay = 0;
  double total = 0;
  differential(summ, interest, period, &first_payment, &last_payment, &overpay,
               &total);
  if (first_payment >= 20355.19 && first_payment <= 20416.67) flag_1 = 1;
  if (last_payment >= 16666.67 && last_payment <= 16875.00) flag_2 = 1;
  if (overpay >= 35000.00 && overpay <= 35625.00) flag_3 = 1;
  if (total >= 335000.00 && total <= 335625.00) flag_4 = 1;
  ck_assert_int_eq(OK, flag_1);
  ck_assert_int_eq(OK, flag_2);
  ck_assert_int_eq(OK, flag_3);
  ck_assert_int_eq(OK, flag_4);
}
END_TEST

START_TEST(credit_diff_2) {
  int flag_1 = 0;
  int flag_2 = 0;
  int flag_3 = 0;
  int flag_4 = 0;
  double summ = 300000;
  double period = 0;
  double interest = 15;
  double first_payment = 0;
  double last_payment = 0;
  double overpay = 0;
  double total = 0;
  differential(summ, interest, period, &first_payment, &last_payment, &overpay,
               &total);
  if (first_payment == INFINITY) flag_1 = 1;
  if (last_payment == 0) flag_2 = 1;
  if (overpay == INFINITY) flag_3 = 1;
  if (total == INFINITY) flag_4 = 1;
  ck_assert_int_eq(OK, flag_1);
  ck_assert_int_eq(OK, flag_2);
  ck_assert_int_eq(OK, flag_3);
  ck_assert_int_eq(OK, flag_4);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("CALCULATIONS TEST RESULT");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, calc_1);
  tcase_add_test(tc1_1, calc_2);
  tcase_add_test(tc1_1, calc_3);
  tcase_add_test(tc1_1, calc_4);
  tcase_add_test(tc1_1, calc_5);
  tcase_add_test(tc1_1, calc_6);
  tcase_add_test(tc1_1, calc_7);
  tcase_add_test(tc1_1, calc_8);
  tcase_add_test(tc1_1, calc_9);
  tcase_add_test(tc1_1, calc_10);
  tcase_add_test(tc1_1, calc_11);
  tcase_add_test(tc1_1, calc_12);
  tcase_add_test(tc1_1, calc_13);
  tcase_add_test(tc1_1, calc_14);
  tcase_add_test(tc1_1, calc_15);
  tcase_add_test(tc1_1, calc_16);
  tcase_add_test(tc1_1, calc_17);
  tcase_add_test(tc1_1, calc_18);
  tcase_add_test(tc1_1, calc_19);
  tcase_add_test(tc1_1, calc_20);
  tcase_add_test(tc1_1, credit_an_1);
  tcase_add_test(tc1_1, credit_an_2);
  tcase_add_test(tc1_1, credit_an_3);
  tcase_add_test(tc1_1, credit_an_4);
  tcase_add_test(tc1_1, credit_diff_1);
  tcase_add_test(tc1_1, credit_diff_2);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
