#pragma once
#include "Cell2D.h"
#include <iostream>

/*
	Class: Grid
	Description: Models a two dimensional grid for the game GreenVsRed
*/

class Grid
{
	unsigned short width;
	unsigned short height;
	Cell2D** cells;

	Grid(const Grid& other) = delete; // Forbid copying
	Grid& operator=(const Grid& other) = delete; // Forbid assignment

	bool IsValidCell(const int x, const int y) const;
	unsigned short CountGreenNeighbours(const int x, const int y);

public:

	// Getters
	unsigned short GetWidth() const { return width; }
	unsigned short GetHeight() const { return height; }
	char GetCellValue(const Cell2D& cell) const;

	// Constructors
	Grid() :width(0), height(0), cells(nullptr) {} // Default constructor
	~Grid();

	// Utilities
	int Initialize(); // Grid initialization from user input
	bool DeriveNextGeneration(); // Derive the next generation from the current one
};
