#pragma once

#include <vector>
#include <algorithm>
#include <numeric>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cmath>
#include <string>

#include "individual.h"

class EvolutionaryAlgorithm
{
public:
    int numberOfRounds;
    int generationNumber;
    int numberOfElites;
    int populationSize;
    int childrenSize;
    int solutionLength;
	int numberOfCommands;
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
    std::vector<std::string> bestGenotype;
    //std::vector<int> solution;
        
    EvolutionaryAlgorithm(int numberOfRounds);
    void evolutionaryLoop();
    //void fitnessEvaluation();
    void elitism();
    void mating();
    void calculateFitness(std::vector<double> childrenScore);
	std::vector<double> sigmaScaling();
    std::vector<std::string> mutation(std::vector<std::string>);
    std::string newGeno();
    std::vector<std::string> randomGenotype();
    std::vector<std::string> crossover(std::vector<std::string>, std::vector<std::string>);
    void loggingRoutine();
    void plottingRoutine();
};
