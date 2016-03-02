from random import randint

from bitarray import bitarray


class Individual():

    def __init__(self, genotype):
        self.genotype = genotype        
        self.fitness = 0.0

    # Converts the Individual`s genotype to phenotype and returns them.
    def convert_geno_to_pheno(self):
        return bitarray.tolist(self.genotype)
