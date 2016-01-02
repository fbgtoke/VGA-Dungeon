#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "behavior.hpp"

class Player : public Behavior
{
private:
    Direction next;

public:
    Player(int i, const DungeonLevel& lvl);

    void event(const sf::Event& event) final;

    Command getCommand() final;
};

#endif // PLAYER_HPP
