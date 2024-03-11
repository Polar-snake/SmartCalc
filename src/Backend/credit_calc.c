#include <stdio.h>

#include "back.h"

void annuity(double loan_amount, double interest_rate, double period,
             double *month_payment, double *amount_overpay,
             double *total_cost) {
  *month_payment = 0;
  *amount_overpay = 0;
  *total_cost = 0;
  if (interest_rate == 0) {
    *month_payment = loan_amount / period;
    *total_cost = loan_amount;
  } else {
    double month_rate =
        interest_rate / 100 / 12;  //ежем % ставка (комиссия), % ставка
    double coef_step1 = month_rate * pow((1 + month_rate), period);
    double coef_step2 = pow((1 + month_rate), period) - 1;
    double coefficient = coef_step1 / coef_step2;
    *month_payment =
        loan_amount * coefficient;  //аннуит платеж = сумма кр * коэф
    *total_cost = *month_payment * period;
    *amount_overpay = *total_cost - loan_amount;
  }
}

//Выход: ежемесячный платеж, переплата по кредиту, общая выплата
void differential(double loan_amount, double interest_rate, double period,
                  double *first_payment, double *last_payment,
                  double *amount_overpay, double *total_cost) {
  *first_payment = 0;
  *last_payment = 0;
  *amount_overpay = 0;
  *total_cost = 0;
  interest_rate /= 100;
  double main_debt = loan_amount / period;
  double month_overpay = loan_amount * interest_rate * 30.0 / 365.0;
  *first_payment = main_debt + month_overpay;
  double loan_amount_begin = loan_amount;
  loan_amount -= main_debt;
  *total_cost = *first_payment;
  for (int i = 0; i < period - 1; ++i) {
    month_overpay = loan_amount * interest_rate * 30.0 / 365.0;
    *last_payment = main_debt + month_overpay;
    loan_amount -= main_debt;
    *total_cost += *last_payment;
  }
  *amount_overpay = *total_cost - loan_amount_begin;
}

// int main() {
//   double loan_amount = 300000;
//   double interest_rate = 0;
//   double period = 10;
//   double first_payment = 0;
//   double last_payment = 0;
//   double amount_overpay = 0;
//   double total_cost = 0;
//   //    annuity(loan_amount, interest_rate, period, &month_payment,
//   //    &amount_overpay, &total_cost);
//   differential(loan_amount, interest_rate, period, &first_payment,
//                &last_payment, &amount_overpay, &total_cost);
//   // printf("%.2lf\n", month_payment);
//   printf("первый ДП: %.2lf\n", first_payment);
//   printf("последний ДП: %.2lf\n", last_payment);
//   printf("переплата: %.2lf\n", amount_overpay);
//   printf("общая ст-ть кредита: %.2lf\n", total_cost);
// }
