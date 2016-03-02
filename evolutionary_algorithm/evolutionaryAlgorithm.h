#pragma once

#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

class EvolutionaryAlgorithm
{
public:
        int generationNumber;
        int numberOfElites;
        int populationSize;
        int childrenSize;
        float crossoverRate;
        float mutationRate;
        float bestFitness;
        float averageFitness;
        std::vector<float> bestFitnessArray;
        std::vector<float> averageFitnessArray;
        std::vector<float> standardDeviationFitnessList;
        std::vector<float> generationNumberList;
        std::vector<Individual> population;
        std::vector<float> populationFitness;
        std::vector<Individual> children;
        std::vector<Individual> masterRace;
        
        EvolutionaryAlgorithm();
        ~EvolutionaryAlgorithm();
        void evolutionaryLoop();
        void fitnessEvaluation();
        void elitism();
        void mating();
        void calculateFitness();
        float sigmaScaling();
        int[] mutation(int[] genotype);
        int newGeno();
        int[] randomGenotype();
        int[] crossover(genotype1, genotype2);
        void loggingRoutine();
        void plottingRoutine();
};
