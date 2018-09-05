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
int Check_User_Search(int number);
void Search_Players(player* players, int num_players, int number);


int main (int argc, char* argv[])
{
  if (argc != 3)
  {
    printf("Incorrect Input\nCorrect input: ./a.out <num> <binaryinputfile>\n");
    exit(0);
  }

  int num = atoi(argv[1]);

  //player* players (address_holder) ------> return value of read_binary_file, which the return value is our (address)[A PLAYER, A PLAYER ,,,,,,]
	player* players = read_binary_file(argv[2], num);

  //printf("Read %d players from binary file\n", num);
  int key;

  while(1){
    printf("------Search players------\n");
    printf("\nWhat value would you like to search for?  (0-50) or -1 to exit: ");
    scanf("%d", &key);

    if(key == -1){
      free(players);
      exit(0);
    }

    while( Check_User_Search(key) == 0){
      printf("\nWhat value would you like to search for?  (0-50) or -1 to exit: ");
      scanf("%d", &key);

      if(key == -1){
        free(players);
        exit(0);
      }
    }

    Search_Players(players,num,key);
  }

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

    //players(address_holder) --------->(address)[A PLAYER , A PLAYER , A PLAYER ,,,,,,,,,,,,,,,,,]
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

int Check_User_Search(int number)
{
  if (number >= 0 && number <= 50)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void Search_Players(player* players, int num_players, int number)
{
  int i;
  int counter = 0;
  for (i = 0; i < num_players; i++)
  {
    if (players[i].singles == number)
    {
      printf("%s has %d singles!\n", players[i].Player_Name, players[i].singles);
      counter++;
    }
    if (players[i].doubles == number)
    {
      printf("%s has %d doubles!\n", players[i].Player_Name, players[i].doubles);
      counter++;
    }
    if (players[i].triples == number)
    {
      printf("%s has %d singles!\n", players[i].Player_Name, players[i].triples);
      counter++;
    }
    if (players[i].homeruns == number)
    {
      printf("%s has %d homeruns!\n", players[i].Player_Name, players[i].homeruns);
      counter++;
    }
  }
  printf("This search had a total of %d matching criteria\n", counter);
}
