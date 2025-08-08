//CLI Casino | Ricardo Pineda Pelaez | CSCN71030
//File I/O implementation

#define _CRT_SECURE_NO_WARNINGS
#include "FileIO.h"
#include <windows.h>

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

    printf(
        "┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐\n"
        "│                                               List of current users                                                  │\n"
        "├─────────────────────────────────────────────────────────┬────────────────────────────────────────────────────────────┤\n"
    );
    USER temp;
    while (fscanf(f, "%50s %lf", temp.username, &temp.balance) == 2) {
        printf("│User: %-50s │ Balance: %-50.2lf│\n", temp.username, temp.balance);
    }
    printf("└─────────────────────────────────────────────────────────┴────────────────────────────────────────────────────────────┘\n");
    fclose(f);
}

PUSER UserSelection() {

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
        printf("User does not exist.\npress any key to continue.");
        (void)_getch();
        ClearInputBuffer();
        return NULL;
    }
    return NULL;//this should never happen
}

void UpdateUser(PUSER u) {
    FILE* original = NULL;
    OpenFileInRead(&original);

    FILE* temp = fopen(TEMP_FILE_NAME, "w");
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
        fclose(temp);
        temp = fopen(TEMP_FILE_NAME, "a");
        if (temp == NULL) {
            fprintf(stderr, "ERROR: Could not open temp file.\n");
            fclose(original);
            exit(EXIT_FAILURE);
        }
        fprintf(temp, "%s %.2lf\n", u->username, u->balance);
        fclose(temp);
    }

    printf("User updated successfully\n");

    fclose(original);
    fclose(temp);

    remove(FILE_NAME);
    (void)rename(TEMP_FILE_NAME, FILE_NAME);
}

PUSER CreateNewUser() {
    char username[MAX_USERNAME_LEN] = { '\0' };
    while (1) {
        printf("Please enter a username for a new user: ");
        if (scanf("%50s", username) != 1) {
            printf("Invalid input. Please try again.\n");
        }
        else{
            break;
        }
    }

    char fileLineUsername[MAX_USERNAME_LEN] = { 0 };
    double fileLineBalance;
    FILE* f = NULL;
    OpenFileInRead(&f);

    bool found = false;
    while (fscanf(f, "%49s %lf", fileLineUsername, &fileLineBalance) == 2) {
        if (strcmp(username, fileLineUsername) == 0) {
            found = true;
            break;
        }
    }
    fclose(f);
    if (found) {
        printf("User already exists.");
        (void)_getch();
        ClearInputBuffer();
        return NULL;
    }
    else {
        PUSER u = CreateUser(username, STARTING_BALANCE);
        printf("Welcome %s\nYour balance is: %.2lf\n", u->username, u->balance);
        UpdateUser(u);
        return u;
    }
    return NULL;//this should never happen
}

void DeleteUserFromFile() {
    FILE* original = NULL;
    OpenFileInRead(&original);

    FILE* temp = fopen(TEMP_FILE_NAME, "w");
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
            printf("successfully removed user from the file.");//this is just a check :)
        }
    }

    fclose(original);
    fclose(temp);

    remove(FILE_NAME);
    if (rename(TEMP_FILE_NAME, FILE_NAME) == 0) {
        printf("User deleted successfully");
    }

}

PUSER UserMenu() {
    while (1) {
        WipeScreen();
        PrintAllUsersToScreen();
        printf("What would you like to do?\n"
            "a. Create new user\n"
            "b. Select a user\n"
            "c. Delete a user\n"
            "q. QUIT\n");
        char selection = GetUserInput("abcq");

        switch (selection)
        {
        case'a':
        {
            PUSER u = CreateNewUser();
            if (u == NULL)
                break;
            return u;
        }

        case'b':
        {
            PUSER u = UserSelection();
            if (u == NULL)
                break;
            return u;
        }

        case'c':
            DeleteUserFromFile();
            break;

        case'q':
            exit(EXIT_SUCCESS);
            break;

        }
    }
   
    return NULL; // THIS SHOULDNT HAPPEN, 
    // CREATE NEW USER & SELECT USER SHOULD RETURN A PUSER
    // DELETE USER FROM FILE AND EXIT SHOULD QUIT THE PROGRAM
}