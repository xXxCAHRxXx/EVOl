#ifndef PROCESSING_WORLD_HPP
#define PROCESSING_WORLD_HPP

#include <algorithm>
#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#include "bot.hpp"
#include "emptiness.hpp"
#include "food.hpp"
#include "object.hpp"
#include "poison.hpp"
#include "wall.hpp"
#include "world.hpp"

class processingWorld
{
public:
    static void makeBorders(
        std::vector<std::vector<std::unique_ptr<Object>>>& field);

    static void drawWalls(
        std::vector<std::vector<std::unique_ptr<Object>>>& field);

    template <typename T>
    static void populate(
        std::vector<std::vector<std::unique_ptr<Object>>>& field,
        const int size,
        std::queue<World::Point> points)
    {
        auto& temp                   = getInstance();
        std::set<World::Point> coord = temp.getCoordinates(field, size);
        for (auto& i : coord)
        {
            field[i.x][i.y] = std::make_unique<T>();
            points.push({i.x, i.y});
        }
    }

    static std::queue<World::Point> populateBots(
        std::vector<std::vector<std::unique_ptr<Object>>>& field,
        const int size);

    static void deleteField(
        std::vector<std::vector<std::unique_ptr<Object>>>& field);

private:
    static processingWorld& getInstance();

    void dfs(std::vector<std::vector<int>>& world,
             std::vector<std::vector<int>>& horizontalWalls,
             std::vector<std::vector<int>>& verticalWalls,
             const int lengthN,
             const int lengthM);

    std::set<World::Point> getCoordinates(
        std::vector<std::vector<std::unique_ptr<Object>>>& field,
        const int size);
};

#endif // !PROCESSING_WORLD_HPP
