/* This is the console executable that makes use of the WordGame class
This acts as the view in an MVC pattern, and is responsible for all 
user interaction. For game logic see the FWordGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include "FWordGame.h"

// substitutions to make synax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void printIntro();
void playGame();
FText getValidGuess(int32 currentTry);
bool playAgain();
void printGameSummary();

FWordGame WordGame; // instantiate a new game that is reused accross plays

// the entry point for our application
 int32 main()
{
	do
	{
		printIntro();
		playGame();		
	} 
	while (playAgain() == 1);		
	return 0; // close the command line window
}

// introduce the game
void printIntro()
{
	std::cout << "Welcome to the word game!\n\n";
	std::cout << "Can you guess the " << WordGame.getHiddenWordLength();
	std::cout << " letter word I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// runs a single game to completion
void playGame()
{	
	WordGame.reset();
	int32 maxTries = WordGame.getMaxTries();
	int32 currentTry = WordGame.getCurrentTry();
	// loop for the number of turns the player is allowed
	while (!WordGame.isGameWon() && WordGame.getCurrentTry() <= maxTries)
	{		
		FText guess = getValidGuess(currentTry); // get the player's validated guess		
		FWordMatchCount wordMatchCount = WordGame.submitValidGuess(guess); // sumbit valid guess and receive count
		// print letter-match results
		std::cout << "Complete Matches: " << wordMatchCount.completeMatch;
		std::cout << std::endl;
		std::cout << "Partial Matches: " << wordMatchCount.partialMatch;
		std::cout << std::endl << std::endl;
		currentTry++;
	}
	printGameSummary();
	return;
}

// loop continually until the player gives a valid guess
FText getValidGuess(int32 currentTry) 
{	
	EWordValidity Status = EWordValidity::invalid_status;
	FText Guess = "";
	do {
		// get the player's guess
		std::cout << "Try " << currentTry << " of " << WordGame.getMaxTries();
		std::cout << " - Enter your guess: ";		
		std::getline(std::cin, Guess);
		// check the validity of the guess
		Status = WordGame.checkValidity(Guess);		
		switch (Status) // prompt the player on invalid input
		{
		case EWordValidity::NotIsogram:
			std::cout << "Please enter a single word with no repeated letters.\n\n";
			break;
		case EWordValidity::WrongLength:
			std::cout << "Please enter a " << WordGame.getHiddenWordLength() << " letter word.\n\n";
			break;
		case EWordValidity::NotLowerCase:
			std::cout << "Please enter all lower case letters.\n\n";
			break;
		default:			
			break;
		}
	} while (Status != EWordValidity::OK); // loop until we get valid input	
	std::cout << std::endl;
	return Guess;
}

// ask the player if they want to play again
bool playAgain()
{
	std::cout << "Do you want to play again?";
	std::cout << std::endl;
	FText response = "";
	std::getline(std::cin, response);
	return (response[0] == 'y') || (response[0] == 'Y');
}

// tell the player if they have won or not
void printGameSummary()
{
	if (WordGame.isGameWon())
	{
		std::cout << "YOU WIN!\n";
	}
	else
	{
		std::cout << "YOU LOSE!\n";
	}
}
