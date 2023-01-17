#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printMessageCenter(const char *message){
    int length = 0;

    length = (68 - strlen(message))/2;
    printf("\t\t\t");
    int i;
    for ( i = 0; i < length; i++)
    {
        printf(" ");
    }
    printf("%s", message);
}

void headMessage(const char *message){
    printf("\t\t\t\t\033[0;35m__________________________________________________");
    printf("\n\n\033[1;37m%65s", "| Library in C |");
    printf("\n\t\t\t\t\033[0;35m__________________________________________________\033[0m");
    printf("\n\t\t\t\t\033[0;34m--------------------------------------------------\033[0;36m\n");
    printMessageCenter(message);
    printf("\n\t\t\t\t\033[0;34m--------------------------------------------------\033[0m\n");
}

void headMessage2(){
    printf("\t\t\t\t\033[0;35m__________________________________________________");
    printf("\n\n\033[1;37m%65s", "| Library in C |");
    printf("\n\t\t\t\t\033[0;35m__________________________________________________\033[0m");
}

void welcomeMessage(){
    headMessage("Library Management Project");
    printf("\n\t\t\t\t\033[0;31m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\033[0;33m");
    printf("\n\t\t\t          .............................................");
    printf("\n\t\t\t          |                  WELCOME                  |");
    printf("\n\t\t\t          |                    TO                     |");
    printf("\n\t\t\t          |                  ORACLE                   |");
    printf("\n\t\t\t          |                  LIBRARY                  |");
    printf("\n\t\t\t          .............................................\n");
    printf("\n\t\t\t\t\033[0;31m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\033[0m\n");
    printf("\n\t\t\t\t Enter to continue.....");
    getchar();
}

// variable untuk dibaca saat dimenu
struct user {
        char newUsername[1000];
        char newPassword[1000];
        char username[1000];
        char password[1000];
    } account;

// Sign up and log in module
void signuplogin(){
    int option, key;
    
    FILE* file = fopen("accountdata.txt", "a+");
    printf("\n\t\t\t\t\033[0;34m--------------------------------------------------\033[0;36m\n");
    printMessageCenter("Sign up & Log in");
    printf("\n\t\t\t\t\033[0;34m--------------------------------------------------\033[0m\n");
    printf("\n\033[0;37m%59s\n", "1. Sign up");
    printf("%58s\n", "2. Log in");
    printf("%56s\n", "3. Back");
    printf("\n\n\033[1;32m%63s","Enter option -> ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        printf("\n");
        printf("\033[0;37m%58s\n\n", "Sign Up");
        printf("%63s", "Enter your new username : ");
        fscanf(stdin, "%s", account.newUsername);
        printf("%63s", "Enter your new password : ");
        fscanf(stdin, "%s", account.newPassword);
        fprintf(file, "%s - %s\n", account.newUsername, account.newPassword);
        break;
    case 2:
        printf("\n");
        printf("\033[0;37m%58s\n\n", "Log In");
        printf("%63s", "Enter your username : ");
        scanf("%s", account.username);
        printf("%63s", "Enter your password : ");
        scanf("%s", account.password);
        FILE* file = fopen("accountdata.txt", "r");
        while (fscanf(file,"%s - %s\n", account.newUsername, account.newPassword) == 2); //check file
        if (strcmp(account.username, account.newUsername) == 0 && strcmp(account.password, account.newPassword) == 0)
        {
            printf("\n\033[1;32m%67s\n\033[0;37m", "Login successfull!");
        } else
        {
            printf("\n\033[0;31m%65s\n\033[0;37m", "Login failed!");
        }
        if (strcmp("adminOracle", account.username) == 0 && strcmp("12345" ,account.password) == 0)
        {
            printMessageCenter("You are now login as admin");
            printf("\n");
        }
        break;
    case 3:
        break;
    
    default:
        printf("INVALID INPUT!!! Try again...");
        break;
    }
    fclose(file);
}

