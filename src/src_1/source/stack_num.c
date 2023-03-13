#include "backend.h"

// вставляет узел на вершину стека
void push_num(StackNumPtr *topPtr, double num) {
  StackNumPtr newPtr;  // указатель на новый узел
  newPtr = malloc(sizeof(StackNum));

  // вставить узел на вершину стека
  if (newPtr != NULL) {
    newPtr->num = num;
    newPtr->next = *topPtr;  // указывает на предыдущий узел
    *topPtr = newPtr;
  }
}  // конец функции

// удаляет узел с вершины
double pop_num(StackNumPtr *topPtr) {
  StackNumPtr temp;  // временный указатель на узел
  double ret_value;  // возвращаемое значение

  temp = *topPtr;
  ret_value = (*topPtr)->num;
  *topPtr = (*topPtr)->next;
  free(temp);
  return ret_value;
}

// освобождает память под стек
void destroy_num(StackNumPtr *topPtr) {
  StackNumPtr last;
  StackNumPtr temp;

  last = *topPtr;
  while (last) {
    if (last->next == NULL) return (free(last));
    temp = last->next;
    free(last);
    last = temp;
  }
}
