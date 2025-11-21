#define _CRT_SECURE_NO_WARNINGS
#include "worknetting.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//so I made this because how else am i supposed to test the network code when we have the entire rest of the project running

int main(void) {
/*
	CLIENSOCKS CS;
	SERVSOCKS SS;

	
	int a;
	scanf_s("%d", &a);
	if (a == 1) {
		LANStart(&SS, NULL);
		runServ(&SS);
	}
	else {
		LANStart(NULL, &CS);
		runClien(&CS);
	}

	LANEnd();
	return 0;
	*/
/*
WSADATA wsa;
if( (WSAStartup(MAKEWORD(2, 1), &wsa)) != 0)
{
printf("Socket init problem\n");
return false;
}

HOSTENT *hp=NULL;
struct sockaddr_in source;
char hostname[128];

gethostname(hostname, 128);
hp = gethostbyname(hostname);

if(hp == NULL)
{
printf("Local gethostbyname failed: %d\n", WSAGetLastError());
return false;
}

memcpy(&(source.sin_addr),hp->h_addr,hp->h_length);
source.sin_family = hp->h_addrtype;

printf("Local IP Address %s\n", inet_ntoa(source.sin_addr));
*/
	char in[150];
	int a=0;
	FILE* fp = _popen("ipconfig", "r");


	while (strcmp(in, "Wireless LAN adapter Wi-Fi:\n") != 0) {
		fgets(in, sizeof(in), fp);
		printf("not yet matched\n");
	}
	fgets(in, sizeof(in), fp);
	fgets(in, sizeof(in), fp);
	fgets(in, sizeof(in), fp);
	fgets(in, sizeof(in), fp);
	char* ip = strtok(in, ":");
	ip = strtok(NULL, " ");


	printf("%s",ip);
}