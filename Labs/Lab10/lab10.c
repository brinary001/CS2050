//
//  lab10.c
//  
//
//  Created by Brian Robinson on 4/13/17.
//
//

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct Person {
    char first[50];
    char last[50];
    char email[50];
    char phone[50];
    char balance[25];
    struct Person* left;
    struct Person* right;
} person;

int isPhone(char* phone);
int isEmail(char* email);
int isName(char* name);
void print_address_book(person* head);
person* add_person(person* head, char* first, char* last, char* phone, char* email, char* balance);
void free_address_book(person* head);
int isBalance(char* balance);

int main(int argc, char **argv){
    
    if (argc!=2)
    {
        printf("Correct Usage: ./a.out <filename>\n");
    }
    person* head = NULL;
    
    //char *input = *(argv+1);
    char string[50];
    char string2[50];
    char fnTemp[25], lnTemp[25], eTemp[25], pTemp[25];
    char balance[25];
    
    FILE *fptr;
    
    int x = 0;
    for (x = 1; x < 6; x++){
        fptr = fopen(argv[x],"r");
        if (fptr == NULL)
        {
            printf("file returned null value\n");
            return 0;
        }
        while(fscanf(fptr,"%s", string)!=EOF){
            if( 0 == isPhone(string)){
                printf("Phone: %s\n", string);
                strcpy(pTemp, string);
            }
            else if( 0 == isEmail(string)){
                printf("Email Address: %s\n", string);
                strcpy(eTemp, string);
            }
            
            
            else if( 0 == isName(string))
            {
                if(fscanf(fptr,"%s",string2) == EOF)
                {
                    printf("End of file... Exiting..\n");
                }
                if (isName(string2) == 0)
                {
                    printf("Name: %s %s\n", string, string2);
                }
                
                
                else if ( 0 == isEmail(string2)){
                    printf("Email Address: %s\n", string);
                    strcpy(eTemp, string);
                }
                else if(  0 == isPhone(string2) ){
                    printf("Phone: %s\n", string);
                    strcpy(pTemp, string);
                }
            }
            if (isBalance(string) == 1)
            {
                strcpy(balance, string);
            }
        
        head = add_person(head, fnTemp, lnTemp, pTemp, eTemp, balance);
        
        strcpy(fnTemp, " ");
        strcpy(lnTemp, " ");
        strcpy(eTemp, " ");
        strcpy(pTemp, " ");
        
        fclose(fptr);

    }
    print_address_book(head);
    free_address_book(head);
}
    return 0;
}

int isPhone(char* phone){
    
    //Get length of string
    int phonelen = strlen(phone);
    
    //Must equal 12
    if(phonelen != 12){
        return -1;
    }
    
    //Make sure everything is a digit, if its not a digit, it must be a hyphen
    int i = 0;
    
    for(i = 0; i < phonelen; i++){
        
        //Checking to see if it is NOT a digit
        if(isdigit(phone[i]) == 0){
            //printf("%c was NOT a digit\n",phone[i]);
            //Checking to see if that non digit was NOT a '-'
            if(phone[i] != '-'){
                //printf("%c was NOT a '-' \n",x);
                return -1;
            }
        }
    }
    
    //Return a good value, zero i guess is good in jason's mind
    return 0;
}

int isEmail(char* email){
    
    int elen = strlen(email);
    
    //Check for an @ symbol
    int i = 0;
    bool atSign = false;
    for(i = 0; i < elen; i++){
        if(email[i] == '@'){
            atSign = true;
            break;
        }
    }
    
    if(atSign == false){
        return -1;
    }
    
    int j = 0;
    char* trail = malloc(sizeof(char)*4);
    for(i = elen-4; i < elen; i++){
        trail[j] = email[i];
        j++;
    }
    
    //printf("Trail: %s\n",trail);
    
    if(strcmp(".edu",trail) == 0  || 0 == strcmp(".com",trail)){
        free(trail);
        return 0;
    }
    
    free(trail);
    
    return -1;
}

int isName(char* name){
    
    int namel = strlen(name);
    
    if(isupper(name[0]) == 0){
        return -1;
    }
    
    int i = 0;
    for(i = 0; i < namel; i++)
    {
        if(isalpha(name[i] == 0)){
            return -1;
        }
    }
    
    return 0;
}

person* add_person(person* head, char* first, char* last, char* phone, char* email, char* balance)
{
    if (head == NULL)
    {
        head = malloc(sizeof(person));
        strcpy(head->first, first);
        strcpy(head->last, last);
        strcpy(head->email, email);
        strcpy(head->phone, phone);
        head->left = NULL;
        head->right = NULL;
    }
    else
    {
        if (strcmp(head->last, last) < 0)
        {
            head->left = add_person(head->left, first, last, phone, email, balance);
        }
        else if (strcmp(head->last, last) > 0)
        {
            head->right = add_person(head->right, first, last, phone, email, balance);
        }
    }
    return head;
}

void print_address_book(person* head)
{
    if (head != NULL)
    {
        
        print_address_book(head->right);
        
        printf("\n===============================================\nNAME: %s %s\n\tPHONE: %s\n\tEMAIL: %s\n\tBalance: %s\n\n===============================================\n", head->first, head->last,
        head->phone, head->email, head->balance);
        
        print_address_book(head->left);
    }
}

void free_address_book(person* head)
{
    if (head != NULL)
    {
        free_address_book(head->left);
        free_address_book(head->right);
        free(head);
    }
}

//BONUS - MY FIRST AND LAST BONUS ATTEMPT EVER!!!
int isBalance(char* balance)
{
    int check = 0;
    
    if (strchr(balance, '$') == NULL)
    {
        check = 1;
    }
    
    if (check == 1)
    {
        return 0;
    }
    return 1;
}
