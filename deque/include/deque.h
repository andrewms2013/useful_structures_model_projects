#pragma once

#include <stdlib.h>

typedef struct __Deque Deque;

Deque * Deque_new(void);
void Deque_free(Deque * self);

void Deque_addFirst(Deque * self, void * value);
void Deque_addLast(Deque * self, void * value);
void * Deque_removeFirst(Deque * self);
void * Deque_removeLast(Deque * self);
void * Deque_atFirst(Deque * self);
void * Deque_atLast(Deque * self);
int Deque_isEmpty(Deque * self);
int Deque_count(Deque * self);

