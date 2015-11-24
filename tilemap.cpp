#include "tilemap.hpp"

Tilemap::Tilemap() {}
Tilemap::~Tilemap() {}

int Tilemap::getWidth() const
{
    if (tiles.size() == 0) return 0;
    else return tiles[0].size();
}
int Tilemap::getHeight() const { return tiles.size(); }
sf::Vector2i Tilemap::getSize() const { return sf::Vector2i(getHeight(), getWidth()); }

void Tilemap::setTile(int x, int y, const Tile& t)
{
    if (x >= 0 and x < getWidth() and y >= 0 and y < getHeight())
    {
        tiles[y][x] = t;
    }
}
void Tilemap::getTile(int x, int y, Tile& t) const
{
    if (x >= 0 and x < getWidth() and y >= 0 and y < getHeight())
    {
        t = Tile(tiles[y][x]);
    }
}
void Tilemap::getAllTiles(matrix<Tile>& t) const { t = tiles; }

void Tilemap::getView(matrix<Tile>& v, int x, int y, int radius) const
{
    int left = x - radius;
    int top = y - radius;

    int size = 2*radius + 1;
    v = matrix<Tile> (size, std::vector<Tile>(size));

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            int posx = j + left;
            int posy = i + top;
            if (posy >= 0 and posy < tiles.size() and posx >= 0 and posx < tiles[0].size())
            {
                v[i][j] = tiles[posy][posx];
            }
        }
    }
}

void Tilemap::printMap() const
{
    std::cout << "Printing map" << std::endl;
    std::cout << "Width: " << getWidth() << " Height: " << getHeight() << std::endl;
    std::cout << std::endl;

    for (auto& row : tiles)
    {
        for (auto& t : row)
        {
            t.printTile();
        }
        std::cout << std::endl;
    }

    std::cout << "End" << std::endl << std::endl;
}
