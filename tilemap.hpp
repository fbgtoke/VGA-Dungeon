#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "utils.hpp"

class Tilemap
{
private:
    matrix<Tile> map;

public:
    Tilemap();
    Tilemap(int width, int height);
    Tilemap(const Tilemap& original);
    ~Tilemap();
    void operator=(const Tilemap& original);

    int getWidth() const;
    int getHeight() const;

    bool outOfBounds(int x, int y) const;
    bool outOfBounds(const sf::Vector2i& pos) const;

    void setTile(int x, int y, Tile value);
    void setTile(const sf::Vector2i& pos, Tile value);

    Tile getTile(int x, int y) const;
    Tile getTile(const sf::Vector2i& pos) const;

    void copyMap(matrix<Tile>& view) const;
    void copyMap(matrix<Tile>& view, const sf::IntRect& bounds) const;
};

#endif // TILEMAP_HPP
