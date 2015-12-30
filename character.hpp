#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "utils.hpp"

struct CharacterStats
{
    int maxhp = 0;
    int hp = 0;
    int attack = 0;
    int defense = 0;
};

class Character
{
private:
    std::string name;
    CharacterStats stats;

public:
    Character();
    Character(const std::string& n);
    Character(const Character& original);
    Character(const CharacterStats& s);
    ~Character();

    void setName(const std::string& n);
    void setMaxHP(int amount);
    void setHP(int amount);
    void setAttack(int amount);
    void setDefense(int amount);

    void raiseMaxHP(int amount);
    void raiseHP(int amount);
    void raiseAttack(int amount);
    void raiseDefense(int amount);

    void fullHeal();

    std::string getName() const;
    int getMaxHP() const;
    int getHP() const;
    int getAttack() const;
    int getDefense() const;
};

#endif // CHARACTER_HPP
