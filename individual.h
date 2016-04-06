#pragma once

#include <vector>

class Individual
{
public:
	std::vector<char[]> genotype;
    double fitness;

    Individual(std::vector<char[]>);
};
