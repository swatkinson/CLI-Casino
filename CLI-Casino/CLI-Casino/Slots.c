// CLI Casino | Spencer Watkinson - Ricardo Pineda Pelaez - Sebastian Solorzano | CSCN71030
// Implementation of Slots module

#include "Slots.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define SYMBOL_COUNT 5
#define SPIN_STEPS 30
#define DELAY_MS 80

// 2D array of symbols for the slot machine (array of strings, since we are using UTF-8 symbols)
const char* Symbols[] = { "💎", "💲", "🍀", "🪙", "🍒" };

// Returns payout multiplier for a given symbol
double GetMultiplier(const char* symbol) {
    if (strcmp(symbol, "💎") == 0) return 10;
    if (strcmp(symbol, "💲") == 0) return 8;
    if (strcmp(symbol, "🍀") == 0) return 6;
    if (strcmp(symbol, "🪙") == 0) return 4;
    if (strcmp(symbol, "🍒") == 0) return 2;
}

double CalculateWinnings(const char* s1, const char* s2, const char* s3, int Bet) {
    // Winnings if all 3 symbols match
    if (strcmp(s1, s2) == 0 && strcmp(s2, s3) == 0) {
        return Bet * GetMultiplier(s1);
    }

    // Winnings if 2 of 3 symbols match
    if (strcmp(s1, s2) == 0) {
        return Bet * GetMultiplier(s1) / 2;
    }
    else if (strcmp(s1, s3) == 0) {
        return Bet * GetMultiplier(s1) / 2;
    }
    else if (strcmp(s2, s3) == 0) {
        return Bet * GetMultiplier(s2) / 2;
    }

    // No match
    return 0;
}