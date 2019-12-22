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
    newGene->nextGene = (gene *)NULL;
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

    for (size_t i = 0; i < POP_SIZE + 1; i++)
    {
        // printf("girdi\n");

        while (tempChromo->nextChromo != NULL)
        // for (size_t j = 0; i < POP_SIZE; j++)
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

    for (size_t i = 0; i < index - 1; i++)
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

    for (size_t i = 0; i < index - 1; i++)
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
    printf("xover numbers: %d %d\n", start, end);
    // printf("\nXOVER START\n\n");
    // printChromos(firstChromo, 1, 10);
    // printChromos(secondChromo, 1, 10);
    // printf("*********************\n");

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

    // printChromos(firstChromo, 1, 10);
    // printChromos(secondChromo, 1, 10);
}

void mutation(chromosome *firstChromo, chromosome *secondChromo, int mutationGeneNumber)
{
    printf("mutation number: %d\n", mutationGeneNumber);

    gene *firstChromoGene = findGene(firstChromo, mutationGeneNumber);
    gene *secondChromoGene = findGene(secondChromo, mutationGeneNumber);

    //complement of first chromo
    if (firstChromoGene->value == 0)
    {
        firstChromoGene->value = 1;
    }
    else
    {
        firstChromoGene->value = 0;
    }

    //complement of first chromo
    if (secondChromoGene->value == 0)
    {
        secondChromoGene->value = 1;
    }
    else
    {
        secondChromoGene->value = 0;
    }

    // printf("\nAFTER MUTATION\n");
    // printChromos(firstChromo, 1, 10);
    // printChromos(secondChromo, 1, 10);
}

chromosome *deepChromoCopy(chromosome *mainChromo)
{
    chromosome *temp = malloc(sizeof(chromosome));

    temp->fitness = mainChromo->fitness;
    temp->rank = mainChromo->rank;
    temp->headGene = mainChromo->headGene;

    gene *mainGeneTraverse = mainChromo->headGene;
    gene *tempGeneTraverse = temp->headGene;

    for (size_t i = 0; i < 10; i++)
    {
        tempGeneTraverse->nextGene = mainGeneTraverse->nextGene;

        mainGeneTraverse = mainGeneTraverse->nextGene;
        tempGeneTraverse = tempGeneTraverse->nextGene;
    }
    
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

    chromosome overallBestChromo;
    chromosome bestFitness;

    chromosome worstFitness;

    for (size_t i = 0; i < MAX_GEN + 1; i++)
    {

        // FITNESS CALCULATIONS

        chromosome *tempChromoFitness = headPtr;

        // while (tempChromoFitness->nextChromo != NULL)
        for (size_t i = 0; i < POP_SIZE; i++)
        {
            int fitness = calculateFitness(tempChromoFitness, PROB_SIZE);
            tempChromoFitness->fitness = fitness;

            if (i != 0)
            {
                if (fitness < bestFitness.fitness)
                {
                    bestFitness = *tempChromoFitness;
                }
                else if (fitness > worstFitness.fitness)
                {
                    worstFitness = *tempChromoFitness;
                }
            }
            else
            {
                bestFitness = *tempChromoFitness;
                worstFitness = *tempChromoFitness;
            }

            tempChromoFitness = tempChromoFitness->nextChromo;
        }

        // SETTING OVERALL BEST
        if (i == 0)
        {
            overallBestChromo = bestFitness;
        }
        else if (bestFitness.fitness < overallBestChromo.fitness)
        {
            overallBestChromo = bestFitness;
        }

        // RANK CALCULATIONS

        chromosome *tempChromoRank = headPtr;

        chromosome *bestRank;
        chromosome *worstRank;

        // while (tempChromoRank->nextChromo != NULL)
        for (size_t i = 0; i < POP_SIZE; i++)
        {
            double rank = calculateRank(tempChromoRank, &bestFitness, &worstFitness);
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

        //PRINTING
        printf("\nGENERATION: %d\n", (int)i);
        printChromos(headPtr, POP_SIZE, PROB_SIZE);
        printf("\n");
        printf("Best chromosome found so far: ");
        printChromos(&overallBestChromo, 1, 10);
        printf("\n");
        printf("Wors chromo: ");
        printChromos(&worstFitness, 1, 10);
        printf("\n");

        if (i == 10)
        {
            break;
        }

        //MUTATION GENE

        int mutationIndex = -1;

        char mutationStr[3];

        // fgets(mutationStr, 3, mutateFilePtr);
        fscanf(mutateFilePtr, "%d\n", &mutationIndex);

        // char mutationChar = fgetc(mutateFilePtr);

        // mutationIndex = atoi(&mutationChar);
        // mutationChar = fgetc(mutateFilePtr);

        //XOVER GENES

        int firstXoverIndex = -1;
        int secondXoverIndex = -1;

        char xoverBuffer[6];

        fgets(xoverBuffer, 6, xoverFilePtr);

        char *xoverIndexPtr = strtok(xoverBuffer, ":");
        firstXoverIndex = atoi(xoverIndexPtr);

        xoverIndexPtr = strtok(NULL, ":");
        secondXoverIndex = atoi(xoverIndexPtr);

        // char xoverChar = fgetc(xoverFilePtr);

        // fscanf(xoverFilePtr, "%d:%d\n", &firstXoverIndex, &secondXoverIndex);

        // while (xoverChar != '\n')
        // {
        //     if (xoverChar != ':')
        //     {
        //         int index = atoi(&xoverChar);
        //         if (firstXoverIndex == -1)
        //         {
        //             firstXoverIndex = index;
        //         }
        //         else if (secondXoverIndex == -1)
        //         {
        //             secondXoverIndex = index;
        //         }
        //     }
        //     xoverChar = fgetc(xoverFilePtr);
        // }

        // SELECTION

        char selectionChar = fgetc(selectionFilePtr);
        int firstSelectionIndex = -1;
        int secondSelectionIndex = -1;

        while (selectionChar != EOF)
        {
            if (selectionChar == ' ' || selectionChar == '\n')
            {
                //next step = xover
                //xoverı yaz
                printf("selection numbers: %d %d\n", firstSelectionIndex, secondSelectionIndex);
                xover(findChromo(headPtr, firstSelectionIndex), findChromo(headPtr, secondSelectionIndex), firstXoverIndex, secondXoverIndex);
                mutation(findChromo(headPtr, firstSelectionIndex), findChromo(headPtr, secondSelectionIndex), mutationIndex);
                firstSelectionIndex = -1;
                secondSelectionIndex = -1;
                if (selectionChar == '\n')
                {
                    break;
                }
            }
            else if (selectionChar != ':')
            {
                int index = atoi(&selectionChar);
                if (firstSelectionIndex == -1)
                {
                    firstSelectionIndex = index;
                }
                else if (secondSelectionIndex == -1)
                {
                    secondSelectionIndex = index;
                }
            }

            selectionChar = fgetc(selectionFilePtr);
        }

        firstXoverIndex = -1;
        secondXoverIndex = -1;
    }
    fclose(xoverFilePtr);
    fclose(mutateFilePtr);
    fclose(selectionFilePtr);
    // free(headPtr);
    free(tailPtr);
    free(newChromo);
    free(newChromo);
}