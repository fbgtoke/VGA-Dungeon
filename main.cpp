#include "utils.hpp"
#include "dungeoncontroller.hpp"

int main()
{
    DungeonController controller;
    controller.create();

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), app_name);
    sf::Clock clk;
    while (window.isOpen())
    {
        try {

        sf::Time deltatime = clk.restart();
        controller.update(deltatime);

        window.clear(sf::Color::Black);
        window.draw(controller);
        window.display();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed or
                (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape))
                window.close();

            controller.event(event);
        }

        } catch (const char* e) { std::cout << e << std::endl; }
    }
}
