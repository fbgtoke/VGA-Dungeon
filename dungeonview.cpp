#include "dungeonview.hpp"

DungeonView::DungeonView(const DungeonLevel& lvl) : level(lvl) {}
DungeonView::~DungeonView() {}

void DungeonView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RectangleShape shape;

    // Tilemap
    shape.setSize(sf::Vector2f(16, 16));
    shape.setOrigin(8, 8);

    int width = level.getMapWidth();
    int height = level.getMapHeight();

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            shape.setPosition(j*tileSize, i*tileSize);

            Tile tile = level.getTile(j, i);
            switch (tile)
            {
            case NONE:
                shape.setFillColor(sf::Color::Magenta);
                break;
            case WALL:
                shape.setFillColor(sf::Color::Red);
                break;
            case WALK:
                shape.setFillColor(sf::Color::White);
                break;
            default:
                shape.setFillColor(sf::Color::Transparent);
                break;
            }

            target.draw(shape);
        }
    }

    // Characters
    shape.setSize(sf::Vector2f(10, 10));
    shape.setOrigin(5, 5);
    shape.setFillColor(sf::Color::Green);

    int n = level.getNumCharacters();

    for (int i = 0; i < n; ++i)
    {
        std::string name = level.getName(i);
        sf::Vector2i pos = level.getPosition(name);
        shape.setPosition(pos.x*tileSize, pos.y*tileSize);

        target.draw(shape);
    }
}
