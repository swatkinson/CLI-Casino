# CLI-Casino
Poker, Blackjack, and Slots - Locally in your terminal

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
### Function Descriptions
### Requirements

## Module - Cards
### Module Description
### Function Descriptions
### Requirements

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
### Function Descriptions
### Requirements

## Module - Blackjack
### Module Description
### Function Descriptions
### Requirements
