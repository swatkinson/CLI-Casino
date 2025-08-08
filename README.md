# CLI-Casino
Poker, Blackjack, and Slots - Locally in your terminal

# Usage
Works out of the box on Visual Studio.  
In the terminal:
- You must compile the project first
- and you must **move the .txt files (deck, and integration tests) from the project file to the build file**!

To run integration tests, either change the line in main, or run with command line arguments in the terminal (-all, -poker).  
Writing './CLICasino.exe -help' prints the usage, if you want a list of all of the flags.


# Requirements & Design
## Module - IOController
### Module Description
IOController is the user input output handler which is responsible for:
- Command line args, which will allow users to access "godmode" and edit files and player balances directly
- Main menu, which allows users to navigate to the games
- Profile Management/Login, which allows the user to select specific accounts to play with
  
### Function Descriptions
/// Gets passed the command line arguments, and assesses if the user is trying to access the program with arguments, or is loading the program to play normally  
/// If passed with arguments, validate if correct, and run respective functions (like updating balances, etc.)  
CommandLineArgHandler(argc, argv)

/// Called from godmode, loads users to memory, checks if passed username is valid, updates their balance with passed value  
UpdateBalance()

/// Call FileIO to load all users into memory  
/// Print all of the existing usernames to screen, and ask the user to pick an account to login to or to create a new account  
UserLogin()

/// Create new default user struct, and ask for a name for the new user, and give it the default starting balance.  
CreateNewUser()

/// Main navigation for the CLI Casino, handles account options, entering games, and calling Quit(). Endless loop  
MainMenu()

/// Saves all loaded user data to file, and exits cleanly  
Quit()


### Requirements
REQ-IOC-001 - The IOController MUST call the fileIO module to load user data on login and save it after any changes.  
REQ-IOC-002 - The IOController MUST prompt the user to enter a username and attempt to load the profile using the fileIO module; if the profile does not exist, it MUST offer to create a new one.  
REQ-IOC-003 - The IOController MUST display the main menu with options to play a game, manage profiles, or exit.  
REQ-IOC-004 - The IOController MUST handle command line arguments such as "--addbalance" to enable special access like editing user profiles and balances.  
REQ-IOC-005 - The IOController MUST allow the user to navigate the menu using keyboard input and trigger the appropriate actions.  
REQ-IOC-006 - The IOController MUST allow the user to select a game and MUST call the appropriate game module, passing the user data and receiving updated balance information.  
REQ-IOC-007 - The IOController MUST validate user input and handle invalid or unexpected input without crashing the program.  
REQ-IOC-008 - The IOController MUST delegate all file and game logic to external modules and MUST only coordinate control flow between them.

## Module - FileIO
### Module Description
This module has to read a file (if it exits, if it doesnt make it), and save all users (usernamen and balance) to an linked list.

### Function Descriptions
///Reads the file, and calls AddUser() to add all users to a linked list
ReadFile()

///Takes in a username and balance and adds user to a linked list.
AddUser(char* username, double balance)

///It will take in a user, and delete it from the linked list.
DeleteUser(USER u)

### Requirements
REQ-FILEIO-001 – The FileIO module MUST check for the existence of the user file on startup and create a new file if it does not exist.

REQ-FILEIO-002 – The FileIO module MUST read all user data (username and balance) from the file and load it into a linked list on initialization.

REQ-FILEIO-003 – The FileIO module MUST call AddUser() for each user entry found in the file to populate the linked list.

REQ-FILEIO-004 – The FileIO module MUST allow adding a new user with a username and balance to the linked list using AddUser().

REQ-FILEIO-005 – The FileIO module MUST allow deleting an existing user from the linked list using DeleteUser().

REQ-FILEIO-006 – The FileIO module MUST save all current users from the linked list back to the file when requested or on program exit.

REQ-FILEIO-007 – The FileIO module MUST handle file read and write errors gracefully, ensuring no data corruption occurs.

## Module - Cards
### Module Description
The cards module is for playing cards. it is responsible for:
    -card structure
    -initializing a deck of cards
    -drawing and discarding cards
    -printing hands to the screen
### Function Descriptions
//initializes a deck of 52 cards in the drawpile
void initDeck(FULLDECK fd);

//reshuffles draw and discard piles
void shuffle(FULLDECK fd);

//removes card from drawpile and sends to discardpile
void discard(FULLDECK fd, CARD c);

//takes a card from drawpile and returns a copy of it. decknode is sent to discard pile
CARD drawCard(FULLDECK fd);

//draws hand to screen
void displayHand(CARD d[], int handsize);

//frees the deck linke list
void destroyDeck(FULLDECK fd);

### Requirements
REQ-CARDS-001 - the cards module must be able to initialize a deck of 52 cards to be used by other card games
REQ-CARDS-002 - the cards module must be able to draw individual cards from the deck and return them
REQ-CARDS-003 - the cards module must be able to remove cards from the deck so that they cannot be drawn multiple times
REQ-CARDS-004 - the cards module must be able to access the card art stored in a separate file in order to draw cards
REQ-CARDS-005 - the cards module must be able to display a hand of multiple cards on the screen next to each other 
REQ-CARDS-006 - the cards module must be able to shuffle the discard and draw piles to return the deck to its initial state

## Module - Slots
### Module Description
The Slots module is responsible for running the slots menu, allowing users to change their bet amount, see their balance, "run" the game, and quit.  
It includes the logic for spinning the slot machine and calculating balance won or lost.

