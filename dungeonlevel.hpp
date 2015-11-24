#ifndef DUNGEONLEVEL_HPP
#define DUNGEONLEVEL_HPP

#include "utils.hpp"
#include "tilemap.hpp"
#include "characterfactory.hpp"
#include "behaviorfactory.hpp"
#include "behavior.hpp"
#include "command.hpp"
#include "dungeongenerator.hpp"

class DungeonLevel
{
private:
    Tilemap tilemap;
    CharacterFactory factory;
    std::vector<int> IDs;
    std::queue<Behavior*> turn_queue;

    void validateCommand(Command& c, const Character* ch);
    void executeCommand(const Command& c, Character* ch);

public:
    DungeonLevel();
    ~DungeonLevel();

    void turn();

    int getWidth() const;
    int getHeight() const;
    void getTile(int x, int y, Tile& t) const;
    void getAllTiles(matrix<Tile>& t) const;

    int getNumCharacters() const;
    bool existsCharacter(int i);
    void getCharacter(int i, Character& c);

    void newCharacter(BehaviorID behavior);
    void newCharacter(BehaviorID behavior, const sf::Vector2i& pos);
};

#endif // DUNGEONLEVEL_HPP
