// CLI Casino | Sebastian Solorzano | hehehehehe
//imp for networking!!!!! to paly multipalyer!!!!!
//imma be honest most of the codee will just be stolen from networks prof (eliott colehill

//I seriously doubt this code is secure or follows proper design principles but I literally just learned it so screw you

//oh mannnn i'm totally forgeting how to do pointers properly
//i blame the professors for net letting me continue to use c for all my courses

//my god I think I'm making a monster


#include "LAN.h"


#include <stdio.h>
#include <Windows.h>




//i'm assuming we *don't* want to crash the whole casino if net connection doesn't work?
bool LANStart(PSERVSOCKS ss, PCLIENSOCKS cs) {

	//startup
	WSADATA wsaData; //THIS CRAP ALMOST CERTAINLY GOES OUT OF SCOPE
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		//still have no idea what this does, especially since it was different in one of his examples?
		printf("cout << ERROR: Failed to start WSA << std::endl;");
		return false;
	}
	printf("succesfull startup\n");


	//socket
	if (cs == NULL) {
		ss->listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (ss->listener == INVALID_SOCKET) {
			printf("cout << ERROR: Failed to create ServerSocket << std::endl;");
			return false;
		}
	}
	else if (ss == NULL) {
		cs->clisok = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (cs->clisok == INVALID_SOCKET) {
			printf("cout << ERROR: Failed to create ServerSocket << std::endl;");
			return false;
		}
	}
	else
		return false;
	//no templates or default params in c, but we DO have pointers!
	//which can be NULL!

	//am I a genius or what? I thought I was gonna have to use void* and enums or something
		//basically, depending on which you want to init, just leave the other as null on the fxn call

	printf("succseful socket creation\n");

}
//I can't believe i'm just copy pasting code, this is a complete betrayal of who i am...!
	//but I literally don't get what half the functions here do
		//even worse, you're on the same level as a python user who doesn't know how anything actually works!!
//also microsof has an official guide to do this and they do it a bit differently? I haven't looked at it properly
	//since I don't get what the functions do anyway
//what's that? read documentation? who has time for that

bool runServ(PSERVSOCKS ss) {
	//bind
	ss->listaddr.sin_family = AF_INET;
	ss->listaddr.sin_addr.s_addr = INADDR_ANY;
	ss->listaddr.sin_port = htons(27000); //who knows what happens if someone else has this port
	if (bind(ss->listener, (struct sockaddr*)&ss->listaddr, sizeof(ss->listaddr)) == SOCKET_ERROR)
	{
		closesocket(ss->listener);
		WSACleanup();
		printf("cout << ERROR: Failed to bind ServerSocket << std::endl;");
		return false;
	}
	printf("succesfull bind\n");


	//listen
	if (listen(ss->listener, 1) == SOCKET_ERROR) { //not sure what the one means, he even used different numbers in his examples
		closesocket(ss->listener);
		WSACleanup();
		printf("cout << ERROR: listen failed to configure ServerSocket << std::endl;");
		return false;
	}
	printf("listening...\n");


	//accept
	SOCKET ConnectionSocket;
	ss->actual = SOCKET_ERROR;
	if ((ss->actual = accept(ss->listener, NULL, NULL)) == SOCKET_ERROR) {
		//why are the 2nd and 3rd parameters on accept NULL ?
		closesocket(ss->listener);
		WSACleanup();
		return false;
	}
	printf("match found!\n");
}

bool runClien(PCLIENSOCKS cs) {
	//connect
	cs->listaddr.sin_family = AF_INET;
	cs->listaddr.sin_port = htons(27000);
	cs->listaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if ((connect(cs->clisok, (struct sockaddr*)&cs->listaddr, sizeof(cs->listaddr))) == SOCKET_ERROR) {
		//I was having some issues at this stage so I added this
		int er = WSAGetLastError();
		printf("err: %d\n", er);

		closesocket(cs->clisok);
		WSACleanup();
		printf("cout << ERROR: Connection attempted failed << std::endl;");
		return false;
	}
	printf("found a connection!\n");
}


bool LANEnd() {
	WSACleanup(); //this works??????????????
	//man, this library is totaly violating some c principles or sometin
	//affects random stuff you don't give it parameters for? doesn't go oos within function calls?
	//this guy's fishy. a real shady figure
	// same with wsagetlasterror() <-- you literally don't give it anything???
		//and it just grabs the error code???
		//this guy's cheating for sure
}
