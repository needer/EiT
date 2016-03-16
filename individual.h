#pragma once

#include <vector>

class Individual
{
public:
    std::vector<int> genotype;
    double fitness;

    Individual(std::vector<int>);
};
