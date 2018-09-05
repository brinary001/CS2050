#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 400
#define MAX_TITLE_LENGTH 40
#define MAX_NAME_LENGTH 40
#define MAX_NUM_MOVIES 20

typedef struct
{
	char title[MAX_TITLE_LENGTH + 1];
	char director[MAX_NAME_LENGTH + 1];
	int year;
} Movie;

Movie* createMovie(char* title, char* director, int year);

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
		free(aMovie);
	}
	
	return 0;
}

Movie* createMovie(char* title, char* director, int year)
{
	Movie *theMovie;
	int len;

	theMovie = malloc(sizeof(Movie));
	if (!theMovie)
	{
		printf("Unable to allocate memory for a Movie.\n");
		return NULL;
	}
	
	if (title)
	{
		len = strlen(title);
		if (len > MAX_TITLE_LENGTH) len = MAX_TITLE_LENGTH;
		strncpy(theMovie->title, title, len);
        theMovie->title[len] = '\0';
	} 
	else 
	{
		free(theMovie);
		return NULL;
	}
	
	if (director)
	{
		len = strlen(director);
		if (len > MAX_NAME_LENGTH) len = MAX_NAME_LENGTH;
		strncpy(theMovie->director, director, len);
        theMovie->director[len] = '\0';
	} 
	else
	{
		free(theMovie);
		return NULL;
	}
	
	theMovie->year = year;
	
	return theMovie;
}
