#pragma once

#include <stdlib.h>

typedef struct __List List;

List * List_new(void);
void List_free(List * self);

void List_insert(List * self, void * value, size_t index);
void List_add(List * self, void * value);
void * List_at(List * self, size_t index);
void * List_removeAt(List * self, size_t index);
size_t List_count(List * self);

