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

void headMessage(){
    printf("\t\t\t\t\033[0;35m__________________________________________________");
    printf("\n\n\033[1;37m%65s", "| Library in C |");
    printf("\n\t\t\t\t\033[0;35m__________________________________________________\033[0m");
}

void headMessage2(const char *message){
    printf("\n\t\t\t\t\033[0;34m--------------------------------------------------\033[0;36m\n");
    printMessageCenter(message);
    printf("\n\t\t\t\t\033[0;34m--------------------------------------------------\033[0m\n");
}

void welcomeMessage(){
    headMessage();
    headMessage2("Library Management Project");
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

void backMenu(){
    printf("\n\n%60s", "Back = 1");
    int option;
    printf("\n\n\033[1;32m%63s", "Enter option -> ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        break;
    
    default:
        printf("\n\n\n\033[0;31m%73s\n", "INVALID INPUT!!! Try again...");
        break;
    }
}

// variable untuk dibaca saat dimenu
struct user {
        char newUsername[1000];
        char newPassword[1000];
        char username[1000];
        char password[1000];
    } account;

// Sign up and log in module
void signup () {

    char name [100];
    char password [20];
    printf("\n");
    printf("\033[0;37m%58s\n\n", "Sign Up");

    printf("%63s", "Enter your new username : ");
    fscanf(stdin, "%s", name);

    printf("%63s", "Enter your new password : ");
    fscanf(stdin, "%s", password);

    FILE *file = fopen("accountdata.txt", "a");

    fprintf(file, "Username : %s\n", name);
    fprintf(file, "Password : %s\n", password);
    fprintf(file, "----------\n");
    fprintf(file, "\n");

    fclose(file);
}

struct account {
    char id[20]; 
    char password[20];
};

static struct account accounts[10];

void read_file(struct account accounts[])
{
    FILE *fp;
    int i = 0;   // count how many lines are in the file
    int c;

    fp = fopen("accountdata.txt", "r");

    while(!feof(fp)) {

        c = fgetc(fp);
        if(c == '\n')
            ++i;
    }

    int j = 0;

    rewind(fp);  // Line I added
        // read each line and put into accounts

    while(j!=i-1) {
        fscanf(fp, "Username : %s\nPassword : %s\n----------\n", accounts[j].id, accounts[j].password);
        ++j;
    }
    fclose(fp);
}

struct logAccount{
    char username[100];
    char password[100];
} logAccount;

void signuplogin(){

    int option;
    int k;
    int check = 0;
    headMessage2("Sign up & Log in");
    printf("\n\033[0;37m%59s\n", "1. Sign up");
    printf("%58s\n", "2. Log in");
    printf("%56s\n", "3. Back");
    printf("\n\n\033[1;32m%63s","Enter option -> ");
    scanf("%d", &option);
    switch (option)
    {

    case 1:
        signup();
        break;

    case 2:
        printf("\n");
        printf("\033[0;37m%58s\n\n", "Log In");
        printf("%63s", "Enter your username : ");
        scanf("%s", logAccount.username);
        printf("%63s", "Enter your password : ");
        scanf("%s", logAccount.password);

        read_file(accounts);

        

        for (k = 0; k < 5; k++) {

            if (strcmp(accounts[k].id, logAccount.username) == 0 && strcmp(accounts[k].password, logAccount.password) == 0) {

                printf("\n\033[1;32m%67s\n\033[0;37m", "Login successfull!");
                check = 1;
                break;
            } 
        }

        if (check == 0) {

            printf("\n\033[0;31m%65s\n\033[0;37m", "Login failed!");
        }

        if (strcmp("adminOracle", logAccount.username) == 0 && strcmp("12345" ,logAccount.password) == 0 && check == 1)
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
}

// View books Module
struct data {
    char title[1000];
    char author[1000];
    long int publication;
    long long int codeBooks;
    char status[15];
} dataBooks[10];


void viewBooks(){ 
    int i = 0;
    FILE* file =fopen("databaseBooks.txt","r");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }
    while (!feof(file))
    {
        fscanf(file, "%[^_]_%[^_]_%ld_%lld_%s\n", dataBooks[i].title, dataBooks[i].author, &dataBooks[i].publication, &dataBooks[i].codeBooks, dataBooks[i].status);
        i++;
    }
    int n = i;
    headMessage2("List of Books");
    for (i = 0; i < n; i++)
    {
        printf("\n\n\033[0;37m%38d. Title : %s\n", i+1,dataBooks[i].title);
        printf("%47s %10s %s\n", "Author ", ":", dataBooks[i].author);
        printf("%58s %ld\n", "Publication year :", dataBooks[i].publication);
        printf("%45s %12s %lld\n", "ISBN ", ":", dataBooks[i].codeBooks);
        printf("%47s %10s %s\n", "Status ", ":", dataBooks[i].status);
    }
    backMenu();
    fclose(file);
}

// Add books Module
struct newData {
        char title[10000];
        char author[10000];
        long int publication;
        long long int codeBooks;
} addData;

void addBooks(){
    FILE* file = fopen("databaseBooks.txt", "a+");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }
    headMessage2("Add Books");
    printf("\n\n\033[0;37m%50s", "Enter title : ");
    getchar();
    fscanf(stdin,"%[^\n]", addData.title);
    getchar();
    printf("\n%51s", "Enter author : ");
    fscanf(stdin,"%[^\n]", addData.author);
    getchar();
    printf("\n%61s", "Enter publication year : ");
    fscanf(stdin ,"%ld", &addData.publication);
    printf("\n%54s", "Enter Code Book : ");
    fscanf(stdin ,"%lld", &addData.codeBooks);
    fprintf(file, "%s_%s_%ld_%lld_Available\n", addData.title, addData.author, addData.publication, addData.codeBooks);
    printf("\n\n\033[1;32m%68s\n\033[0;37m", "Book added successfully!");
    backMenu();
    fclose(file);
}

