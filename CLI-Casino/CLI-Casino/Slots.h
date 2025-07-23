// CLI Casino | Spencer Watkinson - Ricardo Pineda Pelaez - Sebastian Solorzano | CSCN71030
// Interface of the Slots module

// The Slots module is responsible for running the slots menu, allowing users to change their bet amount, see their balance, "run" the game, and quit.
// It includes the logic for spinning the slot machine and calculating balance won or lost.

#pragma once

#include "User.h"

/// Return symbol value multiplier
double GetMultiplier(const char* Symbol);

/// Calculate the amount won based on symbols and bet amount
double CalculateWinnings(const char* S1, const char* S2, const char* s3, int Bet);