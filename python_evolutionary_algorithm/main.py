from algorithm import EvolutionaryAlgorithm

# Main function.
def main():
    # Problem number of problem that is to be solved.
    # 0 OneMax, 1 LOLZ Prefix, 2 Suprising Sequences.
    problem_number = 0
    # Solution of the problem.
    solution = []
    # Length of solution.
    solution_length = 0
    if problem_number == 0 or problem_number == 1:
        solution_length = 40
        # Creates solution for 20-bit OneMax problem.
        for i in range(solution_length):
            solution.append(1)
    # Type of adult selection protocol.
    # 0 full, 1 over-production, 2 mixing.
    selection_protocol = 2 #0
    # Type of mechanism for mate selection.
    # 0 fitness+proportionate, 1 sigma-scaling, 2 tournament selection, 
    # 3 unknown_mechanism
    selection_mechanism = 1 #0
    EvolutionaryAlgorithm(problem_number, selection_protocol,
            selection_mechanism, solution, solution_length)

# Calls main function when the main module is run.
if __name__ == '__main__':
    main()

