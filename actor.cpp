#include "actor.hpp"

Actor::Actor()
{
    position.x = 0;
    position.y = 0;
}
Actor::Actor(int x, int y)
{
    position.x = x;
    position.y = y;
}
Actor::Actor(const sf::Vector2i& p)
{
    position.x = p.x;
    position.y = p.y;
}
Actor::~Actor() {}

void Actor::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
}
void Actor::setPosition(const sf::Vector2i& p) { position = p; }

sf::Vector2i Actor::getPosition() const { return position; }

void Actor::move(int x, int y)
{
    position.x += x;
    position.y += y;
}
void Actor::move(const sf::Vector2i& v)
{
    position.x += v.x;
    position.y += v.y;
}
