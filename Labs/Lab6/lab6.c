#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct Node{
    int number;
    struct Node* next;
}node;

node *add_node(node *head, int *number);
node* delete_node(node *head);
int sum_list(node* head);
void free_list(node *head);
void printList(node* head);
node* bouns_sort(node *head, int *number);

int main (void)
{
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    //initialize to NULL, since we have an empty list
    
    node *head = NULL;
    int i = 0;
    //add 10 nodes to list(the first add_nodes should create it)

    for (i = 0; i < 10; i++)
    {
        head = add_node(head, (array+i));
    }
    
    //print sum
    printf("\nThe sum of the list is %d", sum_list(head));
    
    //loop, delete each node, tries to delete 10 nodes, but the last print should print -1 since there should be no nodes left.
    for (i = 0; i < 10; i++)
    {
        head = delete_node(head);
        printf("\nThe sum of the list is %d", sum_list(head));
    }
    free_list(head);
    head = NULL;
    
    printf("\nThe sum of the list is %d", sum_list(head));
    
    return 0;
}

node* add_node(node *head, int* number)
{
    if (number == NULL)
    {
        printf("The number was null!\n");
        exit(0);
    }
    node* current = head;
    
    if (head == NULL)
    {
        head = malloc(sizeof(node));
        current = head;
    }
    else
    {
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = malloc(sizeof(node));
        current = current->next;
    }
    current->number = *number;
    printList(head);
    return head;
}

node* delete_node(node *head)
{
    if (head == NULL)
    {
        printf("Attempting to delete a node from an empty list\n");
        return NULL;
    }
    
    if (head->next == NULL)
    {
        free(head);
        head = NULL;
        return head;
    }
    
    node* current = head;
    node* previous = NULL;
    
    while (current->next != NULL)
    {
        previous = current;
        current = current->next;
    }
    
    if (previous != NULL)
    {
        previous->next = NULL;
    }
    
    free(current);
    
    return head;
}

int sum_list(node* head)
{
    if (head == NULL)
    {
        return -1;
    }
    node* current = head;
    int total = 0;
    while (current->next != NULL)
    {
        total += current->number;
        current = current->next;
    }
    total += current->number;
    return total;
}

void free_list(node *head)
{
    if (head != NULL)
    {
        while (head != NULL)
        {
            head = delete_node(head);
        }
    }
}

void printList(node* head)
{
    if (head == NULL)
    {
        printf("The head was NULL inside of print list function\n");
        return;
    }
    node* current = head;
    
    while (current != NULL)
    {
        printf("%d->", current->number);
        current = current->next;
    }
    
    printf("NULL\n");
}
