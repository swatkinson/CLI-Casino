// CLI Casino | Spencer Watkinson - Ricardo Pineda Pelaez - Sebastian Solorzano | CSCN71030
// Interface of the Integration Test module

#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

#include "IntegrationTest.h"
#include <fcntl.h>

typedef enum { ALL_TEST, SLOT_TEST, POKER_TEST, BLACKJACK_TEST, NO_TEST } TEST_TYPE;

#define DEFAULT_USERNAME "TestUser"
#define DEFAULT_BALANCE 1000

#define ALL_FLAG "-all"

#define SLOTS_FLAG "-slots"
#define SLOTS_TEST_FILE "Slots_IntegrationTest.txt"
#define SLOTS_EXPECTED_BAL 76

#define POKER_FLAG "-poker"
#define POKER_TEST_FILE "Poker_IntegrationTest.txt"
#define POKER_EXPECTED_BAL -1 // NOT YET IMPLEMENTED

#define BLACKJACK_FLAG "-blackjack"
#define BLACKJACK_TEST_FILE "Blackjack_IntegrationTest.txt"
#define BLACKJACK_EXPECTED_BAL -1 // NOT YET IMPLEMENTED

#define TENSION 500 // Time delay for dramatic effect

void IntegrationTestRunner(TEST_TYPE TestType);

void IntegrationTest(char* TestFile, int ExpectedBalance);

/// Redirects stdin to the given file, returns false if file couldnt be opened
bool RouteStdin(const char* TestFile);	

/// Silences stdout (for running tests without console spam)
void SilenceStdout(FILE* originalStdout);

/// Restores stdout to the console, so we can print test results
void RestoreStdout(FILE* originalStdout);