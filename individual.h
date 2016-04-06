#pragma once

#include <vector>
#include <string>

class Individual
{
public:
	std::vector<std::string> genotype;
    double fitness;

    Individual(std::vector<std::string>);
};
