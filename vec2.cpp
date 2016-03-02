#include "vec2.h"
#include <math.h>

// Constructor
Vec2::Vec2(int x, int y) 
	: x(x), y(y)
{}

// Length of the vector
float Vec2::magnitude()
{
	return sqrt((float)x * (float)x + (float)y * (float)y);
}

Vec2 Vec2::operator-(const Vec2& other)
{
	Vec2 temp(0, 0);
	temp.x = x - other.x;
	temp.y  = y - other.y;

	return temp;
}

Vec2 Vec2::operator+(const Vec2& other)
{
	Vec2 temp(0, 0);
	temp.x = x - other.x;
	temp.y = y - other.y;

	return temp;
}
