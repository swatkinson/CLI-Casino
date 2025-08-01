// CLI Casino | Spencer Watkinson - Ricardo Pineda Pelaez - Sebastian Solorzano | CSCN71030
// Interface of the Slots module

// The Slots module is responsible for running the slots menu, allowing users to change their bet amount, see their balance, "run" the game, and quit.
// It includes the logic for spinning the slot machine and calculating balance won or lost.

#pragma once

#include "User.h"

// ----------- HELPER FUNCTIONS ----------

/// Returns payout multiplier for a given symbol
double GetMultiplier(const char* Symbol);

/// Returns the winnings based on the symbols and the bet
double CalculateWinnings(const char* S1, const char* S2, const char* s3, int Bet);

/// Gets a random symbol from the symbols array, weighted
char* GetRandomSymbol();

// ---------- SLOTS LOGIC FUNCTIONS ----------

/// Runs the slot machine, returns the winnings based on the bet input
double RunSlots(int Bet);

// ---------- USER INTERFACE ----------

/// Looping slots menu - Handles the user interface and pathing
USER SlotsGame(USER User);

/// Slots menu display
void PrintSlotsMenu(USER User, int Bet);

/// Runs the slot machine spinning animation
void SlotMachineAnimation(const char* S1, const char* S2, const char* S3);

/// Draws the static slot machine with the 3 symbols passed
void PrintSlotMachine(const char* S1, const char* S2, const char* S3);