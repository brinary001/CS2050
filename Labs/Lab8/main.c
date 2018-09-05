//
//  main.c
//  lab8
//
//  Created by Brian Robinson on 3/23/17.
//  Copyright © 2017 Brian Robinson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ROLL 6

typedef struct Node {
    int spaceID;
    int backValue;
    struct Node* next;
    struct Node* prev;
    
}node;


node* add_node(node* head, int spaceID, int backValue);
void play_game(node* head);
node* player_turn(node* user);
void free_list(node* head);
void link_back_to_front(node* head);
void print_board(node* head);

int main(int argc, char** argv)
{
    srand(time(NULL));
    
    if (argc != 2)
    {
        printf("Incorrect usage");
    }
    
    node* head = NULL;
    
    char* input1 = argv[1];
    //char* input2 = argv[2];
    
    FILE* fp = fopen(input1, "r");
    
    int id;
    int bv;
    
    while (fscanf(fp, "%d %d", &id, &bv) != EOF)
    {
        head = add_node(head, id, bv);
    }
    
    print_board(head);
    link_back_to_front(head);
    print_board(head);
    
    
    return 0;
}

node* add_node(node* head, int spaceID, int backValue)
{
    node* previous = NULL;
    node* current = NULL;
    
    if (head == NULL)
    {
        head = malloc(sizeof(node));
        head->spaceID = spaceID;
        head->backValue = backValue;
        head->prev = NULL;
        head->next = NULL;
    }
    else
    {
        while (current->next)
        {
            previous = current;
            current = current->next;
        }
        previous = current;
        current = current->next;
        head = malloc(sizeof(node));
        head->spaceID = spaceID;
        head->backValue = backValue;
        head->prev = previous;
        head->next = NULL;
        
    }
    return NULL;
}

void link_back_to_front(node* head)
{
    node* current = head;

    while (current->next)
    {
	current = current->next;
    }
    
    current->next = head;
    head->prev = current;
}

void print_board(node* head)
{
    if (head == NULL)
    {
        printf("head was null\n");
        return;
    }
    
    node* current = head;
    
    while (current != NULL)
    {
        printf("'%d'---'%d'->", current->spaceID, current->backValue);
        current = current->next;
    }
}

void play_game(node* head)
{
    node* player1 = head;
    //node* player2 = head;
    
    while (1)
    {
        player1 = player_turn(player1);
    }
    return;
}

node* player_turn(node* user)
{

    int dice_roll = rand() % MAX_ROLL + 1;
    int i;

	for (i = 0; i < dice_roll; i++)
	{
		user = user->next;
		if (user->spaceID == 0)
	{
		return user;
	}
	
	int backspace = user->backValue;
	
	if (backspace < 0)
	{
		for (i = 0; i > dice_roll; i--)
		{
			user = user->prev;
		}
	}

	else
	{
		for (i = 0; i < dice_roll; i++);
		{
			user = user->next;
			if (backspace == 0)
			{
				return user;
			}
		}
	}
	}

	return user;
}
void free_list(node* head) 
{
    if (head != NULL)
    return;
}

