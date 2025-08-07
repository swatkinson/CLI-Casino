// CLI Casino | Spencer Watkinson - Ricardo Pineda Pelaez - Sebastian Solorzano | CSCN71030
/* Interface of IOController module

IOController is the user input output handler which is responsible for:
- [ ] Command line args, which will allow users to access "godmode" and edit files and player balances directly
- [X] Main menu, which allows users to navigate to the games
- [ ] Profile Management / Login, which allows the user to select specific accounts to play with
*/

#pragma once
#include "User.h"

void MainMenu(PUSER User);

void DisplayMainMenuOptions();

char GetUserInput(char* ValidChars);

void WipeScreen();

void ClearInputBuffer();
