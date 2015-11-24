#include "dungeonlevel.hpp"

DungeonLevel::DungeonLevel() {}
DungeonLevel::~DungeonLevel() {}

void DungeonLevel::validateCommand(Command& c, const Character* ch) {}
void DungeonLevel::executeCommand(Command& c, const Character* ch) {}

void DungeonLevel::turn()
{
    Behavior* next = turn_queue.front();
    turn_queue.pop();
    if (next != NULL)
    {
        int id = next->getID();
        Character* character = factory.getCharacter(id);
        sf::Vector2i position = character->getPosition();
        const int radius = 5;
        matrix<Tile>& view = next->getView();

        tilemap.getView(view, position.x, position.y, radius);

        Command c = next->getCommand();
        validateCommand(c, character);
        executeCommand(c, character);

        turn_queue.push(next);
    }
}

int DungeonLevel::getWidth() const { return tilemap.getWidth(); }
int DungeonLevel::getHeight() const { return tilemap.getHeight(); }
void DungeonLevel::getTile(int x, int y, Tile& t) const { tilemap.getTile(x, y, t); }
void DungeonLevel::getAllTiles(matrix<Tile>& t) const { tilemap.getAllTiles(t); }

int DungeonLevel::getNumCharacters() const { return IDs.size(); }
bool DungeonLevel::existsCharacter(int i) { return factory.existsCharacter(i); }
void DungeonLevel::getCharacter(int i, Character& c)
{   
    c = Character(*factory.getCharacter(i));
}
