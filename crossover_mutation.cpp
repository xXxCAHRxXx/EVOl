#include "crossover_mutation.hpp"

CrossoverMutation&
CrossoverMutation::getInstance()
{
    static CrossoverMutation a;
    return a;
}

void
CrossoverMutation::fillOneGen(std::vector<int>& genes, const int i)
{
    const int typeGen = rand() % 6;

    switch (typeGen)
    {
        case 0:
        {
            const int leftOrRight = rand() % 2;
            switch (leftOrRight)
            {
                case 0:
                    genes[i] = int(Genes::Left);
                    break;
                case 1:
                    genes[i] = int(Genes::Right);
                    break;
            }
            break;
        }
        case 1:
            genes[i] = int(Genes::FORWARD);
            break;
        case 2:
            genes[i] = int(Genes::Eat);
            break;
        case 3:
            genes[i] = int(Genes::Neutralize);
            break;
        case 4:
            genes[i] = int(Genes::Look);
            break;
        case 5:
            const int randGOTO = rand() % (genes.size() * 2 + 1) - genes.size();
            genes[i]           = randGOTO;
            break;
    }
}

void
CrossoverMutation::fillGenes(std::vector<int>& genes)
{
    auto& temp = getInstance();
    for (int i = 0; i < genes.size(); ++i)
    {
        temp.fillOneGen(genes, i);
    }
}

void
CrossoverMutation::mutation(std::vector<int>& genes, const int count)
{
    auto& temp = getInstance();
    for (int i = 0; i < count; ++i)
    {
        const int randGen = rand() % genes.size();
        temp.fillOneGen(genes, randGen);
    }
}

void
CrossoverMutation::crossoverOfTwo(std::vector<int>& genes,
                                  const std::vector<int>& first,
                                  const std::vector<int>& second)
{
    const int divLine = rand() % (genes.size() - 1) + 1;

    for (int i = 0; i < genes.size(); ++i)
    {
        genes[i] = (i < divLine ? first[i] : second[i]);
    }
}
