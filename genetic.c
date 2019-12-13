#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    chromosome *previousChromo;
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
    // tailChromo->nextChromo = newChromo;
}

void printChromos(chromosome *headChromo, int POP_SIZE, int PROB_SIZE)
{
    chromosome *tempp = headChromo;
    for (size_t i = 0; i < POP_SIZE; i++)
    {
        gene *geneTemp = tempp->headGene;
        for (size_t i = 0; i < PROB_SIZE; i++)
        {
            // if (geneTemp == NULL)
            // {
            //     break;
            // }
            if (i == PROB_SIZE - 1)
            {
                printf("%d %d %f\n", geneTemp->value, tempp->fitness, tempp->rank);
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

int calculatePower(int base, int exponent)
{
    int result = 1;
    int i;

    for (i = 0; i < exponent; i++)
    {
        result *= base;
    }

    return result;
}

int calculateFitness(chromosome *chromo, int PROB_SIZE)
{

    int total = 0;

    gene *temp = chromo->headGene;

    for (size_t i = 0; i < PROB_SIZE; i++)
    {
        if (temp->value == 1)
        {
            int decimalValue = calculatePower(2, PROB_SIZE - i - 1);
            total += decimalValue;
        }

        temp = temp->nextGene;
    }
    return total;
}

double calculateRank(chromosome *chromo, chromosome *best, chromosome *worst)
{
    double chromoFitness = chromo->fitness;
    double bestFitness = best->fitness;
    double worstFitness = worst->fitness;

    if (bestFitness == worstFitness)
    {
        return 0; //check
    }

    double result = ((chromoFitness - bestFitness) / (worstFitness - bestFitness));
    return result;
}

void sortChromos(chromosome *head, int POP_SIZE)
{
    chromosome *tempBestHead = NULL;
    chromosome *tempChromo = head;
    chromosome *lastChromoHolder = NULL;
    chromosome *leastFitnessChromo = head;
    chromosome *previousChromo = NULL;
    chromosome *nextChromo = head->nextChromo;

    for (size_t i = 0; i < 8; i++)
    {

        while (tempChromo->nextChromo != NULL)
        {
            if (tempChromo->fitness < leastFitnessChromo->fitness)
            {
                leastFitnessChromo = tempChromo;
                previousChromo = lastChromoHolder;
                nextChromo = tempChromo->nextChromo;
            }
            lastChromoHolder = tempChromo;
            tempChromo = tempChromo->nextChromo;
        }
        printf("least: %d\n", leastFitnessChromo->fitness);
        if (previousChromo != NULL)
        {
            previousChromo->nextChromo = nextChromo;
            printf("previous of the least: %d\n", previousChromo->fitness);
        }
        else
        {
            head = nextChromo;
        }

        printf("next of the least: %d\n", nextChromo->fitness);

        if (tempBestHead == NULL)
        {
            leastFitnessChromo->nextChromo = NULL;
            tempBestHead = leastFitnessChromo;
        }
        else
        {
            chromosome *lastTerm = tempBestHead;
            while (lastTerm->nextChromo != NULL)
            {
                lastTerm = lastTerm->nextChromo;
            }
            leastFitnessChromo->nextChromo = NULL;
            lastTerm->nextChromo = leastFitnessChromo;
        }

        printChromos(head, 7, 10);
        printf("\n\n");
        printChromos(tempBestHead, 1, 10);
    }

    // while (tempChromo->nextChromo != NULL)
    // {
    //     if(tempChromo->fitness < leastFitnessChromo->fitness)
    //     {
    //         leastFitnessChromo = tempChromo;
    //     }
    //     tempChromo = tempChromo->nextChromo;
    // }
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
    chromosome headChromo = {NULL, NULL, NULL, 0, 0};

    chromosome *headPtr = malloc(sizeof(chromosome));
    headPtr = &headChromo;
    chromosome *tailPtr = malloc(sizeof(chromosome));
    tailPtr = &headChromo;
    int chromoCount = 0;

    char ch = fgetc(populationFilePtr);
    while (ch != EOF)
    {
        if (ch == '\n')
        {

            chromosome *newChromo = malloc(sizeof(chromosome));
            addChromo(newChromo, tailPtr);

            tailPtr->nextChromo = newChromo;

            tailPtr = tailPtr->nextChromo;
        }
        else if (ch != ':')
        {
            int value = atoi(&ch);
            gene *newGene = malloc(sizeof(gene));
            addGene(newGene, tailPtr, value);
        }
        ch = fgetc(populationFilePtr);
    }

    // for (size_t i = 0; i < MAX_GEN; i++)
    // {

    // FITNESS CALCULATIONS

    chromosome *tempChromoFitness = headPtr;

    chromosome *bestFitness;

    chromosome *worstFitness;

    while (tempChromoFitness->nextChromo != NULL)
    {
        int fitness = calculateFitness(tempChromoFitness, PROB_SIZE);
        tempChromoFitness->fitness = fitness;

        if (bestFitness && worstFitness)
        {
            if (fitness < bestFitness->fitness)
            {
                bestFitness = tempChromoFitness;
            }
            else if (fitness > worstFitness->fitness)
            {
                worstFitness = tempChromoFitness;
            }
        }
        else
        {
            bestFitness = tempChromoFitness;
            worstFitness = tempChromoFitness;
        }

        tempChromoFitness = tempChromoFitness->nextChromo;
    }

    // RANK CALCULATIONS

    chromosome *tempChromoRank = headPtr;

    chromosome *bestRank;
    chromosome *worstRank;

    while (tempChromoRank->nextChromo != NULL)
    {
        double rank = calculateRank(tempChromoRank, bestFitness, worstFitness);
        tempChromoRank->rank = rank;

        if (bestRank && worstRank)
        {
            if (rank < bestRank->rank)
            {
                bestRank = tempChromoRank;
            }
            else if (rank > worstRank->rank)
            {
                worstRank = tempChromoRank;
            }
        }
        else
        {
            bestRank = tempChromoRank;
            worstRank = tempChromoRank;
        }

        tempChromoRank = tempChromoRank->nextChromo;
    }

    // printChromos(headPtr, POP_SIZE, PROB_SIZE);

    // printf("------------------------\n");

    sortChromos(headPtr, POP_SIZE);

    // SORTING
    // }
}