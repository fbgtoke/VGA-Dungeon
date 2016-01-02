#ifndef TILEMAPVIEW_H
#define TILEMAPVIEW_H

#include "utils.hpp"

class TileMapView : public sf::Drawable
{
private:
    const DungeonLevel& level;

    int tileSize = 16;
    sf::Texture tileSheet;

public:
    TileMapView(const DungeonLevel& lvl);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

    void setTileSize(int size);
    int getTileSize() const;

    void setTileSheet(const std::string& name);
};

#endif // TILEMAPVIEW_H
