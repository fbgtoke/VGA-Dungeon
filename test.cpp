#include "utils.hpp"
#include "nystrom.hpp"

int main()
{
    Nystrom generator;

    const int width = 49;
    const int height = 49;
    generator.setSize(width, height);
    generator.setNumRooms(1, 30);
    generator.setRoomSize(3, 10, 3, 10);
    generator.setPlaceAttempts(50);

    srand(time(NULL));
    generator.create();

    sf::RenderWindow window(sf::VideoMode(800, 640), "TEST");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed and
                event.key.code == sf::Keyboard::Return)
            {
                generator.create();
            }
        }

        window.clear(sf::Color::Red);
        sf::RectangleShape shape;
        shape.setSize(sf::Vector2f(8, 8));
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                shape.setPosition(j*8, i*8);
                int tile = generator.getTile(j, i);
                if (tile == -1) shape.setFillColor(sf::Color::Black);
                else shape.setFillColor(sf::Color::White);
                window.draw(shape);
            }
        }
        window.display();
    }
}
