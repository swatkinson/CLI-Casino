#define _CRT_SECURE_NO_WARNINGS
#include "FileIO.h"

void OpenFileInRead(FILE** f) {
    *f = fopen(FILE_NAME, "r");
    if (*f == NULL) {
        printf("File not found. Creating a new one...\n");
        MakeFile();
        *f = fopen(FILE_NAME, "r");
        if (*f == NULL) {
            fprintf(stderr, "ERROR: Failed to open file after creating it.\n");
            exit(EXIT_FAILURE);
        }
    }
}

void OpenFileInWrite(FILE** f) {
    *f = fopen(FILE_NAME, "w");
    if (*f == NULL) {
        fprintf(stderr, "ERROR: Unable to open file in write mode.\n");
        exit(EXIT_FAILURE);
    }
}

void MakeFile() {
    FILE* f = NULL;
    OpenFileInWrite(&f);
    printf("File created successfully!\n");
    fclose(f);
}

void PrintAllUsersToScreen() {
    FILE* f = NULL;
    OpenFileInRead(&f);

    USER temp;
    while (fscanf(f, "%50s %lf", temp.username, &temp.balance) == 2) {
        printf("%s\t%.2lf\n", temp.username, temp.balance);
    }
    fclose(f);
}

PUSER UserSelection() {
    PrintAllUsersToScreen();

    char userInput[MAX_USERNAME_LEN] = "";
    while (1) {
        printf("Please enter the username you would like to select: ");
        if (scanf("%50s", userInput) != 1) {
            printf("Invalid input. please try again.");
        }
        else {
            break;
        }
    }

    char fileLineUsername[MAX_USERNAME_LEN] = { 0 };
    double fileLineBalance;
    FILE* f = NULL;
    OpenFileInRead(&f);

    bool found = false;
    while (fscanf(f, "%49s %lf", fileLineUsername, &fileLineBalance) == 2) {
        if (strcmp(userInput, fileLineUsername) == 0) {
            found = true;
            break;
        }
    }
    fclose(f);
    if (found) {
        PUSER u = CreateUser(fileLineUsername, fileLineBalance);
        printf("Welcome back, %s! Balance: %.2lf\n", u->username, u->balance);
        return u;
    }
    else {
        printf("User not found.\na. Try again\nb. Create new user\n"); // GetUserInput this
        char choice = GetUserInput("abq");

        switch (choice)
        {
        case 'a':
            return UserSelection();
            break;
        
        case 'b':
            CreateNewUser();
            break;
        }
    }
    return;//this should never happen
}

void UpdateUser(PUSER u) {
    FILE* original = NULL;
    OpenFileInRead(&original);

    FILE* temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        fprintf(stderr, "ERROR: Could not open temp file.\n");
        fclose(original);
        exit(EXIT_FAILURE);
    }

    USER current;
    bool found = false;

    while (fscanf(original, "%50s %lf", current.username, &current.balance) == 2) {
        if (strcmp(current.username, u->username) != 0) {
            fprintf(temp, "%s %.2lf\n", current.username, current.balance);
        }
        else {
            found = true;
        }
    }

    if (found) {
        fprintf(temp, "%s %.2lf\n", u->username, u->balance);
    }
    else {
        printf("User not found, cannot update.\n");
    }

    fclose(original);
    fclose(temp);

    remove(FILE_NAME);
    if (rename("temp.txt", FILE_NAME) == 0) {
        printf("User updated successfully");
    }
}

void CreateNewUser() {
    char username[MAX_USERNAME_LEN];
    username[MAX_USERNAME_LEN - 1] = '\0';//have to do this, if not a warning appears
    printf("Please enter a username for a new user: ");
    if (scanf("%50s", username) != 1) {

    }

    FILE* f = NULL;
    OpenFileInRead(&f);

    USER u;
    bool exists = false;

    while (fscanf(f, "%50s %lf", u.username, &u.balance) == 2) {
        if (strcmp(username, u.username) == 0) {
            exists = true;
            break;
        }
    }
    fclose(f);

    if (exists) {
        int choice = 0;
        printf("Username already exists.\n1. Select existing user\n2. Create new user\n");
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input.\n");
            exit(EXIT_FAILURE);
        }
        if (choice == 1) {
            UserSelection();
        }
        else {
            CreateNewUser();
        }
    }
    else {
        FILE* f_append = fopen(FILE_NAME, "a");
        if (f_append == NULL) {
            fprintf(stderr, "ERROR: Could not open file to append new user.\n");
            exit(EXIT_FAILURE);
        }

        strncpy(u.username, username, MAX_USERNAME_LEN - 1);
        u.balance = STARTING_BALANCE;

        fprintf(f_append, "%s %.2lf\n", u.username, u.balance);
        fclose(f_append);

        printf("User %s created with starting balance: %.2lf\n", u.username, u.balance);
    }
}

void DeleteUserFromFile() {
    FILE* original = NULL;
    OpenFileInRead(&original);

    FILE* temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        fprintf(stderr, "ERROR: Could not open temp file.\n");
        fclose(original);
        exit(EXIT_FAILURE);
    }

    USER u;
    USER current;
    bool found = false;
    while (1) {
        printf("Please enter the username of the user you would like to delete: ");
        if (scanf("%50s", u.username) != 1) {
            printf("Invalid input. Please try again.");
            system("cls");
        }
        else {
            break;
        }
    }

    while (fscanf(original, "%50s %lf", current.username, &current.balance) == 2) {
        if (strcmp(current.username, u.username) != 0) {
            fprintf(temp, "%s %.2lf\n", current.username, current.balance);
        }
        else {
            printf("found user, and did not print it to the new file.");//this is just a check :)
        }
    }

    fclose(original);
    fclose(temp);

    remove(FILE_NAME);
    if (rename("temp.txt", FILE_NAME) == 0) {
        printf("User deleted successfully");
    }

}

PUSER UserMenu() {

    printf("What would you like to do?\n"
           "a. Create new user\n"
           "b. Select a user\n"
           "c. Delete a user\n"
           "q. QUIT\n");
    char selection = GetUserInput("abcq");

    switch (selection)
    {
    case'a':
        CreateNewUser();
        break;

    case'b':
        return UserSelection();
        break;

    case'c':
        DeleteUserFromFile();
        break;

    case'q':
        exit(EXIT_SUCCESS);
        break;

    }
   
    return NULL; // THIS SHOULDNT HAPPEN, 
    // CREATE NEW USER & SELECT USER SHOULD RETURN A PUSER
    // DELETE USER FROM FILE AND EXIT SHOULD QUIT THE PROGRAM
}