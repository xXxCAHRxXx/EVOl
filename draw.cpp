#include "draw.hpp"

const float Draw::sizeN = 12;
const float Draw::r     = (sqrt(3) / 2) * sizeN;

Draw::Draw()
{
    font.loadFromFile("W:/sus/Roboto-Black.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::White);
}

Draw::~Draw()
{
}

void
Draw::run()
{
    World field;

    const float sizeFieldY =
        200 + 1.5 * sizeN * (field.getField().size() - 1) + sizeN;
    const float sizeFieldX = 200 + 2 * r * field.getField()[0].size() + r;
    window.create(sf::VideoMode(sizeFieldX, sizeFieldY), "EVOLUTION");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }
        window.clear();

        drawField(field.getField());

        window.display();
    }
}

void
Draw::drawField(const std::vector<std::vector<std::unique_ptr<Object>>>& field)
{
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(10);

    sf::CircleShape hexagon(sizeN, 6);
    hexagon.setOutlineColor(sf::Color::White);
    hexagon.setOutlineThickness(1);
    hexagon.setFillColor(sf::Color::White);

    float y = 100.f, x = 100.f;

    for (int i = 0; i < field.size(); ++i)
    {
        for (int j = 0; j < field[0].size(); ++j)
        {
            switch (field[i][j]->getType())
            {
                case (Object::Type::Wall):
                    hexagon.setFillColor(sf::Color(127, 127, 127)); // Grey
                    break;
                case (Object::Type::Bot):
                    hexagon.setFillColor(sf::Color(0, 0, 255)); // Blue
                    break;
                case (Object::Type::Food):
                    hexagon.setFillColor(sf::Color(0, 255, 0)); // Green
                    break;
                case (Object::Type::Poison):
                    hexagon.setFillColor(sf::Color(255, 0, 0)); // Red
                    break;
                case (Object::Type::Emptiness):
                    hexagon.setFillColor(sf::Color(0, 0, 0)); // Black
                    break;
            }

            hexagon.setPosition(x, y);
            window.draw(hexagon);

            if (field[i][j]->getType() == Object::Type::Bot)
            {
                text.setString(std::to_string(
                    static_cast<Bot*>(field[i][j].get())->getHealth()));
                text.setPosition(x + sizeN / 2 - 3, y + r / 2 - 1);
                window.draw(text);
            }

            x += 2 * r;
        }
        x = 100.f + (i % 2 == 0 ? r : 0);
        y += 1.5 * sizeN;
    }
}
