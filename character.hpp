#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "utils.hpp"

class Character
{
private:
    sf::Vector2i pos;

    int maxhp, hp;
    int attack, defense;

public:
    Character();
    Character(const sf::Vector2i& p);
    Character(const Character& c);
    Character(int hp, int atk, int def);
    ~Character();

    void setMaxHP(int amount);
    void setHP(int amount);
    void setAttack(int amount);
    void setDefense(int amount);

    int getMaxHP() const;
    int getHP() const;
    int getAttack() const;
    int getDefense() const;

    void raiseMaxHP(int amount);
    void raiseHP(int amount);
    void raiseAttack(int amount);
    void raiseDefense(int amount);

    void fullHeal();

    void setPosition(int x, int y);
    void move(int x, int y);
    sf::Vector2i getPosition() const;
};

#endif // CHARACTER_HPP
