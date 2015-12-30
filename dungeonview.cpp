#include "dungeonview.hpp"

DungeonView::DungeonView(const DungeonLevel& lvl) : level(lvl) {}
DungeonView::~DungeonView() {}

void DungeonView::update(const sf::Time& deltatime)
{
    sf::Vector2i center = tileSize * level.getPosition(0);
    levelView.reset(sf::FloatRect(center.x-tileSize*7.5f, center.y-tileSize*7.5f, tileSize*16, tileSize*16));
    levelView.setCenter(center.x + tileSize/2, center.y + tileSize/2);
    levelView.setViewport(sf::FloatRect(0, 0, 1, 1.25f));
    levelView.zoom(1.0f);

//    GUIView.reset(sf::FloatRect(0.75f, 0.0f, 0.25f, 0.25f));
}

void DungeonView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RectangleShape shape;

    target.setView(levelView);

    // Tilemap
    shape.setSize(sf::Vector2f(16, 16));

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
    shape.setSize(sf::Vector2f(16, 16));
    shape.setFillColor(sf::Color::Green);

    int n = level.getNumCharacters();

    for (int i = 0; i < n; ++i)
    {
        std::string name = level.getName(i);
        sf::Vector2i pos = level.getPosition(name);
        shape.setPosition(pos.x*tileSize, pos.y*tileSize);

        target.draw(shape);
    }


    target.setView(GUIView);
    shape.setSize(sf::Vector2f(1000, 1000));
    shape.setPosition(0, 0);
    shape.setFillColor(sf::Color::Green);
    //target.draw(shape);

    target.setView(target.getDefaultView());
}
