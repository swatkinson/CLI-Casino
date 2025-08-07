// CLI Casino | Spencer Watkinson - Ricardo Pineda Pelaez - Sebastian Solorzano | CSCN71030
// Interface of the Integration Test module

#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

#include "IntegrationTest.h"
#include "User.h"
#include "Slots.h"
#include <fcntl.h>

typedef enum { ALL_TEST, SLOT_TEST, POKER_TEST, BLACKJACK_TEST, NO_TEST } TEST_TYPE;

#define DEFAULT_USERNAME "TestUser"

#define SLOTS_TEST_FILE "Slots_IntegrationTest.txt"
#define SLOTS_EXPECTED_BAL 76

#define POKER_TEST_FILE "Poker_IntegrationTest.txt"
#define POKER_EXPECTED_BAL -1

#define BLACKJACK_TEST_FILE "Blackjack_IntegrationTest.txt"
#define BLACKJACK_EXPECTED_BAL -1

#define TENSION 500

void IntegrationTestRunner(TEST_TYPE TestType);

void IntegrationTest(char* TestFile, int ExpectedBalance);

bool RouteStdin(const char* TestFile);

void SilenceStdout(FILE* originalStdout);

void RestoreStdout(FILE* originalStdout);