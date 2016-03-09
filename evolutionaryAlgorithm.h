#pragma once

#include <vector>
#include <algorithm>
#include <numeric>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cmath>

#include "individual.h"

class EvolutionaryAlgorithm
{
public:
    int generationNumber;
    int numberOfElites;
    int populationSize;
    int childrenSize;
    int solutionLength;
    double crossoverRate;
    double mutationRate;
    double bestFitness;
    double averageFitness;
    double standardDeviationFitness;
    bool noSolution;
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
    std::vector<int> solution;
        
    EvolutionaryAlgorithm();
    void evolutionaryLoop();
    void fitnessEvaluation();
    void elitism();
    void mating();
    void calculateFitness();
	std::vector<double> sigmaScaling();
    std::vector<int> mutation(std::vector<int>);
    int newGeno();
    std::vector<int> randomGenotype();
    std::vector<int> crossover(std::vector<int>, std::vector<int>);
    void loggingRoutine();
    void plottingRoutine();
};
