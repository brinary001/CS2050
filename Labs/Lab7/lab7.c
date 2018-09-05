#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX 15

typedef struct node {
	char* word;
	struct node* next;
} Node;

Node* add_to_front(char* word, Node* head);
void print(Node* head);
void menu();
Node* remove_from_front(Node* head, char* word);
Node* remove_from_back(Node* head);
Node* add_to_back(Node* head, char* word);

int main(void)
{
    Node* head = NULL;
    //Node* temp = NULL;
    //Node* undo = NULL;

	int option = 0;
    
    char* word = malloc(sizeof(MAX));
    
    while (option != 4)
    {
        menu();
        scanf("%d", &option);
        while (option < 1 || option > 4)
        {
            menu();
            scanf("%d", &option);
        }
    
        switch (option)
        {
            case 1:
                printf("Enter a word to add to the document: \n");
                scanf("%s", word);
                head = add_to_back(head, word);
                print(head);
                break;
                
            case 2:
                //temp = remove_from_back(head);
                //undo = add_to_back(head, temp->word);
                print(head);
                break;
                
            case 4:
                
                break;
        }
    }
	return 0;
}

/*Node* add_to_front(char* word, Node* head)
{

	return NULL;
}
*/
void print(Node* head)
{

	while(head != NULL)
    {
		printf("%s ", head->word);
		head = head->next;
	}	

	return;
}

void menu()
{

	printf("Enter 1.) to add a word to the sentance\n");
	printf("Enter 2.) to undo\n");
	printf("Enter 3.) to redo\n");
	printf("Enter 4.) to exit\n");
}

/*Node* remove_from_front(Node* head, char* word)
{

	return NULL;
}
*/
Node* remove_from_back(Node* head)
{
    if (head == NULL)
    {
        printf("Attempting to delete a node from an empty list\n");
        exit(0);
    }
    
    if (head->next == NULL)
    {
        head = NULL;
        return head;
    }
    
    Node* current = head;
    Node* previous = NULL;
    
    while (current->next != NULL)
    {
        previous = current;
        current = current->next;
    }
    
    if (previous != NULL)
    {
        previous->next = NULL;
    }
    
    return current;
}

Node* add_to_back(Node* head, char* word)
{
    if (head == NULL)
    {
        head = malloc(sizeof(Node));
        head->word = malloc(MAX);
        strcpy(head->word, word);
        head->next = NULL;
    }
    
    else
    {
       Node* current = head;
       while (current->next != NULL)
       {
           current = current->next;
       }
        current->next = malloc(sizeof(Node));
        current = current->next;
        current->word = malloc(MAX);
        strcpy(current->word, word);
        current->next = NULL;
    }
    
	return head;
}
