#pragma once
/*
--- AOE TECH TREE REPLACEMENT :: DRAW UTILITIES ---
Contains some helper classes for easier drawing. These types are not game types!
*/

// Defines a two dimensional point.
class Point
{
public:
	int X;
	int Y;

public:
	// Creates a new point with (0, 0) coordinates.
	Point() :
		X(0), Y(0)
	{
	}

	// Creates a new point with the given coordinates.
	Point(int x, int y)
		: X(x), Y(y)
	{
	}

	// Assigns the coordinates of the given point to this point.
	void operator=(const Point &point)
	{
		// Assign coordinates
		X = point.X;
		Y = point.Y;
	}
};

// Defines a two dimensional size information. Does the exact same thing as a point, so simply use a typedef.
typedef Point Size;

// Defines a two dimensional rectangle.
class Rect
{
public:
	int X;
	int Y;
	int Width;
	int Height;

public:
	// Creates a new rectangle with (0, 0) coordinates.
	Rect()
		: X(0), Y(0), Width(0), Height(0)
	{
	}

	// Creates a new rectangle with the given coordinates and size.
	Rect(int x, int y, int width, int height)
		: X(x), Y(y), Width(width), Height(height)
	{
	}

	// Assigns the data of the given rectangle to this rectangle.
	void operator=(const Rect &rect)
	{
		// Assign data
		X = rect.X;
		Y = rect.Y;
		Width = rect.Width;
		Height = rect.Height;
	}
};