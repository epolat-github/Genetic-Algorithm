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
    int fitness;
    double rank;

} chromosome;

void addGene(gene *newGene, chromosome *tailChromo, int value)
{
    newGene->nextGene = (gene*)NULL;
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
            if (geneTemp == NULL)
            {
                break;
            }
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

chromosome *sortChromos(chromosome *head, int POP_SIZE)
{
    chromosome *tempHead = head;
    chromosome *tempBestHead = NULL;       //temporary head pointer
    chromosome *tempChromo = head;         //to iterate over chromos
    chromosome *lastChromoHolder = NULL;   //to hold last chromo before the current chromo
    chromosome *leastFitnessChromo = head; //least chromo
    chromosome *previousChromo = NULL;     //previous chromo of the least
    chromosome *nextChromo = NULL;         //next chromo of the least

    for (size_t i = 0; i < 8; i++)
    {
        // printf("girdi\n");

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
        // printf("least: %d\n", leastFitnessChromo->fitness);
        if (tempHead != leastFitnessChromo)
        {
            previousChromo->nextChromo = nextChromo;
            // printf("previous of the least: %d\n", previousChromo->fitness);
        }
        else
        {
            tempHead = leastFitnessChromo->nextChromo;
        }

        // printf("next of the least: %d\n", nextChromo->fitness);

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
        // printChromos(leastFitnessChromo, 1, 10);

        tempChromo = tempHead;
        leastFitnessChromo = tempHead;
        // printf("tempHead: %d");
        // printChromos(tempHead, 1, 10);
        // printf("\n");

        // printChromos(head, 7, 10);
        // printf("\n\n");
    }
    return tempBestHead;

    // while (tempChromo->nextChromo != NULL)
    // {
    //     if(tempChromo->fitness < leastFitnessChromo->fitness)
    //     {
    //         leastFitnessChromo = tempChromo;
    //     }
    //     tempChromo = tempChromo->nextChromo;
    // }
}

chromosome *findChromo(chromosome *head, int index)
{
    chromosome *temp = head;
    int count = 0;

    for (size_t i = 0; i < index-1; i++)
    {
        temp = temp->nextChromo;
    }

    return temp;

    // chromosome *temp = head;
    // int count = 0;

    // while (temp->nextChromo != NULL)
    // {
    //     if (count == index - 1)
    //     {
    //         return temp;
    //     }
    //     count++;
    //     temp = temp->nextChromo;
    // }
}

gene *findGene(chromosome *head, int index)
{
    gene *temp = head->headGene;
    int count = 0;

    for (size_t i = 0; i < index-1; i++)
    {
        temp = temp->nextGene;
    }

    return temp;
    

    // while (temp->nextGene != NULL)
    // {
    //     if (count == index - 1)
    //     {
    //         return temp;
    //     }
    //     count++;
    //     temp = temp->nextGene;
    // }
}

void xover(chromosome *firstChromo, chromosome *secondChromo, int start, int end)
{
    printf("\nXOVER START\n\n");
    printChromos(firstChromo, 1, 10);
    printChromos(secondChromo, 1, 10);
    printf("*********************\n");

    gene *firstStartGeneTemp = findGene(firstChromo, start);
    gene *secondStartGeneTemp = findGene(secondChromo, start);

    if (start == 1)
    {
        firstChromo->headGene = secondStartGeneTemp;
        secondChromo->headGene = firstStartGeneTemp;
    }
    else
    {
        findGene(firstChromo, start - 1)->nextGene = secondStartGeneTemp;
        findGene(secondChromo, start - 1)->nextGene = firstStartGeneTemp;
    }

    if (end != 10)
    {
        gene *firstEndGeneTemp = findGene(secondChromo, end + 1);
        gene *secondEndGeneTemp = findGene(firstChromo, end + 1);

        findGene(firstChromo, end)->nextGene = firstEndGeneTemp;
        findGene(secondChromo, end)->nextGene = secondEndGeneTemp;
    }

    printChromos(firstChromo, 1, 10);
    printChromos(secondChromo, 1, 10);
}

void mutation(chromosome *firstChromo, chromosome *secondChromo, int mutationGeneNumber)
{
    gene *firstChromoGene = findGene(firstChromo, mutationGeneNumber);
    gene *secondChromoGene = findGene(secondChromo, mutationGeneNumber);

    //complement of first chromo
    if(firstChromoGene->value == 0){
        firstChromoGene->value = 1;
    }
    else{
        firstChromoGene->value = 0;
    }

    //complement of first chromo
    if(secondChromoGene->value == 0){
        secondChromoGene->value = 1;
    }
    else{
        secondChromoGene->value = 0;
    }

    printf("\nAFTER MUTATION\n");
    printChromos(firstChromo, 1, 10);
    printChromos(secondChromo, 1, 10);
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

    chromosome *newChromo;
    gene *newGene;

    chromosome *headPtr = malloc(sizeof(chromosome));
    headPtr = &headChromo;
    chromosome *tailPtr = malloc(sizeof(chromosome));
    tailPtr = &headChromo;
    int chromoCount = 0;

    char populationChar = fgetc(populationFilePtr);
    while (populationChar != EOF)
    {
        if (populationChar == '\n')
        {
            newChromo = malloc(sizeof(chromosome));
            addChromo(newChromo, tailPtr);

            tailPtr->nextChromo = newChromo;

            tailPtr = tailPtr->nextChromo;
        }
        else if (populationChar != ':')
        {
            int value = atoi(&populationChar);
            newGene = malloc(sizeof(gene));
            addGene(newGene, tailPtr, value);
        }
        populationChar = fgetc(populationFilePtr);
    }
    fclose(populationFilePtr);

    int generationCount = 0;

    for (size_t i = 0; i < MAX_GEN+1; i++)
    {

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

        // SORTING

        headPtr = sortChromos(headPtr, POP_SIZE);
        printf("GENERATION: %d\n", (int)i);
        printChromos(headPtr, POP_SIZE, PROB_SIZE);
        printf("\n");
        printf("Best chromosome found so far: ");
        printChromos(bestFitness, 1, 10);
        printf("\n");

        // SELECTION

        char selectionChar = fgetc(selectionFilePtr);
        int firstIndex = -1;
        int secondIndex = -1;

        while (selectionChar != EOF)
        {
            if (selectionChar == ' ')
            {
                //next step = xover
                //xoverı yaz
                xover(findChromo(headPtr, firstIndex), findChromo(headPtr, secondIndex), 5, 10);
                mutation(findChromo(headPtr, firstIndex), findChromo(headPtr, secondIndex), 10);
                firstIndex = -1;
                secondIndex = -1;
            }
            else if (selectionChar != ':')
            {
                int index = atoi(&selectionChar);
                if (firstIndex == -1)
                {
                    firstIndex = index;
                }
                else if (secondIndex == -1)
                {
                    secondIndex = index;
                }
            }

            selectionChar = fgetc(selectionFilePtr);
        }
    }
    free(headPtr);
    free(tailPtr);
    free(newChromo);
    free(newChromo);
}