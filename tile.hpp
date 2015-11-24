#ifndef TILE_HPP
#define TILE_HPP

#include "utils.hpp"

enum TilePermission {NONE, WALK, WALL, NPERMISSIONS};

class Tile
{
private:
    TilePermission permission;
    int texture_index;

public:
    Tile();
    Tile(const Tile& t);
    Tile(TilePermission p, int i);
    ~Tile();

    void setPermission(TilePermission p);
    void setTextureIndex(int i);

    TilePermission getPermission() const;
    int getTextureIndex() const;

    void printTile() const;
};

#endif // TILE_HPP
