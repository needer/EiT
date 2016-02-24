#pragma once

// Simple 2 dimentional vector class
class Vec2
{
public:
	float x, y;
	Vec2(float x, float y);
	float magnitude();
};