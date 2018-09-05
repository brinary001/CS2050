#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct player {

	char Fname[25];
	char Lname[25];
	int Singles;
	int Doubles;
	int Triples;
	int Homeruns;
	int At_Bats;
	float Slugging_Percentage;

} Player;

void read_from_file (char* filename, Player* players, int index, int size);
void calculate_slugging (Player* players, int size);
void sort_array (Player* players, int size);
void write_to_file (char* filename, Player* players, int size);

int main (int argc, char* argv[])
{
  if (argc != 6)
  {
    printf("Incorrect usage\nCorrect usage: <./a.out> <Total number of players> <input1> <input2> <input3> <output>\n");
    printf("......exiting......");
    exit(0);
  }
  int num_players = atoi(argv[1]);
  if (num_players < 1)
  {
    return -1;
  }
  Player* players = malloc(sizeof(Player) * num_players);
  int index = 0;
  if (players == NULL)
  {
    printf("Something went wrong here in main (line 40)\n");
    return -1;
  }
  read_from_file(argv[2], players, index, num_players);
  read_from_file(argv[3], players, index+10, num_players);
  read_from_file(argv[4], players, index+20, num_players);
  calculate_slugging(players, num_players);
  sort_array(players, num_players);
  write_to_file(argv[5], players, num_players);
  free(players);
  return 0;
}

void read_from_file(char* filename, Player* players, int index, int size)
{
  FILE* fp = fopen(filename, "r");
  if (fp == NULL || size < 1)
  {
    printf("Error reading file");
    exit(0);
  }
  int i;
  for (i = index; i < index+10; i++)
  {
    if (i < size)
    {
      fscanf(fp, "%s %s %d %d %d %d %d", (players+i)->Fname, (players+i)->Lname, &(players+i)->Singles, &(players+i)->Doubles, &(players+i)->Triples,
      &(players+i)->Homeruns, &(players+i)->At_Bats);
    }
    else
    {
      break;
    }
  }
  fclose(fp);
}
void calculate_slugging(Player* players, int size)
{
  int i;
  for (i = 0; i < size; i++)
  {
    float total = (players+i)->Singles + ((players+i)->Doubles * 2) + ((players+i)->Triples * 3) + ((players+i)->Homeruns * 4);

    float average = total / (players+i)->At_Bats;

    (players+i)->Slugging_Percentage = average;
  }

}
void sort_array(Player* players, int size)
{
  int i, j;
  Player hold;

  for (i = 0; i < size; ++i)
  {
    for (j = i+1; j < size; ++j)
    {
      if ((players+i)->Slugging_Percentage > (players+j)->Slugging_Percentage)
      {
        hold = *(players+i);
        *(players+i) = *(players+j);
        *(players+j) = hold;
      }
    }
  }
}
void write_to_file(char* filename, Player* players, int size)
{
  FILE* fp = fopen(filename, "w");
  if (fp == NULL || size < 1)
  {
    printf("Error opening file");
    exit(0);
  }
  int i;
  for (i = 0; i < 30; i++)
  {
    if (i < size)
    {
      fprintf(fp, "%s %s %d %d %d %d %d %.3f\n", (players+i)->Fname, (players+i)->Lname, (players+i)->Singles, (players+i)->Doubles, (players+i)->Triples,
      (players+i)->Homeruns, (players+i)->At_Bats, (players+i)->Slugging_Percentage);
    }
    else
    {
      break;
    }
  }
  fclose(fp);
}
