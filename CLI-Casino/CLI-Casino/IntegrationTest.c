// CLI Casino | Spencer Watkinson - Ricardo Pineda Pelaez - Sebastian Solorzano | CSCN71030
// Implementation of the Integration Test module

#include "IntegrationTest.h"

extern bool IntegrationTestFlag;

void IntegrationTestRunner(char SelectedTest) {

	if (SelectedTest == '\0') {
		return;
	}

	IntegrationTestFlag = true;
	srand(1234567890); // Set the seed of the randomizer so that we get the expected results

	switch (SelectedTest) {

	case 'a': // All Integration Tests
		printf("Running All Integration Tests...\n");
		SlotsIntegrationTest();

		fgetc(stdin); // Wait for user input to see results
		break;

	case 's': // Slots Integration Test
		printf("Running Slots Integration Test...\n");
		SlotsIntegrationTest(SLOTS_TEST_FILE);
		break;

	}

	exit(EXIT_SUCCESS); // Exit after running the tests
}

void SlotsIntegrationTest() {
	PUSER testUser = CreateUser(DEFAULT_USERNAME, 1000);
	double expectedBalance = 76; // Expected balance after the test

	RouteStdin(SLOTS_TEST_FILE);

	// Run the program, running the inputs from the test file
	MainMenu(testUser);

	if ((int)testUser->balance == expectedBalance) {
		printf("✅ Slots Integration Test Passed: User balance is as expected.\n");
	}
	else {
		printf("❌ Slots Integration Test Failed: Expected balance %lf, but got %lf.\n", expectedBalance, testUser->balance);
	}

	DeleteUser(testUser); // Free user mem
}


void RouteStdin(const char* TestFile) {
	freopen(TestFile, "r", stdin); // Redirects stdin to read from the specified test file
}