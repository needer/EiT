#pragma once

#include <vector>

class Individual
{
public:
        std::vector<int> genotype;
        float fitness;

        Individual(std::vector<int>);
        ~Individual();
