#include "individual.h"

Individual::Individual(std::vector<int> genotype)
{
        this->genotype = genotype;
        this->fitness = 0;
}
