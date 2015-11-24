#include "dungeonlevel.hpp"

DungeonLevel::DungeonLevel()
{
    DungeonGenerator g(tilemap);
    g.generate();
}
DungeonLevel::~DungeonLevel() {}

void DungeonLevel::validateCommand(Command& c, const Character* ch)
{
    CommandType type = c.getType();
    CommandDirection dir = c.getDirection();
    sf::Vector2i pos = ch->getPosition();
    switch (type)
    {
    case MOVE:
        switch(dir)
        {
        case LEFT:
            if (pos.x <= 0 or tilemap.checkPermission(pos.x-1, pos.y) != WALK)
                c.setType(IDLE);
            break;
        case RIGHT:
            if (pos.x >= tilemap.getWidth()-1 or tilemap.checkPermission(pos.x+1, pos.y) != WALK)
                c.setType(IDLE);
            break;
        case UP:
            if (pos.y <= 0 or tilemap.checkPermission(pos.x, pos.y-1) != WALK)
                c.setType(IDLE);
            break;
        case DOWN:
            if (pos.y >= tilemap.getHeight()-1 or tilemap.checkPermission(pos.x, pos.y+1) != WALK)
                c.setType(IDLE);
            break;
        default:
            break;
        }
    default:
        break;
    }
}
void DungeonLevel::executeCommand(const Command& c, Character* ch)
{
    CommandType type = c.getType();
    CommandDirection dir = c.getDirection();
    switch (type)
    {
    case IDLE:
        break;
    case MOVE:
        switch (dir)
        {
        case UP:
            ch->move(0, -1);
            break;
        case DOWN:
            ch->move(0, 1);
            break;
        case LEFT:
            ch->move(-1, 0);
            break;
        case RIGHT:
            ch->move(1, 0);
            break;
        default:
            break;
        }
    default:
        break;
    }
}

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
    int n = IDs.size();
    if (i >= n) return;
    int index = IDs[i];
    c = Character(*factory.getCharacter(index));
}

void DungeonLevel::newCharacter(BehaviorID b)
{
    int id = factory.newCharacter();
    IDs.push_back(id);
    Behavior* behavior = BehaviorFactory::getBehavior(b, id, factory);
    turn_queue.push(behavior);
}
void DungeonLevel::newCharacter(BehaviorID b, const sf::Vector2i& pos)
{
    int id = factory.newCharacter(pos);
    IDs.push_back(id);
    Behavior* behavior = BehaviorFactory::getBehavior(b, id, factory);
    turn_queue.push(behavior);
}
