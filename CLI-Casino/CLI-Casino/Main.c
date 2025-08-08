// CLI Casino | Spencer Watkinson - Ricardo Pineda Pelaez - Sebastian Solorzano | CSCN71030
// Main run for the CLI Casino game

#include "IOController.h"
#include "User.h"
#include "FileIO.h"
#include <Windows.h>
#include <time.h>
#include "IntegrationTest.h"
#include <stdbool.h>

int main(int argc, char* argv[]) {
	srand((unsigned int)time(NULL)); // Seed the random number generator
	SetConsoleOutputCP(CP_UTF8); //Allow UTF8 Console output
	
	// Check & run command line args (will exit if there are args, doesnt run main logic)
	TEST_TYPE selectedTests = CheckCommandLineArgs(argc, argv);
	//selectedTests = ALL_TEST; // [DEBUG] If you're too lazy to run the exe through terminal, you can quick run the tests by uncommenting this line

	WipeScreen(); // Clear the console screen

	// Run integration tests
	IntegrationTestRunner( selectedTests );

  // User Selection
	PUSER user = UserMenu();

	ClearInputBuffer();

	// Start the main menu loop
	MainMenu(user);

	// Save user to file 
	UpdateUser(user);
	// Free user memory
	DeleteUser(user);

	return 0;
}