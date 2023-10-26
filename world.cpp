#include "world.hpp"

const int World::N              = 41;
const int World::M              = 81;
const int World::maxCountFood   = N * M * 0.1;
const int World::maxCountPoison = N * M * 0.1;
const int World::maxCountBot    = 64;

World::World()
    : field(N), countFood(maxCountFood), countPoison(maxCountPoison), bots(4)
{
    for (int i = 0; i < N; ++i)
    {
        std::vector<std::unique_ptr<Object>> temp(M);
        for (int j = 0; j < M; ++j)
        {
            temp[j] = std::make_unique<Emptiness>();
        }
        field[i] = std::move(temp);
    }
    processingWorld::makeBorders(field);
    processingWorld::drawWalls(field);
    processingWorld::populate<Food>(field, maxCountFood, food);
    processingWorld::populate<Poison>(field, maxCountPoison, poison);
    processingWorld::populateBots(field, maxCountBot);
}

World::~World()
{
}

const std::vector<std::vector<std::unique_ptr<Object>>>&
World::getField() const
{
    return field;
}
