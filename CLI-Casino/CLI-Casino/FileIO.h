//CLI Casino | Ricardo Pineda Pelaez | CSCN71030
//Interface of the File I/O module

#pragma once
#include <conio.h>
#include <stdlib.h>//included for EXIT_FAILURE
#include <stdio.h>//included for fscanf and fprintf
#include <string.h>//included for string reading and writing
#include <stdbool.h>//for booleans
#include "User.h"//included for user struct
#include "IOController.h"//included for input 

#define TEMP_FILE_NAME		"temp.txt"
#define FILE_NAME			"UserDB.txt"
#define MAX_USERNAME_LEN	50
#define STARTING_BALANCE	1000

void OpenFileInRead(FILE** f);//function that opens the file in read mode

void OpenFileInWrite(FILE** f);//function that opens the file in write mode

void MakeFile(); //makes file in case it does not exist

void PrintAllUsersToScreen();//print usernames and balance to the consol 

PUSER UserSelection();//asks what profile the user would like to use

void UpdateUser(PUSER u); //updates the one user whos balance changed in the file

PUSER CreateNewUser();//add user to file

void DeleteUserFromFile();//deletes user from file

PUSER UserMenu();//main menue for the user to select a user to play as, create a user, delete a user, or quit the program.