// Search books module
void searchBooks(){
    FILE *fp = fopen("databaseBooks.txt", "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return;
    }
    
    int found = 0; //flag to check if book found
    char bookName[1000];
    char searchInBooks[1000];
    headMessage2("Search Books");
    printf("\033[0;37m\n%69s", "What are you looking for : ");
    scanf("%s", searchInBooks);

    while(fgets(bookName, sizeof(bookName), fp)){
        if(strstr(bookName, searchInBooks)){
        printf("\n%45s %s", "Book found : ", bookName);
        found = 1;
        break;
        }
    }
    if(!found){
        printf("\n%72s\n", "Book not found in the data base.");
    }
    backMenu();
    fclose(fp);
}

// borrow books module
void borrowBooks(){
    FILE* file = fopen("databaseBooks.txt", "r");
    int i = 0;
    char borrowTitle[1000];

    headMessage2("Borrow Books");
    printf("\033[0;37m\n%55s", "Enter the book title : "); getchar(); 
    scanf("%[^\n]", borrowTitle); getchar(); 
    
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    while (!feof(file))
    {
        fscanf(file, "%[^_]_%[^_]_%ld_%lld_%s\n", dataBooks[i].title, dataBooks[i].author, &dataBooks[i].publication, &dataBooks[i].codeBooks, dataBooks[i].status);
        i++;
    }

    int n = i;
    int j = 0;
    for (i = 0; i < n; i++) {

        
            if (strcmp(borrowTitle, dataBooks[i].title) == 0) {
                
                if (strcmp("Available", dataBooks[i].status) == 0) {

                    printf("\n\n\033[0;37m%68s", "Book succesfully Borrowed");
                    strcpy(dataBooks[i].status, "Unavailable");
                    
                } else {

                    printf("\n\n\033[0;37m%75s", "Book Already Borrowed by Someone Else");
                    j = 0;
                }
            } else
            {
                j = 1;
            }
    }
    if (j == 1)
    {
        printf("\n\n\033[0;37m%65s\n", "Book not found!");
    }
    
    fclose(file);

    FILE* rev = fopen("databaseBooks.txt", "w");

    for (i = 0; i < n; i++) {

        fprintf(rev, "%s_%s_%ld_%lld_%s\n", dataBooks[i].title, dataBooks[i].author, dataBooks[i].publication, dataBooks[i].codeBooks, dataBooks[i].status);
    }

    fclose(rev);

}

