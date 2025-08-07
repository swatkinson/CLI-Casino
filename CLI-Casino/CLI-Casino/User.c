// CLI Casino | Spencer Watkinson - Ricardo Pineda Pelaez - Sebastian Solorzano | CSCN71030

#define _CRT_SECURE_NO_WARNINGS
#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PUSER CreateUser(char* Username, double Balance) {
	PUSER newUser = (PUSER)malloc(sizeof(USER));
	if (newUser == NULL) {
		fprintf(stderr, "Memory allocation failed for new user.\n");
		return NULL;
	}

	// String copy (the steve way)
	strncpy(newUser->username, Username, sizeof(newUser->username) - 1);
	newUser->username[sizeof(newUser->username) - 1] = '\0';

	newUser->balance = Balance;

	return newUser;
}

void DeleteUser(PUSER User) {
	if (User != NULL) {
		free(User);
	}
}