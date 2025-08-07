// CLI Casino | Spencer Watkinson - Ricardo Pineda Pelaez - Sebastian Solorzano | CSCN71030
// Main run for the CLI Casino game

#include "IOController.h"
#include "User.h"
#include "FileIO.h"
#include <Windows.h>
#include <time.h>

int main(void) {
	
	srand((unsigned int)time(NULL)); // Seed the random number generator
	SetConsoleOutputCP(CP_UTF8); //Allow UTF8 Console output

	// Check & run command line args (will exit if there are args, doesnt run main logic)

	PUSER user = UserMenu();

	// Start the main menu loop
	MainMenu(user);

	// Save user to file 
	UpdateUser(user);
	// Free user memory
	DeleteUser(user);

	return 0;
}