#include "tilemap.hpp"

Tilemap::Tilemap() {}
Tilemap::Tilemap(int width, int height)
{
    map = matrix<Tile>(height, std::vector<Tile>(width));
}
Tilemap::Tilemap(const Tilemap& original) : map(original.map) {}
Tilemap::~Tilemap() {}
void Tilemap::operator=(const Tilemap& original) { map = original.map; }

int Tilemap::getWidth() const
{
    if (getHeight() > 0) return map[0].size();
    return 0;
}
int Tilemap::getHeight() const { return map.size(); }

bool Tilemap::outOfBounds(int x, int y) const
{
    return x < 0 or x >= getWidth() or y < 0 or y >= getHeight();
}
bool Tilemap::outOfBounds(const sf::Vector2i& pos) const
{
    return pos.x < 0 or pos.x >= getWidth() or pos.y < 0 or pos.y >= getHeight();
}

void Tilemap::setTile(int x, int y, Tile value)
{
    if (outOfBounds(x, y)) throw "Position out of range";
    map[y][x] = value;
}
void Tilemap::setTile(const sf::Vector2i& pos, Tile value)
{
    if (outOfBounds(pos)) throw "Position out of range";
    map[pos.y][pos.x] = value;
}

Tile Tilemap::getTile(int x, int y) const
{
    if (outOfBounds(x, y)) throw "Position out of range";
    return map[y][x];
}
Tile Tilemap::getTile(const sf::Vector2i& pos) const
{
    if (outOfBounds(pos)) throw "Position out of range";
    return map[pos.y][pos.x];
}

void Tilemap::copyMap(matrix<Tile>& view) const { view = map; }
void Tilemap::copyMap(matrix<Tile>& view, const sf::IntRect& bounds) const
{
    view = matrix<Tile>(bounds.height, std::vector<Tile>(bounds.width, NONE));

    for (int i = 0; i < bounds.height; ++i)
    {
        for (int j = 0; j < bounds.width; ++j)
        {
            int x = j + bounds.left;
            int y = i + bounds.top;
            if (not outOfBounds(x, y)) view[i][j] = map[y][x];
        }
    }
}

