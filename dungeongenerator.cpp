#include "dungeongenerator.hpp"

DungeonGenerator::DungeonGenerator(Tilemap& map) : tilemap(map) {}
DungeonGenerator::~DungeonGenerator() {}

void DungeonGenerator::generate()
{
    int width, height;
    std::cin >> width >> height;
    tilemap = Tilemap(width, height);

    TilePermission p[NPERMISSIONS] = {NONE, WALK, WALL};
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int permission;
            std::cin >> permission;
            Tile aux(p[permission], 0);
            tilemap.setTile(j, i, aux);
        }
    }
}
