#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#define MAXLINELENGTH 200
#define MAXCARPRICE 1000000

typedef struct node {

	char make[25];
	char model[25];
	int price;
	int year;
	char color[25];
	char type[25];
	int mileage;

	struct node* left;
	struct node* right;
} Node;

Node* get_cars(char* filename);
Node* add_to_tree(Node* head, Node* new);
void search_tree(Node* head, int year, int price, int* count);
void print_menu();
void free_tree(Node* head);

int main(int argc, char** argv)
{

	if (argc != 2 )
	{
		printf("Bruh...Correct input: ./a.out <input file>\n");
		return -2;
	}

	Node* head = NULL;

	head = get_cars(argv[1]);

	//char* color = malloc(sizeof(char) * 25);

	int count = 0;
	int price = 0;
	int year = 0;
	int choice = 0;

	do {
		do
		{
			print_menu();
			printf("Enter your choice: \n");
			scanf("%d", &choice);
			if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != -1)
			{
				printf("That's wrong yo.  Maybe try again?\n");
			}
		}while (choice < -1 || choice > 3);

		while (choice != -1)
		{
			print_menu();
			while (choice < -1 || choice > 4)
			{
				printf("That's wrong yo.  Maybe try again?\n");
				print_menu();
				scanf("%d\n", &choice);
			}

			switch (choice)
			{
				case 1:
					printf("Enter the year you would like the vehicles to be newer than:\n");
					scanf("%d", &year);
					while (year < 0)
					{
						printf("Please enter a year greater than 0: ");
						scanf("%d", &year);
					}
					price = MAXCARPRICE;
					break;

				case 2:
					printf("Enter the price you would like the vehicles to be less than: ");
					scanf("%d", &price);
					while (price < 0 || price > MAXCARPRICE)
					{
						printf("Please enter a price greater than 0 and less than 1 million: ");
						scanf("%d", &price);
					}
					year = 0;
					break;

				case 3:
					printf("Enter the year you would like the vehicles to be newer than: ");
					scanf("%d", &year);
					while (year < 0)
					{
						printf("Enter the price you would like the vehicles to be less than: ");
						scanf("%d", &price);
						while (price < 0 || price > MAXCARPRICE)
						{
							printf("Please enter a price greater than 0 and less than 1 million: ");
							scanf("%d", &price);
						}
						break;
					}
				case -1:
					free_tree(head);
					exit(0);
					//break;
			}

			if (choice != -1)
			{
				search_tree(head, year, price, &count);
				printf("%d cars found.\n", count);
				count = 0;
			}
		}

	}while (choice != -1);

	free_tree(head);
	return 0;
}

Node* get_cars(char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Unable to open %s\n", filename);
		return NULL;
	}

	Node* head = NULL;

	char line[MAXLINELENGTH];
	FILE* EcheckFP;
	char makes[25];
	char* token = NULL;;

	bool make = false;
	bool color = false;
	bool type = false;


	Node* new = NULL;
	while (fgets(line, MAXLINELENGTH, fp) != NULL)
	{
		new = malloc(sizeof(Node));
		token = strtok(line, "|");
		while (token != NULL)
		{
			//check make
			if (strcmp("make", token) == 0)
			{
				token = strtok(NULL, "|");

				EcheckFP = NULL;
				EcheckFP = fopen("makes.txt", "r");
				if (EcheckFP == NULL)
				{
					printf("Unable to open makes file\n");
					return NULL;
				}

				while (fscanf(EcheckFP, "%s", makes) != EOF)
				{
					if (strcmp(token, makes) == 0)
					{
						make = true;
						strcpy(new->make, token);
						break;
					}
				}
				fclose(EcheckFP);
			}//end make check

			//check model
			if (strcmp("model", token) == 0)
			{
				token = strtok(NULL, "|");
				strcpy(new->model, token);
			}//end model check

			//check cost
			if (strcmp("price", token) == 0)
			{
				token = strtok(NULL, "|");
				if (atoi(token) > 0)
				{
					new->price = atoi(token);
				}
			}//end price check

			//check type
			if (strcmp("type", token) == 0)
			{
				token = strtok(NULL, "|");

				EcheckFP = NULL;
				EcheckFP = fopen("types.txt", "r");
				if (EcheckFP == NULL)
				{
					printf("Unable to open type file\n");
					return NULL;
				}
				while (fscanf(EcheckFP, "%s", makes) != EOF)
				{
					if (strcmp(token, makes) == 0)
					{
						type = true;
						strcpy(new->type, token);
						break;
					}
				}
				fclose(EcheckFP);
			}//end type check

			//check color
			if (strcmp("color", token) == 0)
			{
				token = strtok(NULL, "|");

				EcheckFP = NULL;
				EcheckFP = fopen("colors.txt", "r");
				if (EcheckFP == NULL)
				{
					printf("Unable to open type file\n");
					return NULL;
				}
				while (fscanf(EcheckFP, "%s", makes) != EOF)
				{
					if (strcmp(token, makes) == 0)
					{
						color = true;
						strcpy(new->color, token);
						break;
					}
				}
				fclose(EcheckFP);
			}//end color check

			//check year
			if (strcmp("year", token) == 0)
			{
				token = strtok(NULL, "|");
				new->year = atoi(token);
			}//end year check

			//check mileage
			if (strcmp("mileage", token) == 0)
			{
				token = strtok(NULL, "|");
				if (atoi(token) > 0)
				{
					new->mileage = atoi(token);
				}
			}//end mileage check

			token = strtok(NULL, "|");
		}//End inner while loop

		//outside of second while loop
		if (make == true && type == true && color == true)
		{
			//printf("Made it\n");
			head = add_to_tree(head, new);
		}
		else
		{
			//printf("Didnt make it\n");
			free(new);
		}
	}//End outer while loop

	fclose(fp);
	return head;

}

Node* add_to_tree(Node* head, Node* new)
{
	if (head == NULL)
	{
		return new;
	}
	else
	{
		if (new->price <= head->price) /* Lower goes to left */
			head->left = add_to_tree( head->left , new);
		else /* Higher goes to right */
			head->right = add_to_tree(head-> right , new);
	}
	return head;
}

void search_tree(Node* head, int year, int price, int* count)
{
	//head = malloc(sizeof(Node));

	if (head != NULL)
	{
		search_tree(head->left, year, price, count);
		if (head->price < price && head->year > year)
		{
			printf("%d %s %s %s with %d miles that costs $%d\n", head->year, head->color, head->make, head->model, head->mileage, head->price);
			*count += 1;
		}

		search_tree(head->right, year, price, count);
	}
}

void print_menu()
{
	printf("To search for a vehicle newer than a specific year enter '1'\nTo search for a vehicle that costs less than a certain price enter '2'\nTo search for a vehilce with both of the above parameters enter '3'\nTo exit enter '-1'\n");
}

void free_tree(Node* head)
{
	if (head != NULL)
	{
		free_tree(head->left);
		free_tree(head->right);
		free(head);
	}
}
