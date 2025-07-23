// CLI Casino | Spencer Watkinson - Ricardo Pineda Pelaez - Sebastian Solorzano | CSCN71030
// Main run for the CLI Casino game

#include "IOController.h"
#include "User.h"
#include <Windows.h>
#include <time.h>

int main(void) {
	
	srand(time(NULL));		     // Seed the random number generator
	SetConsoleOutputCP(CP_UTF8); //Allow UTF8 Console output

	// Check & run command line args (will exit if there are args, doesnt run main logic)

	// Load users from file

	// Ask user to select a user
	// If user wants to make a new user, prompt for username and give default balance

	// [DEBUG] INITIALIZE TESTING USER BEFORE LOGIN IS COMPLETE
	USER user;
	user.username = "Player1";
	user.balance = 1000; // Starting balance

	// Start the main menu loop
	mainMenu(user);

	// Save user to file 

	return 0;
}