#ifndef CROSSOVER_MUTATION_HPP
#define CROSSOVER_MUTATION_HPP

#include <vector>

#include "bot.hpp"

class CrossoverMutation
{
public:
    static void fillGenes(std::vector<int>& genes);
    static void mutation(std::vector<int>& genes, const int count);
    static void crossoverOfTwo(std::vector<int>& genes,
                               const std::vector<int>& first,
                               const std::vector<int>& second);

private:
    enum class Genes
    {
        Left,
        Right,
        FORWARD,
        Eat,
        Neutralize,
        Look,
        GOTO
    };
    static CrossoverMutation& getInstance();
    void fillOneGen(std::vector<int>& genes, const int i);
};

#endif // !CROSSOVER_MUTATION_HPP
