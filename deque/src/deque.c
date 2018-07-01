#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "../include/deque.h"

typedef struct __ListNode ListNode;

struct __ListNode {
	void * value;
	ListNode * next;
    ListNode * prev;
};

struct __Deque{
    ListNode * first;
    ListNode * last;
    int length;
};

Deque * Deque_new(void){
    Deque * new = malloc(sizeof(Deque));
    if(new == NULL){
        fprintf(stderr, "Out of memory");
        abort();
    }
    new->first = NULL;
    new->last = NULL;
    new->length = 0;
    return new;
}
void Deque_free(Deque * self){
    if(self == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return;
    }
    while(self->length != 0){
        void * val = Deque_removeFirst(self);
        free(val);
    }
    free(self);
}

void Deque_addFirst(Deque * self, void * value){
    if(self == NULL || value == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return;
    }
    ListNode * new = malloc(sizeof(ListNode));
    new->value = value; 
    if(self->first == NULL){
        self->first = new;
        self->last = new;
        new->next = NULL;
        new->prev = NULL;
    }
    else{
        self->first->prev = new;
        new->next = self->first;
        self->first = new;
        self->first->prev = NULL;
    }
    self->length++;
}
void Deque_addLast(Deque * self, void * value){
    if(self == NULL || value == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return;
    }
    ListNode * new = malloc(sizeof(ListNode));
    new->value = value; 
    if(self->last == NULL){
        self->first = new;
        self->last = new;
        new->next = NULL;
        new->prev = NULL;
    }
    else{
        self->last->next = new;
        new->prev = self->last;
        self->last = new;
        self->first->next = NULL;
    }
    self->length++;
}

void * Deque_removeFirst(Deque * self){
    if(self == NULL || self->length == 0){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return NULL;
    }
    self->length --;
    void * val = self->first->value;
    if(self->length == 1){
        free(self->first);
        self->first = NULL;
        self->last = NULL;
        return val;
    }
    else{
        self->first->next->prev = NULL;
        self->first = self->first->next;
        free(self->first);
        return val;
    }
}

void * Deque_removeLast(Deque * self){
    if(self == NULL || self->length == 0){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return NULL;
    }
    self->length --;
    void * val = self->last->value;
    if(self->length == 1){
        free(self->last);
        self->first = NULL;
        self->last = NULL;
        return val;
    }
    else{
        self->last->prev->next = NULL;
        self->last = self->last->prev;
        free(self->last);
        return val;
    }
}
void * Deque_atFirst(Deque * self){
    if(self == NULL || self->length == 0){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return NULL;
    }
    void * val = self->first->value;
    return val;
}
void * Deque_atLast(Deque * self){
    if(self == NULL || self->length == 0){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return NULL;
    }
    void * val = self->first->value;
    return val;
}
int Deque_isEmpty(Deque * self){
    if(self == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return 0;
    }
    int result = 0;
    if(self->length > 0){
        result = 1;
    }
    return result;
}
int Deque_count(Deque * self){
    if(self == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return 0;
    }
    return self->length;
}