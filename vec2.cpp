#include "vec2.h"
#include <math.h>

// Constructor
Vec2::Vec2(int x, int y) 
	: x(x), y(y)
{}

// Length of the vector
float Vec2::magnitude()
{
	return sqrt((float)x*(float)x + (float)y*(float)y);
}