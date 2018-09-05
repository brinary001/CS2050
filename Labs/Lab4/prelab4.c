#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Player {
	   char Player_Name[50];
	   int singles;
	   int doubles;
	   int triples;
     int homeruns;
  }player;

player* read_binary_file(char* input_file, int num_players);
void selection_sort(player* array, int size);
void print_Array(player* array, int size);


int main (int argc, char* argv[])
{
  if (argc != 3)
  {
    printf("Incorrect Input\nCorrect input: ./a.out <num> <binaryinputfile>\n");
    exit(0);
  }

  int num = atoi(argv[1]);

	player* players = read_binary_file(argv[2], num);

  return 0;
}

player* read_binary_file(char* input_file, int num_players)
{

	FILE* fp = fopen(input_file, "rb");
	if (fp == NULL)
		{
			printf("Error reading file");
			exit(0);
		}

		player* players = malloc(sizeof(player)*num_players);
		if (players == NULL)
		{
			fclose(fp);
			exit(0);
		}

	      fread(players, sizeof(player), num_players, fp);
	  		fclose(fp);
				return players;
}

void selection_sort(player* array, int size)
{
  int lh, rh, i;

  player* playaBest = array;      //address of player with best homeruns
  player* playaHowSmall = array;  //current location your searching for i.e. smallest, second smallest, etc.
  player* playaCurrent = array;   //used for travelling through loop to make comparisons
  player* temp = NULL;            //temp used for swappage

  for (i = 0; i < size; i++) //Player selector loop
  {
    playaHowSmall = playaHowSmall + i; //location in array
    playaCurrent = playaHowSmall; //initialization
    temp = 0; //value of homeruns


      for(j=0; j < (size - i) ; j++) //Comparison loop-compares HR values
      {
          ;  //sets the current location being compared
          if ((playaCurrent->homeruns) < (playaBest)->homeruns )
          playaBest = playaCurrent;     //sets a reference to address with best homeruns

          currentPlaya++;
      }
        //swappage
        temp = playaHowSmall;
        playaHowSmall = playaBest;
        playaBest = temp;

    }
  }
}

void print_Array(player* array, int size)
{

}
