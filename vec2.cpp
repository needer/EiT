#include "vec2.h"
#include <math.h>

// Constructor
Vec2::Vec2(float x, float y) 
	: x(x), y(y)
{}

// Length of the vector
float Vec2::magnitude()
{
	return sqrt(x*x + y*y);
}