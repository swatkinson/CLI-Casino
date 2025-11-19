#pragma once
#include <stdbool.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS //I had to add this because inet_addr() was giving me issues
#include <winsock2.h>
#include <ws2tcpip.h> 
#pragma comment(lib, "ws2_32.lib") 

typedef struct servsockets {
	SOCKET listener;
	SOCKET actual;
	struct sockaddr_in listaddr; //?
	//still dont know what this is ngl
}SERVSOCKS, * PSERVSOCKS;

typedef struct cliensockets {
	SOCKET clisok;
	struct sockaddr_in listaddr;// ???
	//even less sure what this does
}CLIENSOCKS, * PCLIENSOCKS;


bool LANStart(PSERVSOCKS ss, PCLIENSOCKS cs);
bool LANEnd();

bool runClien(PCLIENSOCKS cs);
bool runServ(PSERVSOCKS ss);