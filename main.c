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
    system("clear");
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
    system("clear");
}

void backMenu(){
    printf("\n\n%60s", "Back = 1");
    int option;
    printf("\n\n\033[1;32m%63s", "Enter option -> ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        system("clear");
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
} dataBooks[100];

int partition(struct data *sortdata, int low, int high){
    char pivot[41];
    strcpy(pivot, sortdata[high].title);
    int i = (low - 1);
    int j;
    for ( j = low; j <= high - 1; j++)
    {
        if (strcmp(sortdata[j].title, pivot) < 0)
        {
            i++;
            struct data temp = sortdata[i];
            sortdata[i] = sortdata[j];
            sortdata[j] = temp;
        }
    }
    struct data temp = sortdata[i + 1];
    sortdata[i + 1] = sortdata[high];
    sortdata[high] = temp;
    return (i + 1);
}

void quickSort(struct data *sortdata, int low, int high){
    if (low < high)
    {
        int pivot_index = partition(sortdata, low, high);

        quickSort(sortdata, low, pivot_index - 1);
        quickSort(sortdata, pivot_index + 1, high);
    }
}

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
    quickSort(dataBooks, 0, n-1);
    for (i = 0; i < n; i++)
    {
        printf("\n\n\033[0;37m%38d. Title : %s\n", i+1,dataBooks[i].title);
        printf("%47s %10s %s\n", "Author ", ":", dataBooks[i].author);
        printf("%58s %ld\n", "Publication year :", dataBooks[i].publication);
        printf("%45s %12s %lld\n", "ISBN ", ":", dataBooks[i].codeBooks);
        // printf("%47s %10s %s\n", "Status ", ":", dataBooks[i].status);
        if (strcmp("Available", dataBooks[i].status))
        {
            printf("%47s %10s \033[0;31m%s\n\033[0;37m", "Status ", ":", dataBooks[i].status);
        } else if (strcmp("Unavailable", dataBooks[i].status))
        {
            printf("%47s %10s \033[1;32m%s\n\033[0;37m", "Status ", ":", dataBooks[i].status);
        }
        
        
    }
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

//Delete books module
void deleteBooks(){
    char titleBooks[1000];
    int found = 0, i = 0;
    FILE *file = fopen("databaseBooks.txt", "r");
    FILE *temp = fopen("temp.txt", "a+");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }
    headMessage2("Delete Books");
    fflush(stdin);
    printf("\n\n\033[0;37m%50s", "Enter title : ");
    scanf("%[^\n]", titleBooks);

    while (!feof(file))
    {
        fscanf(file, "%[^_]_%[^_]_%ld_%lld_%s\n", dataBooks[i].title, dataBooks[i].author, &dataBooks[i].publication, &dataBooks[i].codeBooks, dataBooks[i].status);
        i++;
    }
    int n = i;

    for ( i = 0; i < n; i++)
    {
        if (strcmp(dataBooks[i].title, titleBooks) != 0)
        {
            fprintf(temp, "%s_%s_%ld_%lld_%s\n", dataBooks[i].title, dataBooks[i].author, dataBooks[i].publication, dataBooks[i].codeBooks, dataBooks[i].status);
        } else
        {
            found = 1;
        }
    }
    
    fclose(file);
    fclose(temp);
    remove("databaseBooks.txt");
    rename("temp.txt", "databaseBooks.txt");

    if (found)
    {
            printf("\n\n\033[1;32m%68s\n\033[0;37m", "Book deleted successfully!");
    } else
    {
        printf("\n\n\033[0;37m%65s\n", "Book not found!");
    }
}

