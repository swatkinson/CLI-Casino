// CLI Casino | Sebastian Solorzano | hehehehehe
//networking interfaceeee!!!! ! ! !!!! !! !
// for all your MP game needs!!!
//supports 2 players only, must be on a local network

#pragma once
#include <stdbool.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS //I had to add this because inet_addr() was giving me issues
#include <winsock2.h>
#include <ws2tcpip.h> 
#pragma comment(lib, "ws2_32.lib") 
//imma be honest I still dont know what half of these do but it is what it is



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

//oh man, i'm gonna have so many seg faults
//using structs here because its the most reasonable way of having multiple things persist
//probably


/*
steps for sockets:
	1. WSA startup
	2. socket
	S3. bind
	S4. listen
	S5. accept
	C3. connect
	4. send/recieve
	5. recieve/send
	6. closesocket
	7. WSAcleanup

LANStart handles 1-2
runServ handles S3-S5
runClien handled C3
LANEnd should handle 6-7, only does 7 atm

4-5 must be handled individually at the game/menu level
*/

//LANStart handles 1 - 2
bool LANStart(PSERVSOCKS ss, PCLIENSOCKS cs);

//runServ handles S3 - S5
bool runServ(PSERVSOCKS ss);
//runClien handles C3
bool runClien(PCLIENSOCKS cs);

//not complete actually
//LANEnd should handle 6 - 7, only does 7 atm
bool LANEnd();

//gets the ip address through a really stupid method that might not work everywhere
//but this whole program was already windows specific so whatever
void getIPAddress(char result[]);


bool inputIPAddress(char result[]);