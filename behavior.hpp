#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

#include "utils.hpp"
#include "dungeonlevel.hpp"

class Behavior
{
private:
    const int ID;
    const DungeonLevel& level;
    matrix<Tile> view;

    bool contained(int x, int y) const;
    bool contained(const sf::Vector2i& p) const;

public:
    Behavior(int id, const DungeonLevel& lvl);
    ~Behavior();

    int getID() const;
    std::string getName() const;
    int getMaxHP() const;
    int getHP() const;
    int getAttack() const;
    int getDefense() const;

    matrix<Tile>& getView();

    bool isEmpty(int x, int y) const; // relative to self
    bool isEmpty(const sf::Vector2i& p) const; // relative to self

    Tile getTile(int x, int y) const; // relative to self
    Tile getTile(const sf::Vector2i& p) const; // relative to self

    void getNameAt(int x, int y, std::string& name) const; // relative to self
    void getNameAt(const sf::Vector2i& pos, std::string& name) const; // relative to self

    virtual sf::Vector2i getCommand();
};

#endif // BEHAVIOR_HPP
