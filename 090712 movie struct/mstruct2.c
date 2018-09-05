#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_MOVIES 20
#define MAX_LINE_LENGTH 500

typedef struct
{
	char *title;
	char *director;
	int year;
} Movie;

Movie* createMovie(char* title, char* director, int year);
void freeMovie(Movie *theMovie);

int main( int argc, char **argv )
{
	int i;
	int numMovies = 0;
	Movie *movies[MAX_NUM_MOVIES];
	Movie *aMovie;

	FILE *inFile = NULL;
	char line[MAX_LINE_LENGTH + 1];
	
	char *title, *director, *yearStr;
	int year;
	
	if(argc != 2)
	{
		printf("\nYou did not enter an input file.\n");
		return 1;
	}
	
	if((inFile = fopen(argv[1], "r")) == NULL)
	{
		printf("\nUnable to open file.\n");
		return 2;
	}
	
	while(fgets(line, MAX_LINE_LENGTH, inFile))
	{
		if (numMovies >= MAX_NUM_MOVIES)
		{
			printf("\nThere are more movies than I can process.\n");
			break;
		}
		
		title = strtok(line, ",");
		director = strtok(NULL, ",");
		yearStr = strtok(NULL, ",");
		year = atoi(yearStr);
		
		aMovie = createMovie(title, director, year);
		
		if (aMovie != NULL)
		{
			movies[numMovies] = aMovie;
			numMovies++;
		}
	}
	
	printf("\n%i movies have been processed.\n\n", numMovies);
	
	for (i = 0; i < numMovies; i++)
	{
		aMovie = movies[i];
		printf("Title: %s\nDirector: %s\nYear: %d\n\n", aMovie->title, aMovie->director, aMovie->year);
	}
	
	for (i = 0; i < numMovies; i++)
	{
		aMovie = movies[i];
		freeMovie(aMovie);
	}
	
	return 0;
}

void freeMovie(Movie *theMovie)
{
	if (!theMovie) return;

	if (theMovie->title) free(theMovie->title);
	if (theMovie->director) free(theMovie->director);
	
	free(theMovie);
}

Movie* createMovie(char* title, char* director, int year)
{
	Movie *theMovie;
	int len;
	
	if (!title || !director) return NULL;

	theMovie = malloc(sizeof(Movie));
	if (!theMovie)
	{
		printf("Unable to allocate memory for a Movie.\n");
		return NULL;
	}
	
	len = strlen(title);
	theMovie->title = malloc(len + 1);
	if (!theMovie->title)
	{
		free(theMovie);
		return NULL;
	}
	strncpy(theMovie->title, title, len);
	theMovie->title[len] = '\0';

	len = strlen(director);
	theMovie->director = malloc(len + 1);
	if (!theMovie->director)
	{
		free(theMovie);
		return NULL;
	}
	strncpy(theMovie->director, director, len);
	theMovie->director[len] = '\0';
	
	theMovie->year = year;
	
	return theMovie;
}