// View books
struct data {
    char title[1000];
    char author[1000];
    long int publication;
} dataBooks[10];


void viewBooks(){ 
    int i = 0;
    FILE* file =fopen("databaseBooks.txt","r");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }
    while (fscanf(file, "%[^_] _ %[^_] _ %ld\n", dataBooks[i].title, dataBooks[i].author, &dataBooks[i].publication) == 3)
    {
        i++;
    }
    int n = i;
    printf("\n\t\t\t\t\033[0;34m--------------------------------------------------\033[0;36m\n");
    printMessageCenter("List of Books");
    printf("\n\t\t\t\t\033[0;34m--------------------------------------------------\033[0m\n");
    for (i = 0; i < n; i++)
    {
        printf("\n\n\033[0;37m%38d. Title : %s\n", i+1,dataBooks[i].title);
        printf("%48s %s\n", "Author :", dataBooks[i].author);
        printf("%58s %ld\n", "Publication year :", dataBooks[i].publication);
    }
    fclose(file);
}

// Add books
void addBooks(){
    FILE* file = fopen("databaseBooks.txt", "a+");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }
    struct newData {
        char title[10000];
        char author[10000];
        long int publication;
    } addData;
    printf("\n\t\t\t\t\033[0;34m--------------------------------------------------\033[0;36m\n");
    printMessageCenter("Add Books");
    printf("\n\t\t\t\t\033[0;34m--------------------------------------------------\033[0m\n");
    printf("\n\n%50s", "Enter title : ");
    getchar();
    fscanf(stdin,"%[^\n]", addData.title);
    getchar();
    printf("\n%51s", "Enter author : ");
    fscanf(stdin,"%[^\n]", addData.author);
    getchar();
    printf("\n%61s", "Enter publication year : ");
    fscanf(stdin ,"%ld", &addData.publication);
    fprintf(file, "\n%s _ %s _ %ld", addData.title, addData.author, addData.publication);
    printf("\n\n\033[1;32m%50s\n\033[0;37m", "Book added successfully!");
    fclose(file);
}

// Search books module
void searchBooks(){

}

// Main menu library
void menu(){
    headMessage2();
    int option, key = 0;
    do
    {
        printf("\n\t\t\t\t\033[0;34m--------------------------------------------------\033[0;36m\n");
        printMessageCenter("Main Menu");
        printf("\n\t\t\t\t\033[0;34m--------------------------------------------------\033[0m\n");
        printf("\n\033[0;37m%68s\n", "1. Sign up & Log in");
        printf("%62s\n", "2. View Books");
        printf("%64s\n", "3. Search Books");
        printf("%64s\n", "4. Borrow Books");
        printf("%61s\n", "5. Add Books");
        printf("%56s\033[0m\n", "6. Exit");
        printf("\n\n\033[1;32m%63s", "Enter option -> ");
        scanf("%d", &option);
        printf("\033[0m");
        switch (option)
        {
        case 1:
            signuplogin();
            FILE* file = fopen("accountdata.txt", "r");
            if (strcmp("adminOracle", account.username) == 0 && strcmp("12345" , account.password) == 0)
            {
                key = 1;
            } else
            {
                key = 0;
            }
            
            break;
        case 2:
            viewBooks();
            break;
        case 3:
            /* code */
            break;
        case 4:
            /* code */
            break;
        case 5:
            if (key == 1)
            {
                addBooks();
            } else
            {
                printf("\n\n\n\033[0;31m%68s\033[0;37m\n\n", "You don't have access");
            }
            
            
            break;
        case 6:
            printf("\n\n\n\033[1;33m%73s\n\n\n", "Thank You, Please Come Again!!");
            break;
        
        default:
            printf("\n\n\n\033[0;31m%73s\n", "INVALID INPUT!!! Try again...");
            break;
        }
    } while (option != 6);
    
}

int main()
{
    welcomeMessage();
    menu();
    return 0;
}