//
//  main.c
//  HW2
//
//  Created by Brian Robinson on 3/20/17.
//  Copyright © 2017 Brian Robinson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct Book {
    int bookID;
    char* title;
    bool checkedOut;
    struct Book* next;
} book;

typedef struct BookIds {
    int id;
    struct BookIds* next;
} bookIds;

typedef struct Student {
    char* firstName;
    char* lastName;
    int priority;
    int readingLevel;
    bookIds* wishlist;
    struct Student* next;
} student;

//Prototypes

void freeStudentList(student* head);
void freeWishlist(bookIds* head);
void freeBookList(book* head);

//Part One
student* buildStudentList(char* studentsFile, student* head);
void printStudents(student* head);
void createPriorityQueue(student* head);

//Part Two
void addWishlist(student* head, char* wishListfile);
book* createBookList(char* bookFile,book* bookHead);
void printBookList(book* bookHead);

//Part Three
void checkOutBooks(student* studentHead, book* bookHead);
book* findBook(book* bookhead, int book_id);

#define NAME 25
#define TITLE 50
int main(int argc, char* argv[])
{
    
    if (argc != 4)
    {
        printf("----------------- INVALID USE OF PROGRAM!! ----------------\n");
        printf("./a.out students.txt wishlist.txt books.txt\n");
        printf("-----------------------------------------------------------\n");
        return 0;

    }
    
    student* head = NULL;
    book* bookHead = NULL;
    
    char* studentsFile = argv[1];
    char* wishListfile = argv[2];
    char* bookFile = argv[3];
    
    //Not sure if this shit will work
    head = buildStudentList(studentsFile, head);
    printf("Students \n");
    printStudents(head);
    createPriorityQueue(head);
    addWishlist(head, wishListfile);
    printStudents(head);
    bookHead = createBookList(bookFile, bookHead);
    printBookList(bookHead);
    checkOutBooks(head, bookHead);
    
    freeStudentList(head);
    freeBookList(bookHead);

    
    return 0;
}

// FUNCTIONS
student* buildStudentList(char* studentsFile, student* head)
{
    if (head != NULL)
    {
        head = NULL;
    }
    
    FILE* fp = fopen(studentsFile, "r");
    
    head = malloc(sizeof(student));
    student* current = head;
    
    if ( !fp ) //Revisit - Return NULL?
    {
        printf("File could not be opened \n\n");
        return 0;
    }
    
    while (!feof(fp))
    {
        if (current == head)
        {
            current->firstName = malloc(sizeof(char) * NAME);
            current->lastName = malloc(sizeof(char) * NAME);
            current->wishlist = malloc(sizeof(bookIds));
            current->next = NULL;
            fscanf(fp, "%s %s %d %d", current->firstName, current->lastName, &(current->priority), &(current->readingLevel));
            //current = malloc(sizeof(student));//Allocaate space for student info
            current->next = malloc(sizeof(student)); //initialize next student to zero
            current = current->next; //sets current ptr to null
        }
        
        else
        {
            current->firstName = malloc(sizeof(char) * NAME);
            current->lastName = malloc(sizeof(char) * NAME);
            current->wishlist = malloc(sizeof(bookIds));
            //current = malloc(sizeof(student)); //initialize memory for next student
            
            if (fscanf(fp, "%s %s %d %d", current->firstName, current->lastName, &(current->priority), &(current->readingLevel)) == EOF)
            {
                current->next = NULL;
                return head;
            }
            
            current->next = malloc(sizeof(student));
            current = current->next;

        }
        
    }
    
    current->next = NULL;
    
    fclose(fp);
    
    return head;
}

// PRINT
void printStudents(student* head)
{
    student* current = head;
    //bookIds* currentBook = current->wishlist;
    
    if (head == NULL)
    {
        printf("The head was NULL inside of print function\n");
        return;
    }
    
    while (current->next != NULL)
    {
        //currentBook = current->wishlist;
        printf("First Name: %s\nLast Name: %s\nPriority: %d\nReading Level: %d\nWishlist: ", current->firstName, current->lastName, current->priority, current->readingLevel);
        
        /*while (currentBook)
        {
            printf("%d->", currentBook->id);
            current = current->next;
        }*/
        current = current->next;
    }
}

// CREATE PRIORITY
void createPriorityQueue(student* head)
{
    student* queue = NULL;
    student* current = head;
    student* new = NULL;
    //student* queueHead = NULL;
    student* hold = NULL;
    student* smallest = NULL;
    student* start = head;
    
    queue = malloc(sizeof(student));
    
    int queueCount = 0;
    
    // Copies list for sorting
    while (current != NULL)
    {
        while (start->next != NULL)
        {
            if ((start->next)->priority < start->priority)
            {
                smallest = start->next;
            }
        }
        queue->firstName = malloc(sizeof(char) * NAME);
        queue->lastName = malloc(sizeof(char) * NAME);
        strcpy(queue->firstName, smallest->firstName);
        strcpy(queue->lastName, smallest->lastName);
        queue->priority = smallest->priority;
        queue->readingLevel = smallest->readingLevel;
        
        current = current->next;
        
        if (current == NULL)
        {
            queue->next = NULL;
        }
        
        else
        {
            new = malloc(sizeof(student));
            queue->next = new;
            queue = queue->next;
        }
        queueCount++;
    }
    
    int i, j;
    
    //queueHead = queue;
    
    for (i = 0; i < queueCount; i++)
    {
        current = queue+i;
        
        for (j = 0; j < queueCount; j++)
        {
            
            if (current[j+1].priority < current[j].priority)
            {
                hold = &current[j];
                current[j] = current[j+1];
                current[j+1] = *(hold);
            }
            
        }
    }
    
    
}

