// CLI Casino | Spencer Watkinson | CSCN71030
//Interface of IOController module

#pragma once
#include "User.h"
#include "IntegrationTest.h"

#define EXE_NAME "CLICasino.exe"

// ---------- MENU LOGIC ----------
void MainMenu(PUSER User);

void DisplayMainMenuOptions(PUSER User);

// ---------- COMMAND LINE ARGS ----------
TEST_TYPE CheckCommandLineArgs(int Argc, char* Argv[]);

// ---------- UI HELPER FUNCTIONS ----------
char GetUserInput(char* ValidChars);

void WipeScreen();

void ClearInputBuffer();

void DisplayWindowBoundary(int width, int height);