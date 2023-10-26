#include "bot.hpp"

const int Bot::maxHealth       = 100;
const int Bot::sizeGenes       = 64;
const int Bot::healthForFood   = 30;
const int Bot::healthForPosion = 30;
const int Bot::payForMove      = 1;

Bot::Bot()
    : Object(Object::Type::Bot), health(maxHealth), genes(sizeGenes), curGen(0)
{
}

Bot::~Bot()
{
}

const int
Bot::getHealth() const
{
    return health;
}

const Direction
Bot::getDirection() const
{
    return direction;
}

void
Bot::feed(const float fraction)
{
    health += healthForFood * fraction;
    if (health > maxHealth)
    {
        health = maxHealth;
    }
}

void
Bot::poison(const float fraction)
{
    health -= healthForPosion * fraction;
}

void
Bot::look(const Object* obj)
{
    switch (obj->getType())
    {
        case Object::Type::Poison:
            curGen += 1;
            break;
        case Object::Type::Wall:
            curGen += 2;
            break;
        case Object::Type::Bot:
            curGen += 3;
            break;
        case Object::Type::Food:
            curGen += 4;
            break;
        case Object::Type::Emptiness:
            curGen += 5;
            break;
    }
    if (curGen >= sizeGenes)
    {
        curGen = curGen - sizeGenes;
    }
}

void
Bot::GOTO(const int Goto)
{
    curGen += Goto;
    if (curGen >= sizeGenes)
    {
        curGen -= sizeGenes;
    }
    if (curGen < 0)
    {
        curGen += sizeGenes;
    }
}

void
Bot::payForMOVE()
{
    health -= payForMove;
}

const Bot::Action
Bot::getAction()
{
    if (health <= 0)
    {
        return Action::Died;
    }
    if (curGen >= sizeGenes)
    {
        curGen = curGen - sizeGenes;
    }
    switch (genes[curGen])
    {
        case 0:
            direction--;
            ++curGen;
            return Action::NUN;
            break;
        case 1:
            direction++;
            ++curGen;
            return Action::NUN;
            break;
        case 2:
            ++curGen;
            return Action::FORWARD;
            break;
        case 3:
            ++curGen;
            return Action::Eat;
            break;
        case 4:
            ++curGen;
            return Action::Neutralize;
            break;
        case 5:
            return Action::Look;
            break;
        default:
            GOTO(genes[curGen]);
            return Action::NUN;
            break;
    }
}

std::vector<int>
Bot::getGenes() const
{
    return genes;
}

void
Bot::giveGenes()
{
    CrossoverMutation::fillGenes(genes);
}

void
Bot::mutation(const int count)
{
    CrossoverMutation::mutation(genes, count);
}

void
Bot::crossoverOfTwo(std::vector<int>& genes,
                    const std::vector<int>& first,
                    const std::vector<int>& second)
{
    CrossoverMutation::crossoverOfTwo(genes, first, second);
}
