#include "dungeonlevel.hpp"

DungeonLevel::DungeonLevel() {}
DungeonLevel::~DungeonLevel() {}

void DungeonLevel::create() {}

void DungeonLevel::newCharacter(const std::string& name)
{
    int pos = find(name);
    if (pos != -1) throw "Character already exists";

    Tile tile = tilemap.getTile(0, 0);
    if (tile != WALK) throw "Could not create character at default position";
    if (not freePosition(0, 0)) throw "Could not create character at default position";

    int newID = getNumCharacters();
    characters.push_back(Character(name));
    actors[newID] = sf::Vector2i(0, 0);
}
void DungeonLevel::newCharacter(const std::string& name, int x, int y)
{
    int pos = find(name);
    if (pos != -1) throw "Character already exists";

    if (outOfBounds(x, y)) throw "Spawn position out of bounds";
    Tile tile = tilemap.getTile(x, y);
    if (tile != WALK) throw "Spawn position invalid";
    if (not freePosition(0, 0)) throw "Spawn position already ocupied";

    int newID = getNumCharacters();
    characters.push_back(Character(name));
    actors[newID] = sf::Vector2i(x, y);
}
void DungeonLevel::newCharacter(const std::string& name, const sf::Vector2i& pos)
{
    int id = find(name);
    if (id != -1) throw "Character already exists";

    if (outOfBounds(pos)) throw "Spawn position out of bounds";
    Tile tile = tilemap.getTile(pos);
    if (tile != WALK) throw "Spawn position invalid";
    if (not freePosition(pos)) throw "Spawn position already ocupied";

    int newID = getNumCharacters();
    characters.push_back(Character(name));
    actors[newID] = pos;
}

int DungeonLevel::getID(const std::string& name) const
{
    int pos = find(name);
    if (pos == -1) throw "Character does not exist";

    return pos;
}
int DungeonLevel::getNumCharacters() const { return characters.size(); }

std::string DungeonLevel::getName(int id) const
{
    if (id >= getNumCharacters()) throw "Wrong ID trying to get name";
    return characters[id].getName();
}
sf::Vector2i DungeonLevel::getPosition(int id) const
{
    if (id >= getNumCharacters()) throw "Wrong ID trying to get position";
    return actors.at(id).getPosition();
}
int DungeonLevel::getMaxHP(int id) const
{
    if (id >= getNumCharacters()) throw "Wrong ID trying to get maxhp";
    return characters[id].getMaxHP();
}
int DungeonLevel::getHP(int id) const
{
    if (id >= getNumCharacters()) throw "Wrong ID trying to get hp";
    return characters[id].getHP();
}
int DungeonLevel::getAttack(int id) const
{
    if (id >= getNumCharacters()) throw "Wrong ID trying to get attack";
    return characters[id].getAttack();
}
int DungeonLevel::getDefense(int id) const
{
    if (id >= getNumCharacters()) throw "Wrong ID trying to get defense";
    return characters[id].getDefense();
}

sf::Vector2i DungeonLevel::getPosition(const std::string& name) const
{
    int pos = find(name);
    if (pos == -1) throw "Character does not exist";

    return actors.at(pos).getPosition();
}
int DungeonLevel::getMaxHP(const std::string& name) const
{
    int pos = find(name);
    if (pos == -1) throw "Character does not exist";

    return characters[pos].getMaxHP();
}
int DungeonLevel::getHP(const std::string& name) const
{
    int pos = find(name);
    if (pos == -1) throw "Character does not exist";

    return characters[pos].getHP();
}
int DungeonLevel::getAttack(const std::string& name) const
{
    int pos = find(name);
    if (pos == -1) throw "Character does not exist";

    return characters[pos].getAttack();
}
int DungeonLevel::getDefense(const std::string& name) const
{
    int pos = find(name);
    if (pos == -1) throw "Character does not exist";

    return characters[pos].getDefense();
}

