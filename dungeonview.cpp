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

void DungeonView::drawTilemap(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Sprite sprite(tileSheet);

    int width = level.getMapWidth();
    int height = level.getMapHeight();

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            sprite.setPosition(j*tileSize, i*tileSize);

            Tile tile = level.getTile(j, i);
            switch (tile)
            {
            case NONE:
                sprite.setTextureRect(sf::IntRect(0*tileSize, 0, tileSize, tileSize));
                break;
            case WALL:
                sprite.setTextureRect(sf::IntRect(1*tileSize, 0, tileSize, tileSize));
                break;
            case WALK:
                sprite.setTextureRect(sf::IntRect(2*tileSize, 0, tileSize, tileSize));
                break;
            default:
                sprite.setTextureRect(sf::IntRect(3*tileSize, 0, tileSize, tileSize));
                break;
            }

            target.draw(sprite);
        }
    }
}
void DungeonView::drawCharacters(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RectangleShape shape;
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
}

void DungeonView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RectangleShape shape;

    target.setView(levelView);
    drawTilemap(target, states);
    drawCharacters(target, states);

    target.setView(GUIView);
    shape.setSize(sf::Vector2f(1000, 1000));
    shape.setPosition(0, 0);
    shape.setFillColor(sf::Color::Green);
    //target.draw(shape);

    target.setView(target.getDefaultView());
}

void DungeonView::setTileSize(int size)
{
    assert (size > 0);
    tileSize = size;
}

int DungeonView::getTileSize() const { return tileSize; }

void DungeonView::setTileSheet(const std::string& name)
{
    if (not tileSheet.loadFromFile(resources + name))
        throw "Could not load tile sheet";
}