// return books module
void returnBooks() {
    FILE* file = fopen("databaseBooks.txt", "r");
    int i = 0;
    char returnTitle[1000];

    headMessage2("Return Books");
    printf("\033[0;37m\n%55s", "Enter the book title : "); getchar(); 
    scanf("%[^\n]", returnTitle); getchar(); 

    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    while (!feof(file))
    {
        fscanf(file, "%[^_]_%[^_]_%ld_%lld_%s\n", dataBooks[i].title, dataBooks[i].author, &dataBooks[i].publication, &dataBooks[i].codeBooks, dataBooks[i].status);
        i++;
    }

    int n = i;
    for (i = 0; i < n; i++) {
        
            if (strcmp(returnTitle, dataBooks[i].title) == 0) {
                
                printf("\n\n\033[0;37m%68s", "Thank You for Returned the Book!");
                strcpy(dataBooks[i].status, "Available");
                break;
            }

            else if (i == n - 1) {

                printf("\n\n\033[0;37m%68s\n", "The book is not similar");
                break;
            }
    }

    fclose(file);

    FILE* rev = fopen("databaseBooks.txt", "w");

    for (i = 0; i < n; i++) {

        fprintf(rev, "%s_%s_%ld_%lld_%s\n", dataBooks[i].title, dataBooks[i].author, dataBooks[i].publication, dataBooks[i].codeBooks, dataBooks[i].status);
    }

    fclose(rev);

}

// Main menu library
void menu(){
    headMessage();
    int option, key = 0, key1 = 0, i;
    do
    {
        headMessage2("Main Menu");
        printf("\n\033[0;37m%68s\n", "1. Sign up & Log in");
        printf("%62s\n", "2. View Books");
        printf("%64s\n", "3. Search Books");
        printf("%64s\n", "4. Borrow Books");
        printf("%61s\n", "5. Add Books");
        printf("%64s\n", "6. Return Books");
        if (key == 1 || key1 == 1)
        {
            printf("\n%59s\n\n", "7. Log out");
        }
        
        printf("%56s\033[0m\n", "0. Exit");
        printf("\n\n\033[1;32m%63s", "Enter option -> ");
        scanf("%d", &option);
        printf("\033[0m");
        switch (option)
        {
        case 1:
            signuplogin();
            FILE* file = fopen("accountdata.txt", "r");
            if (strcmp("adminOracle", logAccount.username) == 0 && strcmp("12345" , logAccount.password) == 0)
            {
                key = 1;
            } else
            {
                key = 0;
            }
            read_file(accounts);
            for (i = 0; i < 5; i++) {
                if (strcmp(accounts[i].id, logAccount.username) == 0 && strcmp(accounts[i].password, logAccount.password) == 0) {
                    key1 = 1;
                } 
            }
            
            fclose(file);
            
            break;
        case 2:
            viewBooks();
            break;
        case 3:
            searchBooks();
            break;
        case 4:
            if (key1 == 1)
            {
                borrowBooks();
            } else
            {
                printf("\n\n\n\033[0;31m%69s\033[0;37m\n\n", "You don't have access");
                printf("\n\033[0;31m%68s\033[0;37m\n\n", "Please login first!");
            }
            
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
            if (key1 == 1)
            {
                returnBooks();
            } else
            {
                printf("\n\n\n\033[0;31m%69s\033[0;37m\n\n", "You don't have access");
                printf("\n\033[0;31m%68s\033[0;37m\n\n", "Please login first!");
            }

            break;
        case 7:
            key = 0;
            key1 = 0;
            break;
        case 0:
            printf("\n\n\n\033[1;33m%73s\n\n\n", "Thank You, Please Come Again!!");
            break;
        
        default:
            printf("\n\n\n\033[0;31m%73s\n", "INVALID INPUT!!! Try again...");
            break;
        }
    } while (option != 0);
    
}

int main()
{
    welcomeMessage();
    menu();
    return 0;
}