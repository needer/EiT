#pragma once

#include <vector>
#include <algorithm>
#include <numeric>
#include <stdlib.h>
#include <time.h>

class EvolutionaryAlgorithm
{
public:
        int generationNumber;
        int numberOfElites;
        int populationSize;
        int childrenSize;
        double crossoverRate;
        double mutationRate;
        double bestFitness;
        double averageFitness;
        double standardDeviationFitness;
        std::vector<double> bestFitnessArray;
        std::vector<double> averageFitnessArray;
        std::vector<double> standardDeviationFitnessArray;
        std::vector<double> generationNumberArray;
        std::vector<Individual> population;
        std::vector<double> populationFitness;
        std::vector<double> scaledFitness;
        std::vector<Individual> children;
        std::vector<Individual> masterRace;
        std::vector<int> bestGenotype;
        
        EvolutionaryAlgorithm();
        ~EvolutionaryAlgorithm();
        void evolutionaryLoop();
        void fitnessEvaluation();
        void elitism();
        void mating();
        void calculateFitness();
        double sigmaScaling();
        std::vector<int> mutation(std::vector<int> genotype);
        int newGeno();
        std::vector<int> randomGenotype();
        std::vector<int> crossover(std::vector<int> genotype1, std::vector<int> genotype2);
        void loggingRoutine();
        void plottingRoutine();
};
