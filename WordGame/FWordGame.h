/* The game logic (no view code or direct user interaction). 
The game is a simple guess the word game based on mastermind 
*/

#pragma once

#include <string>

// substitutions to make synax Unreal friendly
using FString = std::string;
using int32 = int;

struct FWordMatchCount
{
	int32 completeMatch = 0;
	int32 partialMatch = 0;
};

enum class EWordValidity
{
	invalid_status,
	OK,
	NotIsogram,
	WrongLength,
	NotLowerCase
};

class FWordGame
{
public:	
	FWordGame(); //constructor

	int32 getMaxTries() const;
	int32 getCurrentTry() const;
	int32 getHiddenWordLength() const;
	bool isGameWon() const;
	EWordValidity checkValidity(FString) const;

	void reset();	
	FWordMatchCount submitValidGuess(FString);

private:
	// see constructor for initialisation
	int32 currentTry;
	FString hiddenWord;
	bool bGameIsWon;

	bool isIsogram(FString) const;
	bool isLowerCase(FString) const;
};