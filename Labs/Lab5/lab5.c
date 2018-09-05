#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

typedef struct info {
    long int phone;
    char* email;
}Info;

typedef struct person {
    char* firstName;
    char* lastName;
    Info contact;
}Person;

#define MAX_NAME_LENGTH 25
#define BOOK_SIZE 5

int check_email(char* email);
int check_phone(long int phone);
Person* allocate_memory();
void add_contacts(Person* list);
void free_list(Person* list);
void print_list(Person* list);

int main (void)
{
    Person* list = allocate_memory();
    
    add_contacts(list);
    
    print_list(list);
    
    free_list(list);
    
    return 0;
}

int check_email(char* email)
{
    int i;
    int len = strlen(email);
    
    for (i = 0; i < len; i++)
    {
        if (*(email+i) == '@')
            {
                return 1;
            }
    }
    return 0;
}
int check_phone(long int phone)
{
    int size = ((int)log10(phone) + 1);
    int check = (size)/1000000000;
    if (size != 10 || check == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
Person* allocate_memory()
{
    Person* list = malloc(sizeof(Person) * BOOK_SIZE);
    
    int i = 0;
    
    for (i = 0; i < BOOK_SIZE; i++)
    {
        (list+i)->firstName = malloc(MAX_NAME_LENGTH);
        (list+i)->lastName = malloc(MAX_NAME_LENGTH);
        (list+i)->contact.email = malloc(MAX_NAME_LENGTH);
    }
    return list;
}
void add_contacts(Person* list)
{
    int i;
    
    for (i = 0; i < BOOK_SIZE; i++)
    {
        printf("===============================\n");
        printf("CONTACT %d\n", i+1);
        printf("===============================\n");
        printf("Enter the first name: \n");
        scanf("%s", (list+i)->firstName);
        printf("Enter the last name: \n");
        scanf("%s", (list+i)->lastName);
        printf("Enter the email: \n");
        scanf("%s", (list+i)->contact.email);
        while ((check_email((list+i)->contact.email) == 0))
        {
            printf("Invalid email.  Make sure you have an '@'\n");
            scanf("%s", (list+i)->contact.email);
        }
        printf("Enter the phone number (10 digits): \n");
        scanf("%ld", &(list+i)->contact.phone);
        while ((check_phone((list+i)->contact.phone) == 0))
        {
            printf("Phone number not 10 digits long\n");
            scanf("%ld", &(list+i)->contact.phone);
        }
        
    }
}
void free_list(Person* list)
{
    int i;
    for (i = 0; i < BOOK_SIZE; i++)
    {
        free((list+i)->contact.email);
        free((list+i)->lastName);
        free((list+i)->firstName);
    }
    free(list);
}
void print_list(Person* list)
{
    int i;
    
    for (i = 0; i < BOOK_SIZE; i++)
    {
        printf("%d) %s %s\n", i, (list+i)->firstName, (list+i)->lastName);
        printf("Email: %s\n", (list+i)->contact.email);
        printf("Phone: %ld\n", (list+i)->contact.phone);
    }

}
