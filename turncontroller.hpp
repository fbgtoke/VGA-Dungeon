#ifndef TURNCONTROLLER_HPP
#define TURNCONTROLLER_HPP

#include "utils.hpp"
#include "behavior.hpp"
#include "dungeonlevel.hpp"

class TurnController
{
private:
    DungeonLevel& level;
    std::queue<Behavior*> turn_queue;

    void validateCommand(Behavior* b, sf::Vector2i& c);
    void executeCommand(Behavior* b, sf::Vector2i& c);

public:
    TurnController(DungeonLevel& lvl);
    ~TurnController();

    void turn();
};

#endif // TURNCONTROLLER_HPP