// Search books module
void searchBooks(){
    
    int i = 0, j;
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
    quickSort(dataBooks, 0, n-1);

    int option;

    headMessage2("Search Book");
    printf("\n\033[0;37m%65s\n", "1. Search by Book Title");
    printf("%61s\n", "2. Search by Author");
    printf("%69s\n", "3. Search by Date Published");
    printf("%59s\n", "4. Search by ISBN");
    printf("\n");
    printf("%49s\n", "5. Back");
    printf("\n\n\033[1;32m%63s","Enter option -> ");
    scanf("%d", &option);
    
    char authorName[30];
    char bookName[30];
    long int datePublished;
    long long int isbn;
    
    int result;
    
    switch(option) {

        case 1:

            printf("\n\033[0;37m%60s", "Enter book title : "); getchar();
            scanf("%[^\n]", bookName);

            int i;

            for (i = 0; i < n; i++) {

                result = 1;

                for (j = 0; j < n; j++) {

                    if (strstr(dataBooks[j].title, bookName)) {

                        result = j;

                        printf("\n\n\033[0;37m%38d. Title : %s\n", i+1,dataBooks[result].title);
                        printf("%47s %10s %s\n", "Author ", ":", dataBooks[result].author);
                        printf("%58s %ld\n", "Publication year :", dataBooks[result].publication);
                        printf("%45s %12s %lld\n", "ISBN ", ":", dataBooks[result].codeBooks);

                        strcpy(dataBooks[result].title, "!!");
                        break;
                    }
                        
                    else  {
                        
                        continue;
                    }
                }
            }

            backMenu();
            break;

        case 2:

            printf("\n\033[0;37m%60s", "Enter Author : "); getchar();
            scanf("%[^\n]", authorName);

                for (i = 0; i < n; i++) {

                result = 1;

                for (j = 0; j < n; j++) {

                    if (strstr(dataBooks[j].author, authorName)) {

                        result = j;

                        printf("\n\n\033[0;37m%38d. Title : %s\n", i+1,dataBooks[result].title);
                        printf("%47s %10s %s\n", "Author ", ":", dataBooks[result].author);
                        printf("%58s %ld\n", "Publication year :", dataBooks[result].publication);
                        printf("%45s %12s %lld\n", "ISBN ", ":", dataBooks[result].codeBooks);

                        strcpy(dataBooks[result].author, "!!");
                        break;
                    }
                        
                    else  {
                        
                        continue;
                    }
                }
            }

            backMenu();
            break;

        case 3:

            printf("\n\033[0;37m%60s", "Enter Date Published : "); getchar();
            scanf("%ld", &datePublished);

                for (i = 0; i < n; i++) {

                result = 1;

                for (j = 0; j < n; j++) {

                    if (dataBooks[j].publication == datePublished) {

                        result = j;

                        printf("\n\n\033[0;37m%38d. Title : %s\n", i+1,dataBooks[result].title);
                        printf("%47s %10s %s\n", "Author ", ":", dataBooks[result].author);
                        printf("%58s %ld\n", "Publication year :", dataBooks[result].publication);
                        printf("%45s %12s %lld\n", "ISBN ", ":", dataBooks[result].codeBooks);

                        dataBooks[result].publication = 0;
                        break;
                    }
                        
                    else  {
                        
                        continue;
                    }
                }
            }

            backMenu();
            break;

        case 4:

            printf("\n\033[0;37m%75s", "Enter ISBN Number (Must Exactly the Same): "); getchar();
            scanf("%lld", &isbn);

                for (i = 0; i < n; i++) {

                result = 1;

                for (j = 0; j < n; j++) {

                    if (dataBooks[j].codeBooks == isbn) {

                        result = j;

                        printf("\n\n\033[0;37m%38d. Title : %s\n", i+1,dataBooks[result].title);
                        printf("%47s %10s %s\n", "Author ", ":", dataBooks[result].author);
                        printf("%58s %ld\n", "Publication year :", dataBooks[result].publication);
                        printf("%45s %12s %lld\n", "ISBN ", ":", dataBooks[result].codeBooks);

                        dataBooks[result].codeBooks = 0;
                        break;
                    }
                        
                    else  {
                        
                        continue;
                    }
                }
            }

            backMenu();
            break;

        case 5:
            system("clear");
            break;

        default:
            printf("\n\n\n\033[0;31m%73s\n", "INVALID INPUT!!! Try again...");
            break;
    }
}

// borrow books module
struct borrow
{
    char status[1000];
    char borrowTitle[1000];
    char account[1000];
} borrows;

void borrowBooks(){
    FILE* file = fopen("databaseBooks.txt", "r");
    FILE* borrowData = fopen("databaseBorrow.txt", "a+");
    char titleBorrow[1000];
    int i = 0;

    headMessage2("Borrow Books");
    printf("\033[0;37m\n%55s", "Enter the book title : "); getchar(); 
    scanf("%[^\n]", titleBorrow); getchar(); 
    strcpy(borrows.borrowTitle, titleBorrow);
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }
    if (borrowData == NULL)
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

        
        if (strcmp(titleBorrow, dataBooks[i].title) == 0) {
            
            if (strcmp("Available", dataBooks[i].status) == 0) {
                
                printf("\n\n\033[0;37m%68s\n", "Book succesfully Borrowed");
                strcpy(borrows.status, "Borrowed");
                strcpy(dataBooks[i].status, "Unavailable");
                strcpy(borrows.account, logAccount.username);
                fprintf(borrowData, "%s_%s_%s\n", borrows.account, borrows.borrowTitle, borrows.status);
                break;
                
            } else {
                printf("\n\n\033[0;37m%75s\n", "Book Already Borrowed by Someone Else");
                break;
            }
        }
        if (i == n-1)
        {
            printf("\n\n\033[0;37m%65s\n", "Book not found!");
            break;
        }
    }
    
    fclose(file);
    fclose(borrowData);

    FILE* rev = fopen("databaseBooks.txt", "w");

    for (i = 0; i < n; i++) {
        fprintf(rev, "%s_%s_%ld_%lld_%s\n", dataBooks[i].title, dataBooks[i].author, dataBooks[i].publication, dataBooks[i].codeBooks, dataBooks[i].status);
    }

    fclose(rev);

}

// return books module
struct databorrow
{
    char status[1000];
    char borrowTittle[1000];
    char account[1000];
} dataBorrows[100];

