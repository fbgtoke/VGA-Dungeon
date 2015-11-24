#ifndef DUNGEONGENERATOR_HPP
#define DUNGEONGENERATOR_HPP

#include "tilemap.hpp"
#include "utils.hpp"

class DungeonGenerator
{
protected:
    Tilemap& tilemap;
public:
    DungeonGenerator(Tilemap& map);
    virtual ~DungeonGenerator();

    virtual void generate();
};

#endif // DUNGEONGENERATOR_HPP
