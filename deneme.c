#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct deneme{
    char name[8];
    struct node *head;
};

struct node{
    int value;
};


int main() {

    struct deneme deneme1;
    struct node node1;

    node1.value = 1;

    strcpy(deneme1.name, "deneme1");
    deneme1.head = &node1;

    struct deneme best;

    best = deneme1;

    deneme1.head->value = 0;


    printf("%d\n", best.head->value);




    return 0;
}