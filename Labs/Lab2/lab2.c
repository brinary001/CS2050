#include <stdio.h>
#include <stdlib.h>

double* read_file(FILE* file, int length);
void write_to_file(FILE* file, double* value);
void sort_ascending(double* array, int length);
void sort_descending(double* array, int length);

int main (int argc, char* argv[])
{
	if (argc != 5)
	{
		printf("\nIncorrect Usage\n");
    printf("Correct input: ./a.out <length> <input file one> <input file two> <output file>");
		return -1;
	}
  /*int length = atoi(argv[1]);
  char* inputfile1 = argv[2];
  char* inputfile2 = argv[3];
  char* outputfile = argv[4];
  FILE* fp1 = fopen(inputfile1, "r");
  FILE* fp2 = fopen(inputfile2, "r");
  FILE* fp3 = fopen(outputfile, "w");
  double* numbers1 = read_file(fp1, length);
  double* numbers2 = read_file(fp2, length);
  write_to_file(outputfile, numbers1);
  write_to_file(outputfile, numbers2);

  close(0);
  close(1);
  close(2);

  fclose(inputfile1);
  fclose(inputfile2);*/

  return 0;
}

double* read_file(FILE* file, int length)
{
  if (file == NULL || length < 1)
  {
    printf("Error reading file");
    exit(0);
  }
  double* array = malloc(sizeof(double) * length);
  if (array == NULL)
  {
    printf("Error reading file\n");
    exit(0);
  }

  int i = 0;
  while (i < length)
  {
    fscanf(file, "%lf", (array+i));
    i++;
  }

  return array;
  free(array);

}

void write_to_file(FILE* file, double* value)
{
  fprintf(file, "%lf", *(value));
}

void sort_ascending(double* array, int length)
{
  int i = 0;
  int j = 0;
  int hold;
  for (i = 0; i < length; ++i)
  {
    for (j = i+1; j < length; ++j)
    {
      if ((array+i) > (array+j))
      {
        hold = *(array+i);
        *(array+i) = *(array+j);
        *(array+j) = hold;
      }
    }
  }
}

void sort_descending(double* array, int length)
{
  int hold;
  int i = 0;
  int j = 0;
  for (i = 0; i < length; ++i)
  {
    for (j = i+1; j < length; ++j)
    {
      if ((array+i) < (array+j))
      {
        hold = *(array+i);
        *(array+i) = *(array+j);
        *(array+j) = hold;
      }
    }
  }
}
