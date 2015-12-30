#ifndef DUNGEONGENERATOR_HPP
#define DUNGEONGENERATOR_HPP

#include "utils.hpp"
#include "dungeonlevel.hpp"

class DungeonGenerator
{
protected:
    DungeonLevel& level;

public:
    DungeonGenerator(DungeonLevel& lvl);
    virtual ~DungeonGenerator();

    virtual void create();
};

#endif // DUNGEONGENERATOR_HPP
