// CLI Casino | Spencer Watkinson - Ricardo Pineda Pelaez - Sebastian Solorzano | CSCN71030

#pragma once
#define USERNAME_MAX 50

typedef struct user {
	char username[USERNAME_MAX];
	double balance;
} USER, *PUSER;

PUSER CreateUser(char* Username, double Balance);

void DeleteUser(PUSER User);
