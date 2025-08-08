// CLI Casino | Spencer Watkinson - Ricardo Pineda Pelaez - Sebastian Solorzano | CSCN71030
// Main run for the CLI Casino game

#include "IOController.h"
#include "User.h"
#include <Windows.h>
#include <time.h>
#include "IntegrationTest.h"
#include <stdbool.h>

int main(void) {
	srand((unsigned int)time(NULL)); // Seed the random number generator
	SetConsoleOutputCP(CP_UTF8); //Allow UTF8 Console output
	WipeScreen(); // Clear the console screen

	// Check & run command line args (will exit if there are args, doesnt run main logic)

	// Run integration tests
	//IntegrationTestRunner( ALL_TEST ); // Switch this to the correct TEST_TYPE to run tests, will be changed to command line args in that branch.

	// User Selection

	// [DEBUG] INITIALIZE TESTING USER BEFORE LOGIN IS COMPLETE
	PUSER user = CreateUser("User1", 1000); // Starting balance

	// Start the main menu loop
	MainMenu(user);

	// Save user to file 

	// Free user memory
	DeleteUser(user);

	return 0;
}