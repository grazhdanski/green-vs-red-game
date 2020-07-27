#pragma once

/* 
	Class: Cell2D
	Description: Models a two dimensional cell
*/

class Cell2D
{
	unsigned short x;
	unsigned short y;
	char value;

public:
	// Constructors
	Cell2D() :x(0), y(0), value(0) {}
	Cell2D(const unsigned short _x, const unsigned short _y, const char _value) : x(_x), y(_y), value(_value) {}

	// Getters
	unsigned short GetX() const { return this->x; }
	unsigned short GetY() const { return this->y; }
	char GetValue() const { return this->value; }

	// Setters
	void SetX(const unsigned short _x) { this->x = _x; }
	void SetY(const unsigned short _y) { this->y = _y; }
	void SetValue(const char _value) { this->value = _value; }
};