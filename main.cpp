#include "utils.hpp"
#include "dungeonlevel.hpp"
#include "dungeonview.hpp"
#include "dungeongenerator.hpp"
#include "turncontroller.hpp"

int main()
{
    DungeonLevel lvl;
    DungeonView view(lvl);
    DungeonGenerator gen(lvl);
    gen.create();
    TurnController turn(lvl);

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), app_name);
    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        window.draw(view);
        window.display();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed or
                (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape))
                window.close();

            if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Return)
                turn.turn();
        }
    }

#ifdef DEBUG
    lvl.printMap();
    lvl.printCharacters();
#endif
}
