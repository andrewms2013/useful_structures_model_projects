#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <list.h>

static const short INITIAL_CAPACITY = 16;

struct __List{
    void ** items;
    int capacity;
    int length;
};

static void List_realloc(List * self){
    List* temp = self;
    self->items = realloc(self->items, sizeof(void *) * self->capacity * 2);
    if(self->items == NULL){
        List_free(temp);
        fprintf(stderr, "Out of memory");
        abort();
    }
    self->capacity *= 2;
}

List * List_new(void){
    List * self = malloc(sizeof(List));
    if(self == NULL){
        fprintf(stderr, "Out of memory");
        abort();
    }
    self->length = 0;
    self->capacity = INITIAL_CAPACITY;
    self->items = malloc(sizeof(void*) * self->capacity); 
    if(self->items == NULL){
        free(self);
        fprintf(stderr, "Out of memory");
        abort();
    }
    return self;
}

void List_free(List * self){
    if(self == NULL){
        return;
    }
    free(self->items);
    free(self);
}

void List_add(List * self, void * value){
    if(self == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return;
    }
    if(self->length >= self->capacity - 1){
        List_realloc(self);
    }
    self->items[self->length] = value;
    self->length++;
}

void * List_at(List * self, size_t index){
    if(self == NULL || index >= self->length){
        assert(0 && "Invalid pointer or index");
        fprintf(stderr, "Invalid pointer or index");
        return NULL;
    }
    return self->items[index];
}

size_t List_count(List * self){
    if(self == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return 0;
    }
    return self->length;
}
void List_insert(List * self, void * value, size_t index){
    if(self == NULL || value == NULL || index >= self->length){
        assert(0 && "Invalid pointer or index");
        fprintf(stderr, "Invalid pointer or index");
        return;
    }
    self->length += 1;
    if(self->length >= self->capacity - 1){
        List_realloc(self);
    }
    int newIndex = index;
    for(int i = self->length - 1; i >= newIndex; i--){
        self->items[i + 1] = self->items[i];
    }
    self->items[index] = value;
}


void * List_removeAt(List * self, size_t index){
    if(self == NULL || index > self->length){
        assert(0 && "Invalid pointer or index");
        fprintf(stderr, "Invalid pointer or index");
        return NULL;
    }
    void * toRemove = self->items[index];
    for(int i = index; i < self->length - 1; i++){
        self->items[i] = self->items[i + 1];
    }
    self->length -= 1;
    return toRemove;
}

// iterator

struct __Iterator{
    List * list;
    int index;
};

static Iterator * Iterator_new(List * list, int index){
    if(list == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return 0;
    }
    Iterator * self = malloc(sizeof(Iterator));
    if(self == NULL){
        fprintf(stderr, "Out of memory");
        abort();
    }
    self->list = list;
    self->index = index;
    return self;
}

Iterator * List_getNewBeginIterator (List * self){
    if(self == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return NULL;
    }
    return Iterator_new(self, 0);
}

Iterator * List_getNewEndIterator   (List * self){
    if(self == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return NULL;
    }
    return Iterator_new(self, List_count(self));
}

void Iterator_free(Iterator * self){
    if(self == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return;
    }
    free(self);
}

void * Iterator_value    (Iterator * self){
    assert(self->index < List_count(self->list) && self->index >= 0);
    return List_at(self->list, self->index);
}

void   Iterator_next     (Iterator * self){
    if(self == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return;
    }
    self->index++;
}

void   Iterator_prev     (Iterator * self){
    if(self == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return;
    }
    self->index--;
}

void   Iterator_advance  (Iterator * self, IteratorDistance n){
    if(self == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return;
    }
    self->index += n;
}

bool   Iterator_equals   (Iterator * self, Iterator * other){
    if(self == NULL || other == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return false;
    }
    return ((self->list == other->list) && (self->index == other->index));
}

IteratorDistance Iterator_distance (Iterator * begin, Iterator * end){
    if(begin == NULL || end == NULL){
        assert(0 && "Invalid pointer");
        fprintf(stderr, "Invalid pointer");
        return 0;
    }
    return end->index - begin->index;
}