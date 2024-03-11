#ifndef S21_CALC_H
#define S21_CALC_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {  // giving pogonyalo to variables instead of pure numbers (e.g. 0
                // or 1)

  OK = 1,
  INCORRECT = 0,

} ret_value;

typedef enum {  // giving pogonyalo to variables instead of pure numbers (e.g. 0
                // or 1)
  prior_0 = 0,  // the least priority - open parenthesis & numbers
  prior_1 = 1,  // + & -
  prior_2 = 2,  // *, /, mod
  prior_3 = 3,  // sqrt & pow
  prior_4 = 4,  // trigonometry

} priority;

typedef enum {  // kinda global variable
  PAR = '(',
  ADD = '+',
  SUB = '-',  // subtraction
  MUL = '*',
  DIV = '/',
  MOD = '%',
  POW = '^',
  SQRT = 'Q',
  SIN = 's',
  COS = 'c',
  TAN = 't',
  ASIN = 'S',
  ACOS = 'C',
  ATAN = 'T',
  LOG = 'L',
  LN = 'l',
} symbols;

typedef struct {
  long double st_value;  // stack_value
  int elem_priority;
  void *next;
} stack_element;  // created my own new data type (собств-ый тип данных)

typedef struct {
  stack_element
      *top;  // pointer top has an address to top of stack_element struct
} top_stack;  // created my own new data type (собств-ый тип данных)

void init_stack(top_stack *stack);
int check_empty(top_stack *stack);
int push(top_stack *stack, long double value, int priority);
int pop(top_stack *stack, long double *value);
void clear_stack(top_stack *stack);
int parser(char *str, long double x, long double *result);
int parsing_number(char *str, long double x, top_stack *numbers);
int parsing_operator(char *str, top_stack *operators, top_stack *numbers);
int close_parenth(top_stack *operators, top_stack *numbers);
int count_len_and_push(char *str, top_stack *operators, top_stack *numbers);
int current_priority(char *str);
long double calculations(top_stack *numbers, top_stack *operators);
void annuity(double loan_amount, double interest_rate, double period,
             double *month_payment, double *amount_overpay, double *total_cost);
void differential(double loan_amount, double interest_rate, double period,
                  double *first_payment, double *last_payment,
                  double *amount_overpay, double *total_cost);

void print_stack(top_stack *current_stack);

#endif