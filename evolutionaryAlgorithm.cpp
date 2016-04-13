#include "evolutionaryAlgorithm.h"

EvolutionaryAlgorithm::EvolutionaryAlgorithm(int numberOfRounds)
{
    this->numberOfRounds = numberOfRounds;
	generationNumber = 0;
	numberOfElites = 2; //2
	populationSize = 10; //10
	childrenSize = populationSize - numberOfElites;
	crossoverRate = 0.5;
	mutationRate = 0.1;
	bestFitness = 0;
	averageFitness = 0;
	numberOfCommands = 10;
	//noSolution = true;
	//solutionLength = 40;
    /*
	for (int i = 0; i < solutionLength; i++)
	{
		solution.push_back(1);
	}
    */
	for (int i = 0; i < populationSize; i++)
	{
		population.push_back(Individual(randomGenotype()));
	}
	srand(time(NULL));
	children.insert(children.end(), population.begin(), population.end());
	//evolutionaryLoop();
}

void EvolutionaryAlgorithm::evolutionaryLoop()
{
	//children.insert(children.end(), population.begin(), population.end());
	calculateFitness();
	population.clear();
	population.insert(population.end(), children.begin(), children.end());
	loggingRoutine();
    for(int i = 0; i<numberOfRounds; i++)
	{
		elitism();
		mating();
		calculateFitness();
		population.clear();
		population.insert(population.end(), children.begin(), children.end());
		population.insert(population.end(), masterRace.begin(), masterRace.end());
		loggingRoutine();
	}
	//plottingRoutine();
}

/*
void EvolutionaryAlgorithm::fitnessEvaluation()
{
	//calculateFitness();
}
*/


void EvolutionaryAlgorithm::calculateFitness(std::vector<double> childrenScore)
{
	for (int i = 0; i < children.size(); i++)
	{
        children[i].fitness = childrenScore[i];
	}
}


void EvolutionaryAlgorithm::elitism()
{
	std::vector<double> previousGenerationFitness;
	for (int i = 0; i < populationSize; i++)
	{
		previousGenerationFitness.push_back(populationFitness[i]);
	}
	masterRace.clear();
	for (int i = 0; i < numberOfElites; i++)
	{
		int fittestIndex = 0;
		double max = 0.0;
		for (int j = 0; j < populationSize; j++)
		{
			if (max < previousGenerationFitness[j])
			{
				fittestIndex = j;
				max = previousGenerationFitness[j];
			}
		}

		masterRace.push_back(population[fittestIndex]);
		previousGenerationFitness[fittestIndex] = 0;
	}
}

void EvolutionaryAlgorithm::mating()
{
	children.clear();
	scaledFitness.clear();
	scaledFitness = sigmaScaling();
	for (int i = 0; i < childrenSize; i++)
	{
		double rouletteValue1 = std::rand() / (RAND_MAX + 1.0);
		double rouletteValue2 = std::rand() / (RAND_MAX + 1.0);
		int index1 = 0;
		int index2 = 0;
		double needleValue = 0;
		for (int i = 0; i < populationSize; i++)
		{
			needleValue += scaledFitness[i];
			if (needleValue >= rouletteValue1)
			{
				index1 = i;
				break;
			}
		}
		needleValue = 0;
		for (int i = 0; i < populationSize; i++)
		{
			needleValue += scaledFitness[i];
			if (needleValue >= rouletteValue2)
			{
				index2 = i;
				break;
			}
		}
		std::vector<std::string> newGenotype = crossover(population[index1].genotype, population[index2].genotype);
		newGenotype = mutation(newGenotype);
		children.push_back(Individual(newGenotype));
	}
}

std::vector<double> EvolutionaryAlgorithm::sigmaScaling()
{
	double standardDeviationFitness2 = 2 * standardDeviationFitness;
	double mean = averageFitness;
	std::vector<double> sigmaFitness;
	for (int i = 0; i < populationSize; i++)
	{
		sigmaFitness.push_back(1 + ((population[i].fitness - mean) / standardDeviationFitness2));
	}

	double sigmaFitnessSum = 0;
    for(int i = 0; i < populationSize; i++)
	{
        sigmaFitnessSum += sigmaFitness[i];
	}

	for (int i = 0; i < sigmaFitness.size(); i++)
	{
		sigmaFitness[i] = sigmaFitness[i] / sigmaFitnessSum;
	}
	return sigmaFitness;
}

std::vector<std::string> EvolutionaryAlgorithm::mutation(std::vector<std::string> genotype)
{
	std::vector<std::string> newGenotype;
	for (int i = 0; i < genotype.size(); i++)
	{
		double rand = std::rand() / (RAND_MAX + 1.0);
		if (rand <= mutationRate)
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

std::string EvolutionaryAlgorithm::newGeno()
{
    std::string randomGeno = "";
	for (int i = 0; i < 2; i++){
		randomGeno += std::to_string(rand() % 3);
	}

	return randomGeno;
}

std::vector<std::string> EvolutionaryAlgorithm::randomGenotype()
{
	std::vector<std::string> newRandomGenotype;
	for (int i = 0; i < numberOfCommands; i++)
	{
		newRandomGenotype.push_back(newGeno());
	}
	return newRandomGenotype;
}

std::vector<std::string> EvolutionaryAlgorithm::crossover(std::vector<std::string> genotype1, std::vector<std::string> genotype2)
{
	std::vector<std::string> newGenotype;
	for (int i = 0; i < genotype1.size(); i++)
	{
		double rand = (double)std::rand() / (RAND_MAX + 1.0);
		if (rand <= crossoverRate)
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
	for (int i = 0; i < populationSize; i++)
	{
		populationFitness.push_back(population[i].fitness);
	}
	generationNumber++;
	averageFitness = std::accumulate(populationFitness.begin(), populationFitness.end(), 0.0) / populationFitness.size();
	double squareSum = std::inner_product(populationFitness.begin(), populationFitness.end(), populationFitness.begin(), 0.0);
	standardDeviationFitness = std::sqrt(squareSum / populationFitness.size() - averageFitness*averageFitness);

	int fittestIndex = 0;
	double max = 0.0;
	for (int i = 0; i < populationFitness.size(); i++)
	{
		if (max < populationFitness[i])
		{
			fittestIndex = i;
			max = populationFitness[i];
		}
	}
	bestGenotype = population[fittestIndex].genotype;
    bestFitness = population[fittestIndex].fitness;

	std::cout << "Generation Number: " << generationNumber << std::endl;
	std::cout << "Average Fitness: " << averageFitness << std::endl;
	std::cout << "Standard Deviation: " << standardDeviationFitness << std::endl;
	std::cout << "Best Fitness: " << bestFitness << std::endl;
	std::cout << "Best Genotype: ";
    for(int i=0; i<solutionLength; i++)
		std::cout << bestGenotype[i];
	std::cout << std::endl;

	//bestFitnessArray.push_back(bestFitness);
	//averageFitnessArray.push_back(averageFitness);
	//standardDeviationFitnessArray.push_back(standardDeviationFitness);
	//generationNumberArray.push_back(generationNumber);
}

//void EvolutionaryAlgorithm::plottingRoutine(){}
