#include "back.h"

void init_stack(top_stack *stack) { /*if we want to change a variable, we need a
pointer otherwise we don't need a pointer*/
  stack->top = NULL;                // stack was initialized
}

int check_empty(top_stack *stack) {  // check for empty stack
  int ret_code = 0;                  // return 0 if empty, 1 if not empty
  if (stack->top != NULL) {
    ret_code = 1;
  }
  return ret_code;
}

int push(top_stack *stack, long double value, int priority) {
  int ret_code = INCORRECT;
  stack_element *new_stack_elem =
      (stack_element *)calloc(1, sizeof(stack_element));
  if (new_stack_elem != NULL) {
    new_stack_elem->st_value = value;
    new_stack_elem->elem_priority = priority;
    new_stack_elem->next =
        stack->top;  // Указываем на текущий верхний элемент стека
    stack->top = new_stack_elem;  // Обновляем указатель на вершину стека
    ret_code = OK;
  }

  return ret_code;
}

int pop(top_stack *stack,
        long double *value) {  // we put pointer because value will be changed
  int ret_code = INCORRECT;
  if (check_empty(stack) != 0) {
    *value = stack->top->st_value;  // извлекаем значение из верхушки стека
    stack_element *temp = stack->top;  // сохраняем указатель на верхушку стека
                                       // во временной переменной
    stack->top = stack->top->next;  // обновляем указатель на верхушку стека на
                                    // следующий элемент
    free(temp);  // освобождаем память, занимаемую удаленным элементом
    ret_code = OK;  // обновляем код возврата, чтобы указать успешное выполнение
                    // операции
  }
  return ret_code;
}

void clear_stack(top_stack *stack) {
  while (stack->top != NULL) {
    stack_element *temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
  }
}
