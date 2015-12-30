#ifndef DUNGEONLEVEL_HPP
#define DUNGEONLEVEL_HPP

#include "utils.hpp"
#include "character.hpp"
#include "tilemap.hpp"
#include "actor.hpp"

class DungeonLevel
{
private:
    std::vector<Character> characters;
    std::map<int, Actor> actors;
    Tilemap tilemap;

    int find(const std::string& name) const;

public:
    DungeonLevel();
    ~DungeonLevel();

    void create();

    void newCharacter(const std::string& name);
    void newCharacter(const std::string& name, int x, int y);
    void newCharacter(const std::string& name, const sf::Vector2i& pos);

    int getID(const std::string& name) const;
    int getNumCharacters() const;

    std::string getName(int id) const;
    sf::Vector2i getPosition(int id) const;
    int getMaxHP(int id) const;
    int getHP(int id) const;
    int getAttack(int id) const;
    int getDefense(int id) const;

    sf::Vector2i getPosition(const std::string& name) const;
    int getMaxHP(const std::string& name) const;
    int getHP(const std::string& name) const;
    int getAttack(const std::string& name) const;
    int getDefense(const std::string& name) const;

    int getMapHeight() const;
    int getMapWidth() const;
    bool outOfBounds(int x, int y) const;
    bool outOfBounds(const sf::Vector2i& pos) const;
    Tile getTile(int x, int y) const;
    Tile getTile(const sf::Vector2i& pos) const;
    void getView(matrix<Tile>& view, const sf::IntRect& bounds) const;

    void setMapSize(int x, int y);
    void setMapSize(const sf::Vector2i& s);
    void setTile(int x, int y, Tile value);
    void setTile(const sf::Vector2i& pos, Tile value);

    void setPosition(const std::string& name, int x, int y);
    void setPosition(const std::string& name, const sf::Vector2i& pos);
    void move(const std::string& name, int x, int y);
    void move(const std::string& name, const sf::Vector2i& v);
    void move(int id, int x, int y);
    void move(int id, const sf::Vector2i& v);

    void setMaxHP(const std::string& name, int amount);
    void setHP(const std::string& name, int amount);
    void setAttack(const std::string& name, int amount);
    void setDefense(const std::string& name, int amount);
    void raiseMaxHP(const std::string& name, int amount);
    void raiseHP(const std::string& name, int amount);
    void raiseAttack(const std::string& name, int amount);
    void raiseDefense(const std::string& name, int amount);
    void fullHeal(const std::string& name);

    bool freePosition(int x, int y) const;
    bool freePosition(const sf::Vector2i& p) const;

#ifdef DEBUG
    void printMap() const;
    void printCharacters() const;
#endif
};

#endif // DUNGEONLEVEL_HPP
