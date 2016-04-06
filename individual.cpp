#include "individual.h"

Individual::Individual(std::vector<std::string> genotype)
{
        this->genotype = genotype;
        this->fitness = 0;
}
