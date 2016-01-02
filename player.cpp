#include "player.hpp"

Player::Player(int i, const DungeonLevel& lvl) : Behavior(i, lvl)
{
    next = Direction(0, 0);
}


void Player::event(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Left:
            if (next != RIGHT)
                next = LEFT;
            break;
        case sf::Keyboard::Right:
            if (next != LEFT)
                next = RIGHT;
            break;
        case sf::Keyboard::Up:
            if (next != DOWN)
                next = UP;
            break;
        case sf::Keyboard::Down:
            if (next != UP)
                next = DOWN;
            break;
        default:
            next = Direction(0, 0);
            break;
        }
    }
    else if (event.type == sf::Event::KeyReleased)
        next = Direction(0, 0);
}

Command Player::getCommand()
{
    if (next == Direction(0, 0)) return Command(IDLE, UP);
    return Command(MOVE, next);
}
