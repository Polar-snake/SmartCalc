#include "back.h"

int parser(char *str, long double x, long double *result) {
  int ret_code = 1;
  if (!str || strlen(str) > 255) {
    return 0;
  }
  int pointer_mover = 0;
  int switch_unary =
      1;  // индикатор начала строки, равен 1 только в начале строки
  top_stack numbers;
  top_stack operators;
  init_stack(&numbers);
  init_stack(&operators);
  while (*str != '\0') {
    if ((*str >= '0' && *str <= '9') || *str == 'X') {
      pointer_mover = parsing_number(str, x, &numbers);
    } else if (*str == ')') {
      pointer_mover = close_parenth(&operators, &numbers);
    } else if ((*str == '+' || *str == '-') && switch_unary == 1) {
      push(&numbers, 0, prior_0);  // -2 = 0-2
      pointer_mover = parsing_operator(str, &operators, &numbers);
    } else {
      pointer_mover = parsing_operator(str, &operators, &numbers);
    }
    str += pointer_mover;
    switch_unary = 0;
  }
  while (check_empty(&operators) != 0) {
    *result = calculations(&numbers, &operators);
    push(&numbers, *result, prior_0);
  }
  if (check_empty(&numbers) != 0 && check_empty(&operators) == 0) {
    *result = numbers.top->st_value;
  }
  clear_stack(&numbers);
  return ret_code;
}

int parsing_number(char *str, long double x, top_stack *numbers) {
  int pointer_mover = 0;
  int start_strlen = strlen(str);
  int end_strlen = 0;
  if (*str == 'X') {
    push(numbers, x, prior_0);
    pointer_mover = 1;
  } else {
    long double value =
        strtold(str,
                &str);  // 1 арг - начало строки, 2 арг - куда strtold двигает
                        // указатель, пока не встретит не число
    push(numbers, value, prior_0);
    end_strlen = strlen(str);
    pointer_mover = start_strlen - end_strlen;
  }
  return pointer_mover;
}

int parsing_operator(char *str, top_stack *operators, top_stack *numbers) {
  int pointer_mover = 0;
  int ret_prior = current_priority(str);
  long double prev_result = 0;  // result of previous operator in stack
  if (check_empty(operators) == 0 || *str == '(') {
    pointer_mover = count_len_and_push(str, operators, numbers);
  } else {
    if (ret_prior > operators->top->elem_priority) {
      pointer_mover = count_len_and_push(str, operators, numbers);
    } else if (check_empty(operators) != 0 &&
               ret_prior <= operators->top->elem_priority && *str != '(') {
      while (check_empty(operators) != 0 &&
             ret_prior <= operators->top->elem_priority) {
        prev_result = calculations(numbers, operators);
        push(numbers, prev_result, prior_0);
      }
      pointer_mover = count_len_and_push(str, operators, numbers);
    } else {
      pointer_mover = count_len_and_push(str, operators, numbers);
    }
  }
  return pointer_mover;
}

int close_parenth(top_stack *operators, top_stack *numbers) {
  int pointer_mover = 1;
  if (check_empty(operators) != 0) {
    while (check_empty(operators) != 0 && operators->top->st_value != '(') {
      long double temp_calc = calculations(numbers, operators);
      push(numbers, temp_calc, prior_0);
    }
    if (check_empty(operators) != 0 && operators->top->st_value == '(') {
      long double del_extra = 0;
      pop(operators, &del_extra);
    }
  }
  return pointer_mover;
}

int current_priority(char *str) {
  int prior_select = 0;
  if (*str == PAR) {
    prior_select = prior_0;
  } else if (*str == ADD || *str == SUB) {
    prior_select = prior_1;
  } else if (*str == MUL || *str == DIV || *str == MOD) {
    prior_select = prior_2;
  } else if (*str == SQRT || *str == POW) {
    prior_select = prior_3;
  } else {
    prior_select = prior_4;
  }
  return prior_select;
}

int count_len_and_push(char *str, top_stack *operators,
                       top_stack *numbers) {  // counts len of the operator
  int pointer_mover = 1;  // when *str == PAR, ADD, SUB, MUL, DIV, MOD etc
  if (*str == '(') {
    str++;
    if (*str == '+' || *str == '-') {
      push(numbers, 0, prior_0);
    }
    push(operators, PAR, prior_0);
  } else if (*str == '+' || *str == '-') {
    push(operators, *str, prior_1);
  } else if (*str == '*' || *str == '/' || *str == '%') {
    push(operators, *str, prior_2);
  } else if (*str == '^') {
    push(operators, *str, prior_3);
  } else if (*str == 'l') {
    str++;
    if (*str == 'o') {
      pointer_mover = 3;  // log
      push(operators, LOG, prior_4);
    } else {
      pointer_mover = 2;  // ln
      push(operators, LN, prior_4);
    }
  } else if (*str == 's' || *str == 'c' || *str == 't') {
    str++;
    if (*str == 'q') {
      pointer_mover = 4;
      push(operators, SQRT, prior_4);
    } else {
      str--;
      pointer_mover = 3;
      push(operators, *str, prior_4);
    }
  } else if (*str == 'a') {
    str++;
    push(operators, *str - 32, prior_4);  // c,s,t - 32; ASCII shift
    pointer_mover = 4;
  }
  return pointer_mover;
}

long double calculations(top_stack *numbers, top_stack *operators) {
  long double result = 0;
  long double prev_operator = 0;
  long double a = 0, b = 0;
  if (check_empty(operators) != 0 && check_empty(numbers) != 0) {
    pop(operators, &prev_operator);
    pop(numbers, &a);
    if (prev_operator == ADD) {
      pop(numbers, &b);
      result = b + a;
    } else if (prev_operator == SUB) {
      pop(numbers, &b);
      result = b - a;
    } else if (prev_operator == MUL) {
      pop(numbers, &b);
      result = b * a;
    } else if (prev_operator == DIV) {
      pop(numbers, &b);
      result = b / a;
    } else if (prev_operator == MOD) {
      pop(numbers, &b);
      if (a == 0)
        result = NAN;
      else
        result = (int)b % (int)a;
    } else if (prev_operator == POW) {
      pop(numbers, &b);
      result = powl(b, a);  // long double
    } else if (prev_operator == SQRT) {
      result = sqrtl(a);
    } else if (prev_operator == SIN) {
      result = sinl(a);
    } else if (prev_operator == COS) {
      result = cosl(a);
    } else if (prev_operator == TAN) {
      result = tanl(a);
    } else if (prev_operator == ASIN) {
      result = asinl(a);
    } else if (prev_operator == ACOS) {
      result = acosl(a);
    } else if (prev_operator == ATAN) {
      result = atanl(a);
    } else if (prev_operator == LOG) {
      result = log10l(a);
    } else if (prev_operator == LN) {
      result = logl(a);
    }
  }
  return result;
}

// int main() {
//     char *str = "-3^2";
//     long double result = 0;
//     long double x = 3;
//     parser(str, x, &result);
//     printf("result: %Lf\n", result);
//     return 0;
// }

// for otladka
void print_stack(top_stack *current_stack) {
  stack_element *temp = current_stack->top;
  while (temp != NULL) {
    printf("%Lf\n", temp->st_value);
    // printf("%p\n", &temp->st_value);
    temp = temp->next;
  }
}
