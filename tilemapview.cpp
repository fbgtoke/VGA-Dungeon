#include "tilemapview.hpp"

TileMapView::TileMapView(const DungeonLevel& lvl) : level(lvl) {}

void TileMapView::draw(sf::RenderTarget& target, sf::RenderStates states) const
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

void TileMapView::setTileSize(int size)
{
    assert (size > 0);
    tileSize = size;
}

int TileMapView::getTileSize() const { return tileSize; }

void TileMapView::setTileSheet(const std::string& name)
{
    if (not tileSheet.loadFromFile(resources + name))
        throw "Could not load tile sheet";
}
