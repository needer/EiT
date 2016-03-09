#include "evolutionaryAlgorithm.h"

EvolutionaryAlgorithm::EvolutionaryAlgorithm()
{
    generationNumber = 0;
    numberOfElites = 5; //1
    populationSize = 50; //10
    childrenSize = populationSize-numberOfElites;
    crossoverRate = 0.5;
    mutationRate = 0.1;
    bestFitness = 0;
    averageFitness = 0;
    noSolution = true;
    solutionLength = 40;
    for(int i = 0; i<solutionLength; i++)
    {
        solution.push_back(newGeno());
    }
    for(int i = 0; i<populationSize; i++)
    {
        population.push_back(Individual(randomGenotype());
    }
    srand(time(NULL));
    evolutionaryLoop();
}

void EvolutionaryAlgorithm::evolutionaryLoop()
{
    children.insert(children.end(), population.begin(), population.end() );
    fitnessEvaluation();
    loggingRoutine();
    while(noSolution)
    {
        elitism();
        mating();
        fitnessEvaluation();
        population.clear();
        population.insert(population.end(), children.begin(), children.end() );
        population.insert(population.end(), masterRace.begin(), masterRace.end() );
        loggingRoutine();
    }
    //plottingRoutine();
}

void EvolutionaryAlgorithm::fitnessEvaluation()
{
    calculateFitness();
    sigmaScaling();
}
void EvolutionaryAlgorithm::calculateFitness()
{
    for(int i = 0; i<childrenSize; i++)
    {
        double count = 0;
        for(int j = 0; i<solutionLength; i++)
        {
            if genotype[i] == solution[i]
            {
                count++;
            }
        }
        children[i].fitness = count/solutionLength;
    }
}

void EvolutionaryAlgorithm::elitism()
{
    std::vector<double> previousGenerationFitness;
    for(int i = 0; i<populationSize; i++)
    {
        previousGenerationFitness.push_back(populationFitness[i]);
    }
    masterRace.clear();
    for(int i = 0; i<numberOfElites; i++)
    {
        fittestIndex = *std::max_element(previousGenerationFitness, previousGenerationFitness+populationSize);
        masterRace.push_back(previousGenerationFitness[fittestIndex]);
        previousGenerationFitness[fittestIndex] = 0;
    }
}

void EvolutionaryAlgorithm::mating()
{
    children.clear();
    scaledFitness.clear();
    sigmaScaling();
    for(int i=0; i<childrenSize; i++)
    {
        double rouletteValue1 = rand();
        double rouletteValue2 = rand();
        int index1 = 0;
        int index2 = 0;
        double needleValue = 0;
        for(int i = 0; i<populationSize; i++)
        {
            needleValue += scaledFitness[i];
            if(needleValue >= rouletteValue1)
            {
                index1 = i
                break;
            }
        }
        needleValue = 0;
        for(int i = 0; i<populationSize; i++)
        {
            needleValue += scaledFitness[i];
            if(needleValue >= rouletteValue2)
            {
                index1 = i
                break;
            }
        }
        std::vector<int> newGenotype = crossover(population[index1].genotype, population[index2].genotype);
        newGenotype = mutation(newGenotype);
        children.push_back(Individual(newGenotype));
    }
}

std::vector<double> EvolutionaryAlgorithm::sigmaScaling()
{
    double standardDeviationFitness2 = 2*standardDeviationFitness;
    double mean = averageFitness;
    std::vector<double> sigmaFitness;
    for(int i = 0; i<populationSize; i++)
    {
    i   sigmaFitness.push_back(1+((fitness-mean)/standardDeviationFitness2));
i       double sigmaFitnessSum = 0;
        for(int n : sigmaFitness)
        {
            sigmaFitnessSum += n;
        }
        for(i = 0; i<populationSize; i++)
        {
            sigmaFitness[i] = sigmaFitness[i]/sigmaFitnessSum;
        }
    }
    return sigmaFitness;
}

std::vector<int> EvolutionaryAlgorithm::mutation(std::vector<int> genotype)
{
    std::vector<int> newGenotype;
    for(int i = 0; i<genotype.size(); i++)
    {
        if(rand <= mutationRate)
        {
            newGenotype.push_back(newGeno());
        }
        else
        {
            newGenotype.push_back(genotype[i]);
        }
    }
    return newGenotype;
}

int EvolutionaryAlgorithm::newGeno()
{
    return rand() % 2; //4
}

std::vector<int> EvolutionaryAlgorithm::crossover(std::vector<int> genotype1, std::vector<int> genotype2)
{
    std::vector<int> newGenotype;
    for(int i = 0; i<genotype1.size(); i++)
    {
        if (rand() <= crossoverRate)
        {
            newGenotype.push_back(genotype1[i]);
        }
        else
        {
            newGenotype.push_back(genotype2[i]);
        }
    }
    return newGenotype;
}

void EvolutionaryAlgorithm::loggingRoutine()
{
    populationFitness.clear();
    for(int i = 0; i<populationSize; i++)
    {
        populationFitness.append(population[i].fitness);
    }
    generationNumber++;
    averageFitness = std::accumulate(populationFitness.begin(), populationFitness.end(), 0.0)/populationFitness.size();
    double squareSum = std::inner_product(populationFitness.begin(), populationFitness.end(), populationFitness.begin(), 0.0);
    standardDeviationFitness = std::sqrt(squareSum/ populationFitness.size() - averageFitness*averageFitness);
    standardDeviationFitness = std::sqrt(
    fittestIndex = *std::max_element(populationFitness, populationFitness+populationSize);
    bestGenotype = population[fittestIndex].genotype;
    cout << "Generation Number: " << generationNumber;
    cout << "Average Fitness: " << averageFitness;
    cout << "Standard Deviation: " << standardDeviationFitness;
    cout << "Best Fitness: " << bestFitness;
    cout << "Best Genotype: " << bestGenotype;
    //bestFitnessArray.push_back(bestFitness);
    //averageFitnessArray.push_back(averageFitness);
    //standardDeviationFitnessArray.push_back(standardDeviationFitness);
    //generationNumberArray.push_back(generationNumber);
}

//void EvolutionaryAlgorithm::plottingRoutine(){}
