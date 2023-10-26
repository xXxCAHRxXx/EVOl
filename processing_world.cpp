#include "processing_world.hpp"

processingWorld&
processingWorld::getInstance()
{
    static processingWorld a;
    return a;
}

void
processingWorld::makeBorders(
    std::vector<std::vector<std::unique_ptr<Object>>>& field)
{
    const int N = field.size();
    const int M = field[0].size();

    for (int i = 0; i < std::max(N, M); ++i)
    {
        if (i < N)
        {
            field[i][0]     = std::make_unique<Wall>();
            field[i][M - 1] = std::make_unique<Wall>();
        }
        if (i < M)
        {
            field[0][i]     = std::make_unique<Wall>();
            field[N - 1][i] = std::make_unique<Wall>();
        }
    }
}

void
processingWorld::dfs(std::vector<std::vector<int>>& world,
                     std::vector<std::vector<int>>& horizontalWalls,
                     std::vector<std::vector<int>>& verticalWalls,
                     const int lengthN,
                     const int lengthM)
{
    std::vector<std::vector<int>> xy = {
        {-1, 0 },
        {1,  0 },
        {0,  -1},
        {0,  1 }
    };

    int randN = rand() % (lengthN - 2) + 1;
    int randM = rand() % (lengthM - 2) + 1;

    std::stack<World::Point> points;
    points.push({randN, randM});
    world[randN][randM] = 0;

    while (!points.empty())
    {
        World::Point v = points.top();

        int temp = 0;
        for (int i = 0; i < 4; ++i)
        {
            if (world[v.x + xy[i][0]][v.y + xy[i][1]] == 0) ++temp;
        }

        if (temp == 4)
        {
            points.pop();
            continue;
        }

        int randPoint = rand() % 4;
        while (world[v.x + xy[randPoint][0]][v.y + xy[randPoint][1]] == 0)
        {
            randPoint = rand() % 4;
        }

        world[v.x + xy[randPoint][0]][v.y + xy[randPoint][1]] = 0;
        points.push({v.x + xy[randPoint][0], v.y + xy[randPoint][1]});

        if (randPoint == 0 || randPoint == 1)
        {
            (xy[randPoint][0] == 1 ? horizontalWalls[v.x][v.y]
                                   : horizontalWalls[v.x + xy[randPoint][0]]
                                                    [v.y + xy[randPoint][1]]) =
                0;
        }
        else
        {
            (xy[randPoint][1] == 1 ? verticalWalls[v.x][v.y]
                                   : verticalWalls[v.x + xy[randPoint][0]]
                                                  [v.y + xy[randPoint][1]]) = 0;
        }
    }
}

void
processingWorld::drawWalls(
    std::vector<std::vector<std::unique_ptr<Object>>>& field)
{
    const int lengthPassage = 5;
    int lengthN             = (field.size() - 1) / lengthPassage + 2,
        lengthM             = (field[0].size() - 1) / lengthPassage + 2;

    std::vector<std::vector<int>> world(lengthN, std::vector<int>(lengthM, 1));
    std::vector<std::vector<int>> horizontalWalls(lengthN - 1,
                                                  std::vector<int>(lengthM, 1));
    std::vector<std::vector<int>> verticalWalls(
        lengthN, std::vector<int>(lengthM - 1, 1));

    for (int i = 0; i < std::max(lengthN, lengthM); ++i)
    {
        if (i < lengthN)
        {
            world[i][0]           = 0;
            world[i][lengthM - 1] = 0;
        }
        if (i < lengthM)
        {
            world[0][i]           = 0;
            world[lengthN - 1][i] = 0;
        }
    }

    auto& temp = getInstance();
    temp.dfs(world, horizontalWalls, verticalWalls, lengthN, lengthM);

    for (int i = 1; i < lengthN - 1; ++i)
    {
        for (int j = 1; j < lengthM - 1; ++j)
        {
            if (horizontalWalls[i][j] == 1)
            {
                for (int k = 0; k <= lengthPassage; ++k)
                {
                    if (j == 1)
                    {
                        if (k == lengthPassage) break;
                        field[i * lengthPassage][j + k] =
                            std::make_unique<Wall>();
                    }
                    else
                    {
                        field[i * lengthPassage][(j - 1) * lengthPassage + k] =
                            std::make_unique<Wall>();
                    }
                }
            }
            if (verticalWalls[i][j] == 1)
            {
                for (int k = 0; k <= lengthPassage; ++k)
                {
                    if (i == 1)
                    {
                        if (k == lengthPassage) break;
                        field[i + k][j * lengthPassage] =
                            std::make_unique<Wall>();
                    }
                    else
                    {
                        field[(i - 1) * lengthPassage + k][j * lengthPassage] =
                            std::make_unique<Wall>();
                    }
                }
            }
        }
    }
}

std::set<World::Point>
processingWorld::getCoordinates(
    std::vector<std::vector<std::unique_ptr<Object>>>& field, const int size)
{
    std::set<World::Point> coord;
    while (coord.size() < size)
    {
        int x, y;
        x = 1 + rand() % (field.size() - 2);
        y = 1 + rand() % (field[0].size() - 2);
        if (field[x][y]->getType() == Object::Type::Emptiness)
        {
            coord.insert({x, y});
        }
    }
    return coord;
}

std::queue<World::Point>
processingWorld::populateBots(
    std::vector<std::vector<std::unique_ptr<Object>>>& field, const int size)
{
    auto& temp                   = getInstance();
    std::set<World::Point> coord = temp.getCoordinates(field, size);
    std::queue<World::Point> points;
    for (auto& i : coord)
    {
        field[i.x][i.y] = std::make_unique<Bot>();
        points.push({i.x, i.y});
        static_cast<Bot*>(field[i.x][i.y].get())->giveGenes();
    }
    return points;
}

void
processingWorld::deleteField(
    std::vector<std::vector<std::unique_ptr<Object>>>& field)
{
    for (int i = 1; i < field.size() - 1; ++i)
    {
        for (int j = 1; j < field[0].size(); ++j)
        {
            field[i][j] = std::make_unique<Emptiness>();
        }
    }
}
