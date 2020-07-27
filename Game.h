#pragma once
#include "Grid.h"

/* 
	Class: Game
	Description: Models a game of GreenVsRed
*/

class Game
{
	Grid gameGrid;
	unsigned int currentGeneration;
	unsigned int targetGeneration; // The generation up to which the game will be simulated
	Cell2D trackedCell; // The cell to track

	// The number of generations in which the tracked cell was green (including 0 and targetGeneration)
	unsigned int trackedCellGreenTimes;
	
	bool isInitialized; // Is the game fully initialized

	Game(const Game& other) = delete; // Forbid copying
	Game& operator= (const Game& other) = delete; // Forbid assignment

public:
	// Constructors
	Game() : currentGeneration(0), targetGeneration(0), trackedCellGreenTimes(0), isInitialized(false) {}
	
	// Getters
	unsigned int GetTrackedCellGreenTimes() const;

	// Utilities
	bool Initialize(); // Initialize the game
	bool Play(); // Play the game up to the targetGeneration included
};