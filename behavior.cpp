#include "behavior.hpp"

Behavior::Behavior(int id, const DungeonLevel& lvl) : ID(id), level(lvl) {}
Behavior::~Behavior() {}

int Behavior::getID() const { return ID; }
std::string Behavior::getName() const { return level.getName(ID); }
int Behavior::getMaxHP() const { return level.getMaxHP(ID); }
int Behavior::getHP() const { return level.getHP(ID); }
int Behavior::getAttack() const { return level.getAttack(ID); }
int Behavior::getDefense() const { return level.getDefense(ID); }

matrix<Tile>& Behavior::getView() { return view; }

bool Behavior::isEmpty(int x, int y) const // relative to self
{
    if (not contained(x, y)) throw "Tile not within view";

    sf::Vector2i pos = level.getPosition(ID) + sf::Vector2i(x, y);
    return level.freePosition(pos);
}
bool Behavior::isEmpty(const sf::Vector2i& p) const // relative to self
{
    if (not contained(p)) throw "Tile not within view";

    sf::Vector2i pos = level.getPosition(ID) + p;
    return level.freePosition(pos);
}

Tile Behavior::getTile(int x, int y) const // relative to self
{
    if (not contained(x, y)) throw "Tile not within view";
    return level.getTile(x, y);
}
Tile Behavior::getTile(const sf::Vector2i& p) const // relative to self
{
    if (not contained(p)) throw "Tile not within view";
    return level.getTile(p);
}

sf::Vector2i Behavior::getCommand()
{
    int d = rand()%4;
    static sf::Vector2i dirs[] = {UP, DOWN, LEFT, RIGHT};
    return dirs[d];
}

bool Behavior::contained(int x, int y) const
{
    int radius = view.size()/2;
    return x >= -radius and x <= radius and y >= -radius and y <= radius;
}
bool Behavior::contained(const sf::Vector2i& p) const
{
    int radius = view.size()/2;
    return p.x >= -radius and p.x <= radius and p.y >= -radius and p.y <= radius;
}
