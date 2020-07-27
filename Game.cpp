#include "Game.h"
#include <iostream>
#include <string>

const unsigned short CELL_DIMENSIONS = 2;

// Try to parse a string argument to an integer
bool IsValidInteger(const std::string& str, int& result)
{
	if (str.empty())
	{
		return false;
	}

	const size_t strLen = str.length();
	/*	A string is valid if the only non-digit character is a "," at the end of the string.
		When a "," is present, the string must be of length > 1
	*/
	for (size_t i = 0; i < strLen; i++)
	{
		if (!std::isdigit(str[i]) && !(i == strLen - 1 && str[i] == ',' && strLen > 1))
		{
			return false;
		}
	}

	try
	{
		result = std::stoi(str);
	}
	catch (std::exception& e)
	{
		return false;
	}

	return true;
}

// Check if the coordinates of a cell are within a given grid
bool IsValidCell(const unsigned short gridWidth, const unsigned short gridHeight, const Cell2D& cell)
{
	unsigned short x = cell.GetX();
	unsigned short y = cell.GetY();
	return x >= 0 && x < gridWidth && y >= 0 && y < gridHeight;
}

bool Game::Initialize()
{
	// Initialize the game grid
	if (this->gameGrid.Initialize() != 0)
	{
		std::cerr << "Game grid initialization failed\n";
		return false;
	}

	// Read the coordinates of the cell to be tracked
	std::string input;
	int parsedInput;

	for (size_t i = 0; i < CELL_DIMENSIONS; i++)
	{
		std::cin >> input;
		if (!IsValidInteger(input, parsedInput))
		{
			std::cerr << "Invalid argument" << std::endl;
			return false;
		}

		if (parsedInput >= 0 && parsedInput <= std::numeric_limits<unsigned short>::max())
		{
			i % 2 == 0 ? this->trackedCell.SetX(parsedInput) : this->trackedCell.SetY(parsedInput);
		}
		else
		{
			std::cerr << "Argument out of range" << std::endl;
			return false;
		}
	}

	// Validate the coordinates of the tracked cell
	if (!IsValidCell(this->gameGrid.GetWidth(), this->gameGrid.GetHeight(), this->trackedCell))
	{
		std::cerr << "Invalid cell coordinates" << std::endl;
		return false;
	}

	// Set the tracked cell value according to the input grid
	this->trackedCell.SetValue(this->gameGrid.GetCellValue(this->trackedCell));

	// Read the number of generations to be simulated
	std::cin >> input;
	if (!IsValidInteger(input, parsedInput))
	{
		std::cerr << "Argument is not a valid integer" << std::endl;
		return false;
	}
	else if (parsedInput < 0)
	{
		std::cerr << "Positive integer required" << std::endl;
		return false;
	}

	this->targetGeneration = parsedInput;
	this->isInitialized = true;

	return true;
}

bool Game::Play()
{
	if (!this->isInitialized)
	{
		std::cerr << "The game is not initialized" << std::endl;
		return false;
	}

	while (this->currentGeneration <= this->targetGeneration)
	{
		if (this->gameGrid.GetCellValue(this->trackedCell) == '1')
		{
			this->trackedCellGreenTimes++;
		}

		if (this->gameGrid.DeriveNextGeneration() == false)
		{
			std::cerr << "Failed calculating generation " << this->currentGeneration << std::endl;
			return false;
		}

		this->currentGeneration++;
	}

	return true;
}

unsigned int Game::GetTrackedCellGreenTimes() const
{
	if (this->isInitialized && this->currentGeneration >= this->targetGeneration)
	{
		return this->trackedCellGreenTimes;
	}
	else if (!this->isInitialized)
	{
		std::cerr << "The game is not initialized" << std::endl;
	}
	else
	{
		std::cerr << "The game is not played up to generation " << this->targetGeneration << std::endl;
	}

	return (std::numeric_limits<unsigned int>::max());
}
