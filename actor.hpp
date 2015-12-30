#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "utils.hpp"

class Actor
{
private:
    sf::Vector2i position;

public:
    Actor();
    Actor(int x, int y);
    Actor(const sf::Vector2i& p);
    ~Actor();

    void setPosition(int x, int y);
    void setPosition(const sf::Vector2i& p);

    sf::Vector2i getPosition() const;

    void move(int x, int y);
    void move(const sf::Vector2i& v);
};

#endif // ACTOR_HPP
