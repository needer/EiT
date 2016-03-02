#include "evolutionaryAlgorithm.h"

EvolutionaryAlgorithm::EvolutionaryAlgorithm()
{
        generationNumber = 0;
        numberOfElites = 1;
        populationSize = 10;
        childrenSize = populationSize-numberOfElites;
        crossoverRate = 0.5;
        mutationRate = 0.1;
        bestFitness = 0;
        averageFitness = 0;
        for( int i = 0; i<populationSize; i++)
        {
                population.push_back(Individual(randomGenotype());
        }
        evolutionaryLoop();
}

void EvolutionaryAlgorithm::evolutionaryLoop()
{
        children.insert(children.end(), population.begin(), population.end() );
        fitnessEvaluation();
        loggingRoutine();
        while(true)
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
{}

void EvolutionaryAlgorithm::elitism()
{
        std::vector<float> previousGenerationFitness;
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
        
        
}
