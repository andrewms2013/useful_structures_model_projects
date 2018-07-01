#pragma once

#include <stdbool.h>

typedef struct __Stack Stack;

Stack * Stack_new(void);
void Stack_free(Stack * self);

void Stack_push(Stack * self, void * val);
void * Stack_peek(Stack * self);
void * Stack_pop(Stack * self);
bool Stack_isEmpty(Stack * self);