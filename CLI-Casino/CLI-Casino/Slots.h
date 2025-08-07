// CLI Casino | Spencer Watkinson - Ricardo Pineda Pelaez - Sebastian Solorzano | CSCN71030
// Interface of the Slots module

// The Slots module is responsible for running the slots menu, allowing users to change their bet amount, see their balance, "run" the game, and quit.
// It includes the logic for spinning the slot machine and calculating balance won or lost.

#pragma once
#define _CRT_SECURE_NO_WARNINGS

#define SYMBOL_COUNT 5
#define INITIAL_BET 50

// Slot Animation Numbers
#define SPIN_STEPS 20
#define SPIN_DELAY 50

// Symbol Modifiers - This setup gives a slightly positive win amount, approx 104% return per pull
#define DIAMOND_MODIFIER    15
#define DOLLAR_MODIFIER     8
#define CLOVER_MODIFIER     6
#define COIN_MODIFIER       4
#define CHERRY_MODIFIER     2

#define DIAMOND_RARITY		1   // Lower number = rarer
#define DOLLAR_RARITY		2
#define CLOVER_RARITY		3
#define COIN_RARITY			3
#define CHERRY_RARITY		4

#define DOUBLE_DIVISOR      3

#include "User.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "IOController.h"
#include <stdbool.h>

// ----------- HELPER FUNCTIONS ----------

/// Returns payout multiplier for a given symbol
double GetMultiplier(const char* Symbol);

/// Returns the winnings based on the symbols and the bet
double CalculateWinnings(const char* S1, const char* S2, const char* s3, int Bet);

/// Gets a random symbol from the symbols array, weighted
const char* GetRandomSymbol();

// ---------- SLOTS LOGIC FUNCTIONS ----------

/// Looping slots menu - Handles pathing
void SlotsGame(PUSER User);

/// Runs the slot machine, returns the winnings based on the bet input
double RunSlots(int Bet);

// ---------- USER INTERFACE ----------

/// Slots menu display
void PrintSlotsMenu(int Bet);

/// Changes the user info in the slots menu header
void UpdateSlotsMenu(PUSER User, int Bet);

/// Runs the slot machine spinning animation
void SlotMachineAnimation(const char* S1, const char* S2, const char* S3);

/// Draws the static slot machine with the 3 symbols passed
void PrintSlotMachine(int Bet);

/// Moves cursor to the input line, and clears all the lines underneath it
void MoveCursorToInput();

/// Print the winnings or try again message under the slot machine
void DisplayWinnings(double Winnings);

/// Printf but prints out status messages underneath the slot machine
void PrintUnderSlots(const char* format, ...);