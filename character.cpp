#include "character.hpp"

Character::Character() { maxhp = hp = defense = attack = 0; }
Character::Character(const Character& c)
{
    maxhp = c.maxhp;
    hp = c.hp;
    attack = c.attack;
    defense = c.defense;
}
Character::Character(int hp, int atk, int def) : maxhp(hp), hp(hp), attack(atk), defense(def) {}
Character::~Character() {}

void Character::setMaxHP(int amount)
{
    if (amount >= 0)
    {
        maxhp = amount;
        if (hp > maxhp) hp = maxhp;
    }
}
void Character::setHP(int amount)
{
    if (amount >= 0)
    {
        if (amount > maxhp) hp = maxhp;
        else hp = amount;
    }
}
void Character::setAttack(int amount) { if (amount >= 0) attack = amount; }
void Character::setDefense(int amount) { if (amount >= 0) defense = amount; }

int Character::getMaxHP() const { return maxhp; }
int Character::getHP() const { return hp; }
int Character::getAttack() const { return attack; }
int Character::getDefense() const { return defense; }

void Character::raiseMaxHP(int amount)
{
    maxhp += amount;
    if (maxhp < 0) maxhp = 0;
}
void Character::raiseHP(int amount)
{
    hp += amount;
    if (hp < 0) hp = 0;
    if (hp > maxhp) hp = maxhp;
}
void Character::raiseAttack(int amount)
{
    attack += amount;
    if (attack < 0) attack = 0;
}
void Character::raiseDefense(int amount)
{
    defense += amount;
    if (defense < 0) defense = 0;
}

void Character::fullHeal()
{
    hp = maxhp;
}

void Character::setPosition(int x, int y) { pos.x = x; pos.y = y; }
void Character::move(int x, int y) { pos.x += x; pos.y += y; }
sf::Vector2i Character::getPosition() const { return pos; }
