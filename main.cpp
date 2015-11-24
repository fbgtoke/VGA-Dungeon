#include "utils.hpp"
#include "dungeonlevel.hpp"

int main(int argc, char** argv)
{
    DungeonLevel lvl;
    lvl.newCharacter(DEFAULT, sf::Vector2i(3, 3));

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), app_name);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        lvl.turn();

        window.clear(sf::Color::Black);

        sf::RectangleShape sprite(sf::Vector2f(16, 16));

        // Tiles
        matrix<Tile> tiles;
        lvl.getAllTiles(tiles);
        int width = tiles[0].size();
        int height = tiles.size();
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                sprite.setPosition(j*16, i*16);

                TilePermission p = tiles[i][j].getPermission();
                switch(p)
                {
                case NONE:
                    sprite.setFillColor(sf::Color::White);
                    break;
                case WALK:
                    sprite.setFillColor(sf::Color::Blue);
                    break;
                case WALL:
                    sprite.setFillColor(sf::Color::Green);
                    break;
                default:
                    break;
                }

                window.draw(sprite);
            }
        }

        // Characters
        sprite.setFillColor(sf::Color::Red);
        int n = lvl.getNumCharacters();
        for (int i = 0; i < n; ++i)
        {
            Character c;
            lvl.getCharacter(i, c);
            sf::Vector2i pos = c.getPosition();
            sprite.setPosition(pos.x*16, pos.y*16);
            window.draw(sprite);
        }
        window.display();
    }

    return EXIT_SUCCESS;
}