### Function Descriptions
/// Allows user to choose between options with keyboard entries, such as running the machine, changing the bet, and leaving  
SlotsMenu()

/// Runs the slot machine animation, gets 3 random symbols/values, and calculates the winnings to add to the balance  
RunSlotMachine(betAmount)

/// Graphical display of slot machine  
DisplaySlots()

/// Allows user to change their bet amount, between a min and max value  
ChangeBet()

/// Quits slots, and returns to the main menu, passing back the users info  
ExitToMainMenu()

### Requirements
REQ-SLOTS-001 - The Slots module MUST provide a menu interface allowing the user to run the slot machine, change their bet amount, or exit back to the main menu.  
REQ-SLOTS-002 - The Slots module MUST accept and respond to keyboard input for all menu navigation and option selection.  
REQ-SLOTS-003 - The Slots module MUST allow the user to run the slot machine using the current bet amount.  
REQ-SLOTS-004 - The Slots module MUST generate three random symbols or values to simulate a spin when the machine is run.  
REQ-SLOTS-005 - The Slots module MUST calculate the user’s winnings or losses based on the result of the spin and adjust their balance accordingly.  
REQ-SLOTS-006 - The Slots module MUST display the slot machine visually using a simple text-based graphic layout.  
REQ-SLOTS-007 - The Slots module MUST allow the user to change their bet amount, enforcing both a minimum and maximum allowed value.  
REQ-SLOTS-008 - The Slots module MUST validate the entered bet amount to ensure it is numeric, within range, and not greater than the user’s current balance.  
REQ-SLOTS-009 - The Slots module MUST display the user’s current balance and bet amount during gameplay.  
REQ-SLOTS-010 - The Slots module MUST exit cleanly when the user chooses to quit, returning to the main menu and passing the updated user data back to the IOController.

## Module - Poker
### Module Description
The Poker module is responsible for running the Poker game. Ie. calculate the value of different hands, compare different hands, discarde X cards, deal x cards, betting system, and quit the game.

### Function Descriptions
///Takes in a poker hand (5 cards) and checks what the highest possible hand is, it will make sure it is returning the highest possible hand by checking from highest value to lowest, and exit the functions as soon as it meets the requirements for a hand
CalculateHandValue(CARD* c)

///Takes in 2 arrays of 5 cards, aswell as their hand type (from CalculateHandValue()). It will compare the two hand values, if one is higher it will select that one as the winner, if they are both the same, it will do more in depth checks (if both hands have a single pair, but one of the two has a pair of As and the other a pair of 5s it will select the As as winner) 
CompareHands()

///It will take in an arry of 5 cards, ask the user how many and which cards they want to discard 0-4, and it will call discard(), from the card module, to add those cards to the discard pile.
DiscardXCards(CARD* c)

///It will take in an array of cards, as well as how many cards it must deal (if at the bigining of the game 5, if after discard, however many cards were discarded), it will call drawCard(), and ask fro how ever many cards it needs.
DealXCards(CARD* c, int Num)

///It will allow the user to bet however micht they want.
Bet()

///Quits the module
Quit()
### Requirements
REQ-POKER-001 – The Poker module MUST evaluate any 5-card hand and determine the highest possible Poker hand based on standard hand rankings.

REQ-POKER-002 – The Poker module MUST compare two 5-card hands and declare a winner, using tiebreakers if both hands have the same rank.

REQ-POKER-003 – The Poker module MUST allow the player to select 0–4 cards to discard from their hand.

REQ-POKER-004 – The Poker module MUST deal a specified number of cards to the player to replace any discarded cards.

REQ-POKER-005 – The Poker module MUST support a betting system where the player can place, raise, or fold bets during gameplay.

REQ-POKER-006 – The Poker module MUST accept and respond to keyboard input for all menu navigation and in-game actions.

REQ-POKER-007 – The Poker module MUST call the Card module’s drawCard() function when dealing new cards.

REQ-POKER-008 – The Poker module MUST call the Card module’s discard() function to add discarded cards to the discard pile.

REQ-POKER-009 – The Poker module MUST allow the player to quit the game at any time and return to the main menu.

REQ-POKER-010 – The Poker module MUST validate all user inputs (e.g., bet amounts, card selections) and handle invalid inputs gracefully.

## Module - Blackjack
### Module Description
the blackjack module is responsible for playing the game of blackjack. players should be able to bet money, play the game, quit the game etc.
### Function Descriptions

//main loop that runs the game. calls other functions
runBJREQ

//calculates the score of given cards. check if player busted
scoreHand

//compares the scores of two players (dealer and player), and checks for blackjack(21)
compareScores

//allows user to input a bet, subtracts from balance
bet

//plays the dealers turn. calls regular game action functions
dealerTurn

//game actions:
//draws card
hit
//skips your turn
stand
//splits your cards into 2 hands, splits bet
split
//doubles bet, draw a single card
double down
//quit out and keep a portion of bet
surrender

### Requirements
REQ-BJ-001 - the blackjack module must be able to accept player bets and access/modify their balance
REQ-BJ-002 - the blackjack module must be able to score 2+ card hands and determine whether they are over 21 or not
REQ-BJ-003 - the blackjack module must be able to compare the scores of two players and determine the winner of the round
REQ-BJ-004 - the blackjack module must let the player make decisions during the round and act appropriately
REQ-BJ-005 - the blackjack module must let the player quit the game and return to the main menu
