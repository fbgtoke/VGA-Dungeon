#include "character.hpp"

Character::Character() {}
Character::Character(const std::string& n) : name(n) {};
Character::Character(const Character& original)
{
    name = original.name;
    stats = original.stats;
}
Character::Character(const CharacterStats& s) : stats(s) {}
Character::~Character() {}

void Character::setName(const std::string& n) { name = n; }
void Character::setMaxHP(int amount)
{
    assert (amount >= 0 and amount >= stats.hp);
    stats.maxhp = amount;
}
void Character::setHP(int amount)
{
    assert (amount >= 0 and amount <= stats.maxhp);
    stats.hp = amount;
}
void Character::setAttack(int amount)
{
    assert (amount >= 0);
    stats.attack = amount;
}
void Character::setDefense(int amount)
{
    assert (amount >= 0);
    stats.defense = amount;
}

void Character::raiseMaxHP(int amount)
{
    assert (stats.maxhp + amount >= 0 and stats.maxhp + amount >= stats.hp);
    stats.maxhp += amount;
}
void Character::raiseHP(int amount)
{
    assert (stats.hp + amount >= 0 and stats.hp + amount <= stats.maxhp);
    stats.hp += amount;
}
void Character::raiseAttack(int amount)
{
    assert (stats.attack + amount >= 0);
    stats.attack += amount;
}
void Character::raiseDefense(int amount)
{
    assert (stats.defense + amount >= 0);
    stats.defense += amount;
}

void Character::fullHeal() { stats.hp = stats.maxhp; }

std::string Character::getName() const { return name; }
int Character::getMaxHP() const { return stats.maxhp; }
int Character::getHP() const { return stats.hp; }
int Character::getAttack() const { return stats.attack; }
int Character::getDefense() const { return stats.defense; }
