#pragma once
#include <stdlib.h>//included for EXIT_FAILURE
#include <stdio.h>//included for fscanf and fprintf
#include <string.h>//included for string reading and writing
#include <stdbool.h>//for booleans
#include "User.h"//included for user struct
#include "IOController.h"//included for input 

#define FILE_NAME			"UserDB.txt"
#define MAX_USERNAME_LEN	25
#define MAX_NAME_LEN		100
#define STARTING_BALANCE	1000

void OpenFileInRead(FILE** f);//function that opens the file in read mode

void OpenFileInWrite(FILE** f);//function that opens the file in write mode

void MakeFile(); //makes file in case it does not exist

void PrintAllUsersToScreen();//print usernames and balance to the consol 

PUSER UserSelection();//asks what profile the user would like to use

void UpdateUser(PUSER u); //updates the one user whos balance changed in the file

void CreateNewUser();//add user to file

void DeleteUserFromFile();

PUSER UserMenu();