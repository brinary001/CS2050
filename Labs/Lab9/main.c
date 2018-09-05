//
//  main.c
//  lab9
//
//  Created by Brian Robinson on 4/6/17.
//  Copyright © 2017 Brian Robinson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct Node {

	int num;
	int count;
	struct Node* left;
	struct Node* right;

} node;

node* add_to_tree(node* head, int number);
void print_totals(node* head);
void free_tree(node* head);

int main(int argc, char* argv[])
{
	node* head = NULL;

	if (argc != 4)
	{
		printf("command line no good");
	}

	FILE* fp = fopen(argv[1], "w+");

	if (fp == NULL)
	{
		printf("no file");
	}

	int i = 0;

	for (i = 0; i < atoi(argv[2]); i++)
	{
		fprintf(fp, "%d\n", rand() % atoi(argv[3]) + 1);
	}

	fclose(fp);
	int num;
	fp = fopen(argv[1], "r");

		for (i = 0; i < atoi(argv[2]); i++){
			fscanf(fp, "%d",&num);
			head = add_to_tree(head,num);
		}   


		int total = atoi(argv[2]);

		while(1)
		{
			printf("Enter '1' to add a number to the tree\n");
			printf("Enter '2' to print the totals for each number\n");
			printf("Enter '-1' to terminate\n");
			printf("Enter your choice: \n");

			int selection;
			int x;
			scanf("%d", &selection);

			if (selection == -1)
			{
				free_tree(head);
				fclose(fp);
				exit(0);
				break;
			}

			if (selection == 1)
			{
				printf("Enter a number (1-10) to add to the tree\n");
				scanf("%d", &x);
				if(x >= 1 && x<= 10)
				{
					head = add_to_tree(head, x);
				}

				total += 1;

			}

			else if (selection == 2)
			{
				print_totals(head);
				printf("Total: %d\n",total);
			}

		}

		free_tree(head);

		return 0;
	}

	node* add_to_tree(node* head, int number)
	{
		if (head == NULL)
		{
			head = malloc(sizeof(node));
			head->num = number;
			head->left = NULL;
			head->right = NULL;

			head->count = 1;
			return head;
		}

		if (head->num == number)
		{
			head->count++;
			return head;
		}

		else if (number < head->num)//left
		{
			head->left = add_to_tree(head->left , number);
		}

		else if (number > head->num)//right
		{
			head->right = add_to_tree(head->right, number);
		}

		return head;
	}

	void print_totals(node* head)
	{
		if (head == NULL)
		{
			return;
		}

		print_totals(head->left);
		printf("There are %d occurances of the number %d\n", head->count, head->num);
		print_totals(head->right);
	}

	void free_tree(node* head)
	{
		if (head == NULL)
		{
			return;
		}

		free_tree(head->left);
		free_tree(head->right);

		free(head);
	}