int DungeonLevel::getMapHeight() const { return tilemap.getHeight(); }
int DungeonLevel::getMapWidth() const { return tilemap.getWidth(); }
bool DungeonLevel::outOfBounds(int x, int y) const { return tilemap.outOfBounds(x, y); }
bool DungeonLevel::outOfBounds(const sf::Vector2i& pos) const { return tilemap.outOfBounds(pos); }
Tile DungeonLevel::getTile(int x, int y) const { return tilemap.getTile(x, y); }
Tile DungeonLevel::getTile(const sf::Vector2i& pos) const { return tilemap.getTile(pos); }
void DungeonLevel::getView(matrix<Tile>& view, const sf::IntRect& bounds) const { tilemap.copyMap(view, bounds); }

void DungeonLevel::setMapSize(int x, int y) { tilemap = Tilemap(x, y); }
void DungeonLevel::setMapSize(const sf::Vector2i& s) { tilemap = Tilemap(s.x, s.y); }
void DungeonLevel::setTile(int x, int y, Tile value) { tilemap.setTile(x, y, value); }
void DungeonLevel::setTile(const sf::Vector2i& pos, Tile value) { tilemap.setTile(pos, value); }

void DungeonLevel::setPosition(const std::string& name, int x, int y)
{
    if (tilemap.outOfBounds(x, y)) throw "Position out of bounds";
    Tile tile = tilemap.getTile(x, y);
    if (tile != WALK) throw "Invalid position";
    if (not freePosition(x, y)) throw "Position already ocupied";

    int pos = find(name);
    if (pos == -1) throw "Character does not exist";

    actors[pos].setPosition(x, y);
}
void DungeonLevel::setPosition(const std::string& name, const sf::Vector2i& pos)
{
    if (tilemap.outOfBounds(pos)) throw "Position out of bounds";
    Tile tile = tilemap.getTile(pos);
    if (tile != WALK) throw "Invalid position";
    if (not freePosition(pos)) throw "Position already ocupied";

    int p = find(name);
    if (p == -1) throw "Character does not exist";

    actors[p].setPosition(pos);
}
void DungeonLevel::move(const std::string& name, int x, int y)
{
    int pos = find(name);
    if (pos == -1) throw "Character does not exist";

    sf::Vector2i newpos = actors[pos].getPosition() + sf::Vector2i(x, y);
    if (tilemap.outOfBounds(newpos)) throw "Position out of bounds";
    Tile tile = tilemap.getTile(newpos);
    if (tile != WALK) throw "Invalid position";
    if (not freePosition(newpos)) throw "Position already ocupied";

    actors[pos].move(x, y);
}
void DungeonLevel::move(const std::string& name, const sf::Vector2i& v)
{
    int pos = find(name);
    if (pos == -1) throw "Character does not exist";

    sf::Vector2i newpos = actors[pos].getPosition() + v;
    if (tilemap.outOfBounds(newpos)) throw "Position out of bounds";
    Tile tile = tilemap.getTile(newpos);
    if (tile != WALK) throw "Invalid position";
    if (not freePosition(newpos)) throw "Position already ocupied";

    actors[pos].move(v);
}
void DungeonLevel::move(int id, int x, int y)
{
    if (id >= getNumCharacters()) throw "Wrong ID";

    sf::Vector2i newpos = actors[id].getPosition() + sf::Vector2i(x, y);
    if (tilemap.outOfBounds(newpos)) throw "Position out of bounds";
    Tile tile = tilemap.getTile(newpos);
    if (tile != WALK) throw "Invalid position";
    if (not freePosition(newpos)) throw "Position already ocupied";

    actors[id].move(x, y);
}
void DungeonLevel::move(int id, const sf::Vector2i& v)
{
    if (id >= getNumCharacters()) throw "Wrong ID";

    sf::Vector2i newpos = actors[id].getPosition() + v;
    if (tilemap.outOfBounds(newpos)) throw "Position out of bounds";
    Tile tile = tilemap.getTile(newpos);
    if (tile != WALK) throw "Invalid position";
    if (not freePosition(newpos)) throw "Position already ocupied";

    actors[id].move(v);
}

