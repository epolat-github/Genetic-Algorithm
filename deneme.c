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

#include <stdio.h>
 
 
int calculatePower(int base, int exponent){
    int result = 1;
    int i;
    
    for (i = 0; i < exponent; i++)
    {
        result *= base;
    }
    
    return result;
}



int main() {


    FILE *ptr = fopen("mutate", "r");

    int a = 10;

    int mutations[a];

    char str[3];
    for (size_t i = 0; i < a; i++)
    {
        fgets(str, 3, ptr);
        mutations[i] = atoi(&str);
        printf("%d\n", mutations[i]);
    }
    

    // int a = 3;
	// int b = 3;
    // int result = calculatePower(a,b);
	// printf("%d", result);

    // struct deneme deneme1;
    // struct node node1;

    // node1.value = 1;

    // strcpy(deneme1.name, "deneme1");
    // deneme1.head = &node1;

    // struct deneme best;

    // best = deneme1;

    // deneme1.head->value = 0;


    // printf("%d\n", best.head->value);




    return 0;
}