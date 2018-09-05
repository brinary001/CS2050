#include <stdio.h>
#include <stdlib.h>

typedef struct Player {
	char Player_Name[50];
	int Homeruns;
	int triples;
	int doubles;

} player;

player* read_binary_file(char* input_file);

int main (int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Incorrect Input\nCorrect input: ./a.out <binaryinputfile>\n");
		exit(0);
	}

	player* playa = NULL;

	playa = read_binary_file(argv[1]);

	printf("%s %d %d %d", playa->Player_Name, playa->Homeruns, playa->triples, playa->doubles);

	return 0;
}

player* read_binary_file(char* input_file)
{

	FILE* fp = fopen(input_file, "rb");
	if (fp == NULL)
	{
		printf("Error reading file");
		exit(0);
	}


	player* players = malloc(sizeof(player));
			if (players == NULL)
			{
			fclose(fp);
			exit(0);
			}


			fread(players, sizeof(player), 1, fp);

			fclose(fp);

			return players;
}
