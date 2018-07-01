#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <list.h>
#include <time.h>
#include <stdbool.h>

int main(void){
    List * list =  List_new();
    int * a = malloc(sizeof(int));
    int * b = malloc(sizeof(int));
    int * c = malloc(sizeof(int));
    *a = 3;
    *b = 4;
    *c = 5;
    List_add(list, a);
    List_add(list, b);
    List_add(list, c);
    for(int i = 0; i < 1; i++){
        printf("%i\n", (int)List_count(list));
        int * cur = List_removeAt(list, 1);
        printf("%i\n", *cur);
        free(cur);
    }
    for(int i = 0; i < 2; i++){
        printf("%i\n", (int)List_count(list));
        int * cur = List_at(list, i);
        printf("%i\n", *cur);
    }
    List_free(list);
    return 0;
}