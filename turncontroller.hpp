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

    void validateCommand(Behavior* b, Command& c);
    void executeCommand(Behavior* b, Command& c);

public:
    TurnController(DungeonLevel& lvl);
    ~TurnController();

    void loadBehaviors();

    void turn();
};

#endif // TURNCONTROLLER_HPP
