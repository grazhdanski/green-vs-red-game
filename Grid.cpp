#include "Grid.h"
#include <string>
#include <iostream>
#include <vector>
#include <unordered_set>

const unsigned short GRID_MIN_SIZE = 1;
const unsigned short GRID_MAX_SIZE = 999;
const unsigned short GRID_DIMENSIONS = 2;

// The required number of green neighbours in order to apply rule 1 or rule 3 respectively
// Note: Rules 2 and 4 are not considered in the calculations, since they do not affect the generation
const std::unordered_set<unsigned short> rule1PossibleValues({ 3, 6 });
const std::unordered_set<unsigned short> rule3PossibleValues({ 0, 1, 4, 5, 7, 8 });

// Try to parse a string parameter to an unsigned short in a fixed range
bool IsValidShortInRange(const std::string& str, unsigned short& result)
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

	int number;
	try
	{
		number = std::stoi(str);
	}
	catch(std::exception& e)
	{
		return false;
	}

	result = (unsigned short)number;
	return (number >= GRID_MIN_SIZE && number <= GRID_MAX_SIZE);
}

/* Check if the coordinates (x, y) are valid coordinates of a cell in the grid and that the grid is initialized. 
 Internal use only */
bool Grid::IsValidCell(const int x, const int y) const
{
	return this->cells != nullptr && x >= 0 && x < this->width && y >= 0 && y < this->height;
}

// Count the green neighbours of a given cell. Assumes that the grid is initialized.
unsigned short Grid::CountGreenNeighbours(const int x, const int y)
{
	unsigned short greenCount = 0;

	// Check each of the 8 possible neighbours of a cell
	for (int row = -1; row <= 1; row++)
	{
		for (int col = -1; col <= 1; col++)
		{
			if (row == 0 && col == 0) // Ignore the cell (x, y)
			{
				continue;
			}

			if (IsValidCell(x + col, y + row))
			{
				if (this->cells[y + row][x + col].GetValue() == '1')
				{
					greenCount++;
				}
			}
		}
	}

	return greenCount;
}

char Grid::GetCellValue(const Cell2D& cell) const
{
	unsigned short x = cell.GetX();
	unsigned short y = cell.GetY();

	if (IsValidCell(x, y))
	{
		return this->cells[y][x].GetValue();
	}

	std::cerr << "Cell (" << x << "," << y << ") cannot be accessed. Invalid coordinates" << std::endl;

	return '\0';
}

// Initialize the grid by reading input from std::cin. Non-zero return value signals an initialization failure
int Grid::Initialize()
{
	std::string input;
	unsigned short parsedInput;
	for (size_t i = 0; i < GRID_DIMENSIONS; i++)
	{
		std::cin >> input;
		if (!IsValidShortInRange(input, parsedInput))
		{
			return 1;
		}

		// The first expected number is the grid width, the second is grid height
		i % 2 == 0 ? this->width = parsedInput : this->height = parsedInput; 
	}

	// Allocate memory for the cells matrix
	this->cells = new Cell2D * [this->height];
	for (size_t row = 0; row < this->height; row++)
	{
		cells[row] = new Cell2D[this->width];
	}

	// Initialize the grid row by row
	std::string inputRow;
	size_t inputRowLength;

	for (size_t row = 0; row < this->height; row++)
	{
		std::cin >> inputRow; // Each matrix row is inputed as a single string
		inputRowLength = inputRow.length();

		if (inputRowLength != this->width) // A matrix row must be width characters long
		{
			return 2;
		}

		for (size_t col = 0; col < inputRowLength; col++)
		{
			if (inputRow[col] == '0' || inputRow[col] == '1') // A matrix row consists of 1s and 0s only
			{
				this->cells[row][col].SetX(col);
				this->cells[row][col].SetY(row);
				this->cells[row][col].SetValue(inputRow[col]);
			}
			else
			{
				return 3;
			}
		}
	}

	return 0;
}

// Derive the next generation from the current one. Return true on success
bool Grid::DeriveNextGeneration()
{
	if (this->cells == nullptr)
	{
		std::cerr << "Game grid is not initialized" << std::endl;
		return false;
	}

	// Changes to be applied to the current state of the grid in order to represent the next generation
	std::vector<Cell2D> changes; 

	unsigned short greenNeighbours;
	for (size_t x = 0; x < this->width; x++)
	{
		for (size_t y = 0; y < this->height; y++)
		{
			greenNeighbours = CountGreenNeighbours(x, y);
			if (this->cells[y][x].GetValue() == '0' && (rule1PossibleValues.count(greenNeighbours) != 0)) // Rule 1
			{
				changes.push_back(Cell2D(x, y, '1'));
			}
			else if (this->cells[y][x].GetValue() == '1' && (rule3PossibleValues.count(greenNeighbours) != 0)) // Rule 3
			{
				changes.push_back(Cell2D(x, y, '0'));
			}
		}
	}

	// Apply changes to the grid to represent the new generation
	size_t changesCount = changes.size();
	Cell2D affectedPoint;

	for (size_t i = 0; i < changesCount; i++)
	{
		affectedPoint = changes[i];
		this->cells[affectedPoint.GetY()][affectedPoint.GetX()].SetValue(affectedPoint.GetValue());
	}

	return true;
}

Grid::~Grid()
{
	for (size_t ptrIndex = 0; ptrIndex < this->height; ptrIndex++)
	{
		delete[] this->cells[ptrIndex];
	}

	delete[] this->cells;

}
