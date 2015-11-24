#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

#include "utils.hpp"
#include "tile.hpp"
#include "characterfactory.hpp"
#include "command.hpp"

class Behavior
{
protected:
    const int myid;
    matrix<Tile> view;

    const CharacterFactory& factory;

public:
    Behavior(int id, const CharacterFactory& f);
    virtual ~Behavior();

    int getID() const;
    matrix<Tile>& getView();
    
    virtual Command getCommand();
};

#endif // BEHAVIOR_HPP
