#include "dungeongenerator.hpp"

DungeonGenerator::DungeonGenerator(DungeonLevel& lvl) : level(lvl) {}
DungeonGenerator::~DungeonGenerator() {}

void DungeonGenerator::create()
{
    // Tilemap
    int width, height;
    std::cin >> width >> height;

    level.setMapSize(width, height);
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int t;
            std::cin >> t;

            static Tile tiles[] = {NONE, WALL, WALK};
            level.setTile(j, i, tiles[t]);
        }
    }

    // Characters
    int nchars;
    std::cin >> nchars;

    for (int i = 0; i < nchars; ++i)
    {
        std::string name;
        int x, y;
        int hp, atk, def;
        std::cin >> name >> x >> y;
        std::cin >> hp >> atk >> def;

        level.newCharacter(name, x, y);
        level.setMaxHP(name, hp);
        level.setAttack(name, atk);
        level.setDefense(name, def);
        level.fullHeal(name);
    }
}