//ADD WISH LIST
void addWishlist(student* head, char* wishListfile)
{
    FILE* fp = fopen(wishListfile, "r");
    
    if (fp == NULL)
    {
        printf("Could not open file\n");
        exit(0);
    }
    
    student* current = head;
    bookIds* currentBook = head->wishlist;
    
    while (current->next)
    {
        int i = 0;
        
        currentBook = current->wishlist;
        
        for (i = 0; i < 4; i++)
        {
            if (currentBook == NULL)
            {
                currentBook = malloc(sizeof(bookIds));
            }
            
            fscanf(fp, "%d", &(currentBook->id));
            currentBook->next = NULL;
            
            if (i < 3)
            {
                currentBook->next = malloc(sizeof(bookIds));
            }
            
            
            currentBook = currentBook->next;
        }
        
        current = current->next;
    }
    
    fclose(fp);
}

//CREATE BOOK LIST
book* createBookList(char* bookFile, book* bookHead)
{
    FILE* fp = fopen(bookFile, "r");
    
    book* current = bookHead;
    book* prev = NULL;
    
    if (fp == NULL) //Revisit - Return NULL?
    {
        printf("File could not be opened \n\n");
        return 0;
    }
    
    while (!feof(fp))
    {
        if (current == bookHead)
        {
            current = malloc(sizeof(book));//Allocate space for book info
            fscanf(fp, "%d %s", &current->bookID, current->title);
            current->next = NULL; //initialize next book to zero
            prev = current; //stores address of the head
            current = NULL; //sets current ptr to null
        }
        
        else
        {
            current = malloc(sizeof(book)); //initialize memory for next student
            prev->next = current; //Linking happens here
            fscanf(fp, "%d %s", &current->bookID, current->title);
            prev = current;
            current->next = NULL;
        }
        
    }
    
    return bookHead;
}

//PRINT BOOK LIST
void printBookList(book* bookHead)
{
    book* current = bookHead;
    
    if (current == NULL)
    {
        printf("The book head was NULL inside of print function\n");
        exit(0);
    }
    
    printf("Books\n");
    
    while (current->next != NULL)
    {
        printf("ID: %d Title: %s %s\n", current->bookID, current->title, current->checkedOut ? "Checked out" : "Available");
        current = current->next;
    }
}

//CHECK OUT BOOK
void checkOutBooks(student* studentHead, book* bookHead)
{
    if (studentHead == NULL)
    {
        printf("student list is null inside checkOutBooks function.\n");
        exit(0);
    }
    
    else if (bookHead == NULL)
    {
        printf("book list is null inside checkOutBooks function.\n");
        exit(0);
    }
    
    student* currentStudent = studentHead;
    book* temp = NULL;
    bookIds* currentWishlist = studentHead->wishlist;
    
    while (currentStudent->next)
    {
        currentWishlist = currentStudent->wishlist;
        printf("Student: %s %s is checking out:\n", currentStudent->firstName, currentStudent->lastName);
        
        while (currentWishlist)
        {
            temp = findBook(bookHead, currentWishlist->id);
            
            if (temp->checkedOut == true)
            {
                printf("Book: %s is already checked out!\n", temp->title);
            }
            
            else if (temp->checkedOut == false)
            {
                printf("Book: %s\n", temp->title);
                temp->checkedOut = true;
            }
            
            currentWishlist = currentWishlist->next;
        }
        
        printf("\n");
        currentStudent = currentStudent->next;
    }
}

//FIND BOOK
book* findBook(book* bookhead, int book_id)
{
    book* current = bookhead;
    
    while(current->next)
    {
        if (current->bookID == book_id)
        {
            return current;
        }
        current = current->next;
    }
    
    return NULL;
}

//FREE STUDENT
void freeStudentList(student* head)
{
    student* previous;
    student* current;
    
    while(head != NULL)
    {
        current = head;
        previous = head;
        
        if(head->next != NULL)
        {
            while(current->next)
            {
                previous = current;
                current = current->next;
            }
            
            previous->next = NULL;
            free(current->firstName);
            free(current->lastName);
            //freeWishlist(current->wishlist);
            free(current);
        }else
        {
            free(head->firstName);
            free(head->lastName);
            //freeWishlist(head->wishlist);
            free(head);
            head = NULL;
        }
        
        //current->next = NULL;
    }
    
}

//FREE WISHLIST - COME BACK TO THIS
void freeWishlist(bookIds* head)
{
    bookIds* currentBook = head;
    bookIds* prevBook = head;
    
    while (head != NULL)
    {
        currentBook = head;
        prevBook = head;
        
        if (head->next != NULL)
        {
            while (currentBook->next)
            {
                prevBook = currentBook;
                currentBook = currentBook->next;
            }
            
            prevBook->next = NULL;
            free(currentBook);
        }
        
        else
        {
            free(head);
            head = NULL;
        }
        
    }
}

//FREE BOOK
void freeBookList(book* head)
{
    book* currentBook = head;
    book* prevBook = head;
    
    while (head != NULL)
    {
        if (head->next == NULL)
        {
            free(head->title);
            head->next = NULL;
            free(head);
            head = NULL;
        }
        
        else
        {
            currentBook = head;
            prevBook = head;
            
            while (currentBook->next)
            {
                prevBook = currentBook;
                currentBook = currentBook->next;
            }
            
            free(currentBook->title);
            currentBook->next = NULL;
            free(currentBook);
            prevBook->next = NULL;
        }
    }
}

