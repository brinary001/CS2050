#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int* readfile(char* filename, int size);
void bubble_sort(int* array, int size);
void selection_sort(int* array, int size);
void insertion_sort(int* array, int size);

int main (int argc, char** argv)
{
	if (argc != 3)
	{
		printf("Command line arguments: ./a.out <length> <input file>\nPROGRAM EXITING");
		exit(0);
	}
	int size = atoi(argv[1]);
	int* arrPtr = malloc(sizeof(int) * size);
	int choice;
	
	do {
		printf("Enter '1' for a bubble sort\nEnter '2' for a selection sort\nEnter '3' for an insertion sort");
		printf("\nEnter -1 to exit\n");
		printf("Choice: ");
		scanf("%d", &choice);

		switch (choice)
		{
			case 1:
				bubble_sort(arrPtr, size);
			
			case 2:
				//selection_sort(arrPtr, size);
				break;
			case 3:
				//insertion_sort(arrPtr, size);
				break;
			default:
				break;
		}
	}
	while (choice != -1);
	
	return 0;
}
int* readfile(char* filename, int size)
{
	FILE* fp = fopen(filename, "r");

	int* arrPtr = malloc(sizeof(int) * size);
	
	if (fp == NULL || size < 1)
	{
		printf("Error reading file");
		exit(0);
	}
	int i;
	for (i = 0; i < size; i++)
	{
		if (i < size)
		{
			fscanf(fp, "%d", arrPtr);
		}
		else
		{
			break;
		}
	}
	fclose(fp);
	return arrPtr;
}	
void bubble_sort(int* array, int size)
{
    int i, j, hold;
    
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (*(array+i) > *(array+j))
            {
                hold = *(array+i);
                *(array+i) = *(array+j);
                *(array+j) = hold;
                
            }
        }
    }
}

/*void selection_sort(int* array, int size)
{
	
}
void insertion_sort(int* array, int size)
{
	
}*/

