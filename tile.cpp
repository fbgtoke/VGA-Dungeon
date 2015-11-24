#include "tile.hpp"

Tile::Tile() { permission = NONE; texture_index = 0; }
Tile::Tile(const Tile& t) { permission = t.permission; texture_index = t.texture_index; }
Tile::Tile(TilePermission p, int i) : permission(p), texture_index(i) {}
Tile::~Tile() {}

void Tile::setPermission(TilePermission p) { permission = p; }
void Tile::setTextureIndex(int i) { texture_index = i; }

TilePermission Tile::getPermission() const { return permission; }
int Tile::getTextureIndex() const { return texture_index; }

void Tile::printTile() const
{
    static const char p[NPERMISSIONS] = {'X', '.', '#'};
    std::cout << p[permission];
}