void DungeonLevel::setMaxHP(const std::string& name, int amount)
{
    int pos = find(name);
    if (pos == -1) throw "Character does not exist";

    characters[pos].setMaxHP(amount);
}
void DungeonLevel::setHP(const std::string& name, int amount)
{
    int pos = find(name);
    if (pos == -1) throw "Character does not exist";

    characters[pos].setHP(amount);
}
void DungeonLevel::setAttack(const std::string& name, int amount)
{
    int pos = find(name);
    if (pos == -1) throw "Character does not exist";

    characters[pos].setAttack(amount);
}
void DungeonLevel::setDefense(const std::string& name, int amount)
{
    int pos = find(name);
    if (pos == -1) throw "Character does not exist";

    characters[pos].setDefense(amount);
}
void DungeonLevel::raiseMaxHP(const std::string& name, int amount)
{
    int pos = find(name);
    if (pos == -1) throw "Character does not exist";

    characters[pos].raiseMaxHP(amount);
}
void DungeonLevel::raiseHP(const std::string& name, int amount)
{
    int pos = find(name);
    if (pos == -1) throw "Character does not exist";

    characters[pos].raiseHP(amount);
}
void DungeonLevel::raiseAttack(const std::string& name, int amount)
{
    int pos = find(name);
    if (pos == -1) throw "Character does not exist";

    characters[pos].raiseAttack(amount);
}
void DungeonLevel::raiseDefense(const std::string& name, int amount)
{
    int pos = find(name);
    if (pos == -1) throw "Character does not exist";

    characters[pos].raiseDefense(amount);
}
void DungeonLevel::fullHeal(const std::string& name)
{
    int pos = find(name);
    if (pos == -1) throw "Character does not exist";

    characters[pos].fullHeal();
}

int DungeonLevel::find(const std::string& name) const
{
    for (int i = 0; i < characters.size(); ++i)
        if (characters[i].getName() == name) return i;

    return -1;
}
bool DungeonLevel::freePosition(int x, int y) const
{
    for (int i = 0; i < characters.size(); ++i)
        if (actors.at(i).getPosition() == sf::Vector2i(x, y))
            return false;

    return true;
}
bool DungeonLevel::freePosition(const sf::Vector2i& p) const
{
    for (int i = 0; i < characters.size(); ++i)
        if (actors.at(i).getPosition() == p)
            return false;

    return true;
}

#if DEBUG
void DungeonLevel::printMap() const
{
    std::cout << "################" << std::endl;
    std::cout << "#Printing map: #" << std::endl;
    std::cout << "################" << std::endl;

    int height = getMapHeight();
    int width = getMapWidth();
    std::cout << "Dimensions: " << width << "x" << height << std::endl;

    for (int i = 0; i < height; ++i)
    {
        std::cout << std::endl;
        for (int j = 0; j < width; ++j)
        {
            Tile tile = tilemap.getTile(j, i);
            std::cout << tile << " ";
        }
    }

    std::cout << std::endl << std::endl;
}

void DungeonLevel::printCharacters() const
{
    std::cout << "#######################" << std::endl;
    std::cout << "#Printing characters: #" << std::endl;
    std::cout << "#######################" << std::endl;

    int nchars = getNumCharacters();
    std::cout << "Total number: " << nchars << std::endl << std::endl;

    for (int i = 0; i < nchars; ++i)
    {
        sf::Vector2i pos = actors.at(i).getPosition();

        std::cout << "#" << i << ": " << characters[i].getName() << std::endl;
        std::cout << "@(" << pos.x << "," << pos.y << ")" << std::endl;
        std::cout << "HP: " << characters[i].getHP() << "/" << characters[i].getMaxHP() << std::endl;
        std::cout << "Atk: " << characters[i].getAttack() << std::endl;
        std::cout << "Def: " << characters[i].getDefense() << std::endl;
        std::cout << std::endl;
    }

    std::cout << std::endl;
}
#endif
