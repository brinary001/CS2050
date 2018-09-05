#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE 25

typedef struct numbers{
    int* array;
    int* sortedAscending;
    int* sortedDescending;
    
} Numbers;

Numbers* readBinaryFile(FILE* fp);
void display_menu();
void sortAscending(int* array);
void sortDescending(int* array);
void freeArrays(Numbers* numbers);
void printArray(int* array);


int main (int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Command line arguments: ./a.out <input file>\nPROGRAM EXITING");
        exit(0);
    }
    FILE* fp = fopen(argv[1], "rb");
    Numbers* num = readBinaryFile(fp);
    int choice;
    do {
    display_menu();
    scanf("%d", &choice);
    
        switch (choice)
        {
            case 1:
                printArray(num->array);
                printf("-- Printing unsorted array --\n");
                break;
            case 2:
                printf("-- Printing ascending array --\n");
                printArray(num->sortedAscending);
                break;
            case 3:
                printf("-- Printing descending array --\n");
                printArray(num->sortedDescending);
                break;
            case 4:
                printf("-- Exiting and freeing all memory --\n");
                freeArrays(num);
                fclose(fp);
                exit(0);
            default:
                break;
        }
    }
    while (choice != 4);
    fclose(fp);
    return 0;
}

void display_menu()
{
    printf("1.) Print array\n2.) Print ascending array\n3.) Print descending array\n4.) exit\n");
    printf("Select an option:\n");
}

Numbers* readBinaryFile(FILE* fp)
{
    if (fp == NULL || SIZE < 1)
    {
        printf("Error reading file");
        exit(0);
    }


    Numbers* num = malloc(sizeof(Numbers));
    num->array = malloc(sizeof(int) * SIZE);
    num->sortedAscending = malloc(sizeof(int) * SIZE);
    num->sortedDescending = malloc(sizeof(int) * SIZE);
    fread(num->array, sizeof(int), SIZE, fp);
    fclose(fp);
    int i = 0;
				for (i = 0; i < SIZE; i++)
                {
                    num->sortedAscending[i] = num->array[i];
                    num->sortedDescending[i] = num->array[i];
                }
				sortAscending(num->sortedAscending);
				sortDescending(num->sortedDescending);
    
    return num;
    
}
void sortAscending(int* array)
{
        int valueToInsert;
        int holePosition;
        int i;
        
        // loop through all numbers
        for(i = 1; i < SIZE; i++)
        {
            
            // select a value to be inserted.
            valueToInsert = array[i];
            
            // select the hole position where number is to be inserted
            holePosition = i;
            
            // check if previous no. is larger than value to be inserted
            while (holePosition > 0 && array[holePosition-1] > valueToInsert)
            {
                array[holePosition] = array[holePosition-1];
                holePosition--;
            }
            
            if(holePosition != i)
            {
                // insert the number at hole position 
                array[holePosition] = valueToInsert;
            }
        }
}
void sortDescending(int* array)
{
    int valueToInsert;
    int holePosition;
    int i;
    
    // loop through all numbers
    for(i = 1; i < SIZE; i++)
    {
        
        // select a value to be inserted.
        valueToInsert = array[i];
        
        // select the hole position where number is to be inserted
        holePosition = i;
        
        // check if previous no. is larger than value to be inserted
        while (holePosition > 0 && array[holePosition-1] < valueToInsert)
        {
            array[holePosition] = array[holePosition-1];
            holePosition--;
        }
        
        if(holePosition != i)
        {
            // insert the number at hole position
            array[holePosition] = valueToInsert;
        }
    }
}
void printArray(int* array)
{
    int i;
    for (i = 0; i < SIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
void freeArrays(Numbers* num)
{
				free(num->array);
				free(num->sortedAscending);
				free(num->sortedDescending);
                free(num);
}
