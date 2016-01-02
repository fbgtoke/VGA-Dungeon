#include "dungeonview.hpp"

DungeonView::DungeonView(const DungeonLevel& lvl) : level(lvl)
{
    if (not minimapTexture.loadFromFile(resources + "minimapsheet.png"))
        throw "Could not load minimap texture";
}
DungeonView::~DungeonView() {}

void DungeonView::update(const sf::Time& deltatime)
{
    center = level.getPosition(0);
    sf::Vector2i tile_center = center * tileSize;

    levelView.reset(sf::FloatRect(tile_center.x-tileSize*7.5f, tile_center.y-tileSize*7.5f, tileSize*16, tileSize*16));
    levelView.setCenter(tile_center.x + tileSize/2, tile_center.y + tileSize/2);
    levelView.setViewport(sf::FloatRect(0, 0, 1, 1.25f));
    levelView.zoom(1.0f);

    minimapView.reset(sf::FloatRect(tile_center.x-tileSize*37.5f, tile_center.y-tileSize*37.5f, tileSize*80, tileSize*80));
    minimapView.setCenter(tile_center.x + tileSize/2, tile_center.y + tileSize/2);
    minimapView.setViewport(sf::FloatRect(0.75f, 0.05f, 0.2f, 0.25f));
    minimapView.zoom(0.5f);
}

void DungeonView::drawTilemap(sf::RenderTarget& target, const sf::Texture& texture, int width, int height) const
{
    int left = center.x - width/2;
    int top = center.y - height/2;
    sf::IntRect boundary(left, top, width, height);
    matrix<Tile> view;
    level.getView(view, boundary);

    sf::Sprite sprite(texture);
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            Tile tile = view[i][j];
            int x = (j + left) * tileSize;
            int y = (i + top) * tileSize;
            sprite.setPosition(x, y);

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
    shape.setFillColor(sf::Color::Magenta);

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
    target.setView(levelView);
    drawTilemap(target, tileSheet, 20, 20);
    drawCharacters(target, states);

    target.setView(minimapView);
    drawTilemap(target, minimapTexture, 90, 90);

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
