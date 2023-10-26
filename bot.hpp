#ifndef BOT_HPP
#define BOT_HPP

#include <vector>

#include "crossover_mutation.hpp"
#include "direction.hpp"
#include "object.hpp"

class Bot : public Object
{
public:
    // структуры
    enum class Action
    {
        NUN,
        FORWARD,
        Eat,
        Neutralize,
        Look,
        Died
    };
    // переменные и структуры данных

    // методы и конструкторы
    Bot();
    ~Bot();
    const int getHealth() const;
    const Direction getDirection() const;

    void feed(const float fraction);
    void poison(const float fraction);
    void look(const Object* obj);
    void payForMOVE();
    const Action getAction();

    std::vector<int> getGenes() const;

    void giveGenes();
    void mutation(const int count);
    void crossoverOfTwo(std::vector<int>& genes,
                        const std::vector<int>& first,
                        const std::vector<int>& second);

private:
    // структуры
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
    // переменные и структуры данных
    static const int maxHealth;
    int health;

    static const int sizeGenes;
    std::vector<int> genes;
    int curGen;

    Direction direction;

    static const int healthForFood;
    static const int healthForPosion;

    static const int payForMove;

    // методы и конструкторы
    void GOTO(const int Goto);
};

#endif // !BOT_HPP
