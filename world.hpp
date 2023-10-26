#ifndef WORLD_HPP
#define WORLD_HPP

#include <memory>

#include "bot.hpp"
#include "emptiness.hpp"
#include "food.hpp"
#include "object.hpp"
#include "poison.hpp"
#include "processing_world.hpp"
#include "wall.hpp"

class World
{
public:
    struct Point
    {
        int x;
        int y;

        bool operator<(const Point& other) const
        {
            if (x == other.x) return y < other.y;
            return x < other.x;
        }

        bool operator==(const Point& other) const
        {
            return x == other.x && y == other.y;
        }
    };

    World();
    ~World();

    const std::vector<std::vector<std::unique_ptr<Object>>>& getField() const;

private:
    // структуры

    // переменные и структуры данных
    std::vector<std::vector<std::unique_ptr<Object>>> field;
    static const int N;
    static const int M;

    static const int maxCountFood;
    static const int maxCountPoison;
    static const int maxCountBot;
    int countFood;
    int countPoison;

    std::vector<std::queue<Point>> bots;
    std::queue<Point> food;
    std::queue<Point> poison;

    // методы
};

#endif // !WORLD_HPP
