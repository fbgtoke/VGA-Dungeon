#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "utils.hpp"
#include "tile.hpp"

class Tilemap : public GameObject
{
private:
    matrix<Tile> tiles;

public:
    Tilemap();
    Tilemap(int width, int height);
    ~Tilemap();

    int getWidth() const;
    int getHeight() const;
    sf::Vector2i getSize() const;

    void setTile(int x, int y, const Tile& t);
    void getTile(int x, int y, Tile& t) const;
    void getAllTiles(matrix<Tile>& t) const;

    TilePermission checkPermission(int x, int y) const;

    void getView(matrix<Tile>& v, int x, int y, int radius) const;

    void printMap() const;
};

#endif // TILEMAP_HPP
