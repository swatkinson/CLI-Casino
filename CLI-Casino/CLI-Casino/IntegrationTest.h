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

#define DEFAULT_USERNAME "TestUser"
#define SLOTS_TEST_FILE "Slots_IntegrationTest.txt"

void IntegrationTestRunner(char SelectedTest);

void SlotsIntegrationTest();

void RouteStdin(const char* TestFile);