#include "utils.hpp"
#include "nystrom.hpp"

int main()
{
    Nystrom generator;

    generator.setSize(50, 50);
    generator.setNumRooms(1, 30);
    generator.setRoomSize(3, 10, 3, 10);
    generator.setPlaceAttempts(50);

    srand(time(NULL));
    generator.create();

    sf::RenderWindow window(sf::VideoMode(800, 640), "TEST");
    window.clear(sf::Color::Black);

    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(8, 8));
    for (int i = 0; i < 50; ++i)
    {
        for (int j = 0; j < 50; ++j)
        {
            shape.setPosition(j*8, i*8);
            Tile tile = generator.getTile(j, i);
            switch (tile)
            {
            case NONE:
                shape.setFillColor(sf::Color::Black);
                break;
            case WALL:
                shape.setFillColor(sf::Color::Red);
                break;
            case WALK:
                shape.setFillColor(sf::Color::White);
                break;
            default:
                shape.setFillColor(sf::Color::Magenta);
                break;
            }

            window.draw(shape);
        }
    }

    window.display();
    while (window.isOpen());
}
