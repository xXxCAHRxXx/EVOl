#ifndef DRAW_HPP
#define DRAW_HPP

#include <SFML/Graphics.hpp>

#include <memory>
#include <thread>

#include "Bot.hpp"
#include "object.hpp"
#include "world.hpp"

class Draw
{
public:
    Draw();
    ~Draw();

    void run();

private:
    void drawField(
        const std::vector<std::vector<std::unique_ptr<Object>>>& field);

    sf::RenderWindow window;
    sf::Text text;
    sf::Font font;
    static const float sizeN;
    static const float r;
};

#endif // !DRAW_HPP
