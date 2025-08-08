// CLI Casino | Spencer Watkinson | CSCN71030
//Interface of IOController module

#pragma once
#include "User.h"

void MainMenu(PUSER User);

void DisplayMainMenuOptions(PUSER User);

char GetUserInput(char* ValidChars);

void WipeScreen();

void ClearInputBuffer();

void DisplayWindowBoundary(int width, int height);