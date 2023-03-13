#include "backend.h"

int is_empty(StackOpPtr *topPtr) { return *topPtr == NULL; }

// вставляет узел на вершину стека
void push(StackOpPtr *topPtr, char op, int priority) {
  StackOpPtr newPtr;  // указатель на новый узел
  newPtr = malloc(sizeof(StackOp));

  // вставить узел на вершину стека
  if (newPtr != NULL) {
    newPtr->op = op;
    newPtr->priority = priority;
    newPtr->next = *topPtr;  // указывает на предыдущий узел
    *topPtr = newPtr;
  }
}  // конец функции

// удаляет узел с вершины
int pop(StackOpPtr *topPtr) {
  StackOpPtr temp;  // временный указатель на узел
  int ret_value;    // возвращаемое значение

  temp = *topPtr;
  ret_value = (*topPtr)->op;
  *topPtr = (*topPtr)->next;
  free(temp);
  return ret_value;
}

int show_priority(StackOpPtr *topPtr) { return (*topPtr)->priority; }

// освобождает память под стек
void destroy(StackOpPtr *topPtr) {
  StackOpPtr last;
  StackOpPtr temp;

  last = *topPtr;
  while (last) {
    if (last->next == NULL) return (free(last));
    temp = last->next;
    free(last);
    last = temp;
  }
}
