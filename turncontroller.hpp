#ifndef TURNCONTROLLER_HPP
#define TURNCONTROLLER_HPP

#include "utils.hpp"
#include "behavior.hpp"
#include "dungeonlevel.hpp"

class TurnController
{
private:
    DungeonLevel& level;
    std::list<Behavior*> turn_queue;

    void validateCommand(Behavior* b, Command& c);
    void executeCommand(Behavior* b, Command& c);

public:
    TurnController(DungeonLevel& lvl);
    ~TurnController();

    void event(const sf::Event& event);

    void newCharacter(const std::string& name, int x, int y, Behavior* b);

    void turn();
};

#endif // TURNCONTROLLER_HPP