void returnBooks() {
    FILE* file = fopen("databaseBooks.txt", "r");
    FILE* borrowData = fopen("databaseBorrow.txt", "r");
    int i = 0, j = 0;
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

    while (!feof(borrowData))
    {
        fscanf(borrowData, "%[^_]_%[^_]_%s\n", dataBorrows[j].account, dataBorrows[j].borrowTittle, dataBorrows[j].status);
        j++;
    }

    int n = i;
    int m = j;
    for (i = 0; i < n; i++) {
        
            if (strcmp(returnTitle, dataBooks[i].title) == 0) {
                
                printf("\n\n\033[0;37m%68s\n", "Thank You for Returned the Book!");
                strcpy(dataBooks[i].status, "Available");
                break;
            }

            else if (i == n - 1) {

                // printf("\n\n\033[0;37m%68s\n", "The book is not similar");
                printf("\n\n\033[0;37m%76s\n", "Our library doesn't have that book");
                break;
            }
    }
    for ( j = 0; j < m; j++)
    {
        if (strcmp(returnTitle, dataBorrows[j].borrowTittle) == 0)
        {
            strcpy(dataBorrows[j].status, "Returned");
        }
    }
    

    fclose(file);
    fclose(borrowData);

    FILE* rev = fopen("databaseBooks.txt", "w");
    FILE* borrowFile = fopen("databaseBorrow.txt", "w");

    for (i = 0; i < n; i++) {
        fprintf(rev, "%s_%s_%ld_%lld_%s\n", dataBooks[i].title, dataBooks[i].author, dataBooks[i].publication, dataBooks[i].codeBooks, dataBooks[i].status);
    }
    for (j = 0; j < m; j++)
    {
        fprintf(borrowFile, "%s_%s_%s\n", dataBorrows[j].account, dataBorrows[j].borrowTittle, dataBorrows[j].status);
    }
    

    fclose(rev);
    fclose(borrowFile);
}

// View borrow module
struct accBorrow
{
    char nameAcc[1000];
} acc[100];

void viewBorrow(){
    FILE* borrowFile = fopen("databaseBorrow.txt", "r");
    if (borrowFile == NULL)
    {
        perror("Error opening file");
        return;
    }
    int i = 0;
    while (!feof(borrowFile))
    {
        fscanf(borrowFile, "%[^_]_%[^_]_%s\n", acc[i].nameAcc, dataBorrows[i].borrowTittle, dataBorrows[i].status);
        i++;
    }
    int n = i;
    headMessage2("List of borrower");
    for ( i = 0; i < n; i++)
    {
        printf("\n\n\033[0;37m%38d. %s %10s %s\n", i+1, "Name", ":",acc[i].nameAcc);
        printf("%46s %8s %s\n", "Title ", ":", dataBorrows[i].borrowTittle);
        // printf("%47s %7s %s\n", "Status ", ":", dataBorrows[i].status);
        if (strcmp("Returned", dataBorrows[i].status))
        {
            printf("%47s %7s \033[0;31m%s\n\033[0;37m", "Status ", ":", dataBorrows[i].status);
        } else if (strcmp("Borrowed", dataBorrows[i].status))
        {
            printf("%47s %7s \033[1;32m%s\n\033[0;37m", "Status ", ":", dataBorrows[i].status);
        }
    }
    fclose(borrowFile);
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
        printf("%64s\n", "5. Return Books");
        printf("%61s\n", "6. Add Books");
        if (key == 1)
        {
            printf("\n%64s", "7. Delete Books");
            printf("\n%63s\n", "8. View borrow");
        }
        if (key == 1 || key1 == 1)
        {
            printf("\n%59s\n\n", "9. Log out");
        }
        
        printf("%56s\033[0m\n", "0. Exit");
        printf("\n\n\033[1;32m%63s", "Enter option -> ");
        scanf("%d", &option);
        printf("\033[0m");
        system("clear");
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
            backMenu();
            system("clear");
            break;
        case 3:
            searchBooks();
            break;
        case 4:
            if (key1 == 1)
            {
                borrowBooks();
            } else if (key1 == 0)
            {
                printf("\n\n\n\033[0;31m%69s\033[0;37m\n\n", "You don't have access");
                printf("\n\033[0;31m%68s\033[0;37m\n\n", "Please login first!");
            }
            
            break;
        case 5:
            if (key1 == 1)
            {
                returnBooks();
            } else if (key1 == 0)
            {
                printf("\n\n\n\033[0;31m%69s\033[0;37m\n\n", "You don't have access");
                printf("\n\033[0;31m%68s\033[0;37m\n\n", "Please login first!");
            }
            break;
        case 6:
            if (key == 1)
            {
                addBooks();
            } else if (key == 0)
            {
                printf("\n\n\n\033[0;31m%68s\033[0;37m\n\n", "You don't have access");
            }
            break;
        case 7:
            if (key == 1)
            {
                deleteBooks();
            } else if (key == 0)
            {
                printf("\n\n\n\033[0;31m%68s\033[0;37m\n\n", "You don't have access");
            }
            break;
        case 8:
            if (key == 1)
            {
                viewBorrow();
                backMenu();
                system("clear");
            } else if (key == 0)
            {
                printf("\n\n\n\033[0;31m%68s\033[0;37m\n\n", "You don't have access");
            }
            break;
        case 9:
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