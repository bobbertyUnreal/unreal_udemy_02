# pragma once

#include "FWordGame.h"
#include <map>

// substitutions to make synax Unreal friendly
#define TMap std::map
using int32 = int;

FWordGame::FWordGame() { reset(); } // default constructor

int32 FWordGame::getCurrentTry() const { return currentTry; }

int32 FWordGame::getHiddenWordLength() const { return hiddenWord.length(); }

bool FWordGame::isGameWon() const { return bGameIsWon; }

int32 FWordGame::getMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[hiddenWord.length()]; 
}

// reset the game starting conditions
void FWordGame::reset()
{
	const FString HIDDEN_WORD = "ant"; // this must be an isogram
	hiddenWord = HIDDEN_WORD;
	currentTry = 1;
	bGameIsWon = false;
	return;
}

// check the validity of a guess
EWordValidity FWordGame::checkValidity(FString guess) const
{
	if (!isIsogram(guess)) // If not an isogram
	{
		return EWordValidity::NotIsogram;
	}
	else if (!isLowerCase(guess)) // If not all lower case
	{
		return EWordValidity::NotLowerCase;
	}
	else if (guess.length() != getHiddenWordLength()) // If guess length is wrong
	{
		return EWordValidity::WrongLength;
	}
	else 
	{
		return EWordValidity::OK;
	}
}

// receives a valid guess, increments turn, returns count
FWordMatchCount FWordGame::submitValidGuess(FString guess)
{
	currentTry++;
	FWordMatchCount wordMatchCount;
	int32 wordLength = hiddenWord.length();
	int32 guessLength = guess.length();
	// loop through each letter in the hidden word
	for (int32 i = 0; i < wordLength; i++) {
		// loop through each letter in the guess
		for (int32 j = 0; j < guessLength; j++) {
			// compare the characters and find matches
			if (hiddenWord[i] == guess[j]) {
				if (i == j)	{
					wordMatchCount.completeMatch++;
				} else {
					wordMatchCount.partialMatch++;
				}
			}
		}			
	}
	if (wordMatchCount.completeMatch == wordLength)
	{
		bGameIsWon = true;
	}
	return wordMatchCount;
}

bool FWordGame::isIsogram(FString guess) const
{
	if (guess.length() <= 1) { return true; }

	TMap<char, bool> letterSeen;
	for (auto letter : guess)
	{
		letter = tolower(letter);
		if (letterSeen[letter])
		{
			return false;
		} else {
			letterSeen[letter] = true;
		}
	}
	return true;
}

bool FWordGame::isLowerCase(FString guess) const
{
	for (auto letter : guess)
	{
		if (!islower(letter))
		{
			return false;
		}
	}
	return true;
}
