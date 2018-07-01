#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "../include/stack.h"

struct ListNode {
	void * value;
	struct ListNode * next;
};

struct __Stack{
    struct ListNode *top;
};

Stack * Stack_new(void){
    Stack * self = malloc(sizeof(Stack));
    if(self == NULL){
        fprintf(stderr, "Out of memory");
        abort();
    }
    self->top = NULL;
    return self;
}

void Stack_free(Stack * self){
    assert(self != NULL);
    while(self->top != NULL){
        void * temp = Stack_pop(self);
        free(temp);
    }
    free(self);
}

void Stack_push(Stack * self, void * val){
    assert(self != NULL);
    struct ListNode * newNode = malloc(sizeof(struct ListNode));
    newNode->value = val;
    newNode->next = self->top;
    self->top = newNode;
}

void * Stack_peek(Stack * self){
    assert(self != NULL);
    return self->top->value;
}

bool Stack_isEmpty(Stack * self){
    if(self->top == NULL){
        return true;
    }
    else{
        return false;
    }
}

void * Stack_pop(Stack * self){
    assert(self != NULL);
    void * val = NULL;
    if(self->top != NULL){
        val = self->top->value;
        struct ListNode * temp = self->top;
        self->top = self->top->next;
        free(temp);
    }
    return val;
}