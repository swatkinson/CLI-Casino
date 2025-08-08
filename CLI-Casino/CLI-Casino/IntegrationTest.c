// CLI Casino | Spencer Watkinson | CSCN71030
// Implementation of the Integration Test module

#include "IntegrationTest.h"

bool IntegrationTestFlag = false;

void IntegrationTestRunner(TEST_TYPE TestType) {
	if (TestType == NO_TEST) {
		return;
	}

	printf("Running Integration Tests:\n");
	IntegrationTestFlag = true; // Makes games run at instant speed
	
	switch (TestType) {

	case ALL_TEST:
		IntegrationTest(SLOTS_TEST_FILE, SLOTS_EXPECTED_BAL);
		IntegrationTest(POKER_TEST_FILE, POKER_EXPECTED_BAL);
		IntegrationTest(BLACKJACK_TEST_FILE, BLACKJACK_EXPECTED_BAL);
		break;

	case SLOT_TEST:
		IntegrationTest(SLOTS_TEST_FILE, SLOTS_EXPECTED_BAL);
		break;

	case POKER_TEST:
		IntegrationTest(POKER_TEST_FILE, POKER_EXPECTED_BAL);
		break;

	case BLACKJACK_TEST:
		IntegrationTest(BLACKJACK_TEST_FILE, BLACKJACK_EXPECTED_BAL);
		break;
	}

	exit(EXIT_SUCCESS); // Exit after running the tests
}

void IntegrationTest(char* TestFile, int ExpectedBalance) {
	Sleep(TENSION);
	printf("%-30s- ", TestFile);
	Sleep(TENSION); // This is for you, Sebastian

	srand(1234567890); // Set the seed of the randomizer so that we get the expected results

	PUSER testUser = CreateUser(DEFAULT_USERNAME, DEFAULT_BALANCE);

	if ( RouteStdin(TestFile) == false) return; // Dont run tests if integration test file didnt open

	// Silence stdout
	FILE* originalStdout = NULL;
	SilenceStdout(originalStdout);

	// Run the program, running the inputs from the test file
	MainMenu(testUser);

	// Restore stdout to console
	RestoreStdout(originalStdout);

	//   v Truncates balance to int for comparison
	if ((int)testUser->balance == ExpectedBalance) {
		printf("✅ Passed - User balance is as expected.\n");
	}
	else {
		printf("❌ Failed - Expected balance %d, but got %d.\n", ExpectedBalance, (int)testUser->balance);
	}

	DeleteUser(testUser); // Free mem
}


bool RouteStdin(const char* TestFile) {
	FILE* file = freopen(TestFile, "r", stdin); // Redirects stdin to read from the specified test file
	if (file == NULL) {
		fprintf(stderr, "❗ Error  - Could not open test file, is it not implemented yet? \n");
		return false;
	}
	return true;
}

void SilenceStdout(FILE* OriginalStdout) {
	OriginalStdout = stdout; // Store pointer to original stdout

	// Route Stdout to NUL (silences it)
	if (freopen("NUL", "w", stdout) == NULL) {
		fprintf(stderr, "❗ Error  - Could not redirect stdout to NUL\n");
		exit(EXIT_FAILURE);
	}

}

void RestoreStdout(FILE* OriginalStdout) {
	if (freopen("CON", "w", stdout) == NULL) {
		fprintf(stderr, "❗ Error  - Could not restore stdout to console\n");
		exit(EXIT_FAILURE);
	}
}