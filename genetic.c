#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct genes gene;
typedef struct chromosome chromosome;

typedef struct genes
{
    int value;
    gene *nextGene;

} gene;

typedef struct chromosome
{

    // int id;
    gene *headGene;
    chromosome *nextChromo;
    int fitness;
    double rank;

} chromosome;

void addGene(gene *newGene, chromosome *tailChromo, int value)
{
    newGene->nextGene = NULL;
    newGene->value = value;

    gene *geneTemp = tailChromo->headGene;

    if (geneTemp == NULL)
    {
        tailChromo->headGene = newGene;
    }
    else
    {
        while (geneTemp->nextGene != NULL)
        {
            geneTemp = geneTemp->nextGene;
        }
        geneTemp->nextGene = newGene;
    }
}

void addChromo(chromosome *newChromo, chromosome *tailChromo)
{

    newChromo->fitness = 0;
    newChromo->rank = 0;
    newChromo->headGene = NULL;
    newChromo->nextChromo = NULL;
    tailChromo->nextChromo = newChromo;
}

void printChromos(chromosome *headChromo, int POP_SIZE, int PROB_SIZE)
{
    chromosome *tempp = headChromo;
    for (size_t i = 0; i < POP_SIZE; i++)
    {
        gene *geneTemp = tempp->headGene;
        for (size_t i = 0; i < PROB_SIZE; i++)
        {
            if (geneTemp == NULL)
            {
                break;
            }
            if (i == PROB_SIZE - 1)
            {
                printf("%d %d\n", geneTemp->value, tempp->fitness);
            }
            else
            {
                printf("%d:", geneTemp->value);
            }
            geneTemp = geneTemp->nextGene;
        }
        tempp = tempp->nextChromo;
    }
}

int calculateFitness(chromosome *chromo, int PROB_SIZE)
{

    int total = 0;

    gene *temp = chromo->headGene;

    for (size_t i = 0; i < PROB_SIZE; i++)
    {
        if (temp->value == 1)
        {
            int decimal = pow(2, PROB_SIZE - i - 1);
            total += decimal;
        }

        temp = temp->nextGene;
    }
    return total;
}

int main(int argc, char *argv[])
{

    int PROB_SIZE, POP_SIZE, MAX_GEN;

    // check parameters
    if (argc != 4)
    {
        printf("Wrong number of inputs!\n");
        return 1;
    }

    // init parameters
    PROB_SIZE = atoi(argv[1]);
    POP_SIZE = atoi(argv[2]);
    MAX_GEN = atoi(argv[3]);

    //open files
    FILE *populationFilePtr = fopen("population", "r");
    FILE *selectionFilePtr = fopen("selection", "r");
    FILE *xoverFilePtr = fopen("xover", "r");
    FILE *mutateFilePtr = fopen("mutate", "r");

    //check file integrity
    if (populationFilePtr == NULL ||
        selectionFilePtr == NULL ||
        xoverFilePtr == NULL ||
        mutateFilePtr == NULL)
    {
        printf("At least a file is missing!\n");
        return 1;
    }

    // INITIALIZE POPULATION
    chromosome headChromo = {NULL, NULL, 0, 0};

    chromosome *headPtr = &headChromo;
    chromosome *tailPtr = &headChromo;

    char ch = fgetc(populationFilePtr);
    while (ch != EOF)
    {
        if (ch == '\n')
        {
            chromosome *newChromo = malloc(sizeof(chromosome));
            addChromo(newChromo, tailPtr);
            tailPtr = newChromo;
        }
        else if (ch != ':')
        {
            int value = atoi(&ch);
            gene *newGene = malloc(sizeof(gene));
            addGene(newGene, tailPtr, value);
        }
        ch = fgetc(populationFilePtr);
    }

    // FITNESS CALCULATIONS

    chromosome *temp = headPtr;

    chromosome *bestChromo;

    chromosome *worstChromo;

    while (temp->nextChromo != NULL)
    {
        int fitness = calculateFitness(temp, PROB_SIZE);
        temp->fitness = fitness;

        if(bestChromo && worstChromo){
            if(fitness < bestChromo){
                bestChromo = temp;
            }
            else if(fitness > worstChromo){
                worstChromo = temp;
            }
        }
        else{
            bestChromo = temp;
            worstChromo = temp;
        }
        

        temp = temp->nextChromo;
    }

    // RANK CALCULATIONS






    printChromos(headPtr, POP_SIZE, PROB_SIZE);

    printf("\n--------------------------------\n");

    // SORTING

}