#pragma once

// Simple 2 dimentional vector class
class Vec2
{
public:
	int x, y;
	Vec2(int x, int y);
	float magnitude();
};