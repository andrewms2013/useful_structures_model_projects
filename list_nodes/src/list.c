#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "../include/list.h"

typedef struct __ListNode ListNode;

struct __ListNode {
	void * value;
	ListNode * next;
    ListNode * prev;
};

struct __List{
    ListNode *first;
    int length;
};

List * List_new(void){
    List * new = malloc(sizeof(List));
    if(new == NULL){
        fprintf(stderr, "Out of memory");
        abort();
    }
    new->first = NULL;
    new->length = 0;
    return new;
}

void List_free(List * self){
    if(self == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return;
    }
    while(self->length != 0){
        void * val = List_removeAt(self, 0);
        free(val);
    }
    free(self);
}

void List_insert(List * self, void * value, size_t index){
    if(self == NULL || value == NULL || index > self->length){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return;
    }
    if(self->first == NULL){
        List_add(self, value);
    }
    else if(index == self->length){
        List_add(self, value);
    }
    else{
        ListNode * new = malloc(sizeof(ListNode));
        new->value = value; 
        ListNode * current = self->first;
        for(int i = 0; i < self->length; i++){
            if(i == index){
                new->prev = current->prev;
                new->next = current;
                if(i != 0){
                    current->prev->next = new;
                }
                else{
                    self->first = new;
                }
                current->prev = new;
                break;
            }
            else{
                current = current->next;
            }
        }
        self->length++;
    }
}

void List_add(List * self, void * value){
    if(self == NULL || value == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return;
    }
    ListNode * new = malloc(sizeof(ListNode));
    new->value = value;
    new->next = NULL;
    if(self->first == NULL){
        self->first = new;
        new->prev = NULL;
    }
    else{
        int i = 0;
        ListNode * current = self->first;
        while(i < self->length-1){
            current = current->next;
            i++;
        }
        current->next = new;
        new->prev = current;
    }
    self->length += 1;
}

void * List_at(List * self, size_t index){
    if(self == NULL || index >= self->length){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return NULL;
    }
    int i = 0;
    ListNode * current = self->first;
    while(i < index){
        current = current->next;
        i++;
    }
    void * val = current->value;
    return val;
}

void * List_removeAt(List * self, size_t index){
    if(self == NULL || index >= self->length){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return NULL;
    }
    int i = 0;
    ListNode * current = self->first;
    while(i < index){
        current = current->next;
        i++;
    }
    void * val = current->value;
    if(i == 0){
        if(self->first->next){
            self->first->next->prev = NULL;
        }
        self->first = self->first->next;
    }
    else if(i == self->length-1){
        current->prev->next = NULL;
    }
    else{
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }
    self->length--;
    free(current);
    return val;
}

size_t List_count(List * self){
    if(self == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return 0;
    }
    return self->length;
}