#include "turncontroller.hpp"

TurnController::TurnController(DungeonLevel& lvl) : level(lvl)
{
    int nchars = level.getNumCharacters();
    for (int i = 0; i < nchars; ++i)
    {
        Behavior* b = new Behavior(i, level);
        turn_queue.push(b);
    }
}

TurnController::~TurnController()
{
    while (not turn_queue.empty())
    {
        Behavior* b = turn_queue.front();
        turn_queue.pop();
        delete b;
    }
}

void TurnController::turn()
{
    if (not turn_queue.empty())
    {
        Behavior* next = turn_queue.front();
        turn_queue.pop();

        int id = next->getID();
        auto view = next->getView();
        sf::Vector2i pos = level.getPosition(id);
        static const int RADIUS = 3;
        level.getView(view, sf::IntRect(pos.x-RADIUS, pos.y-RADIUS, RADIUS*2+1, RADIUS*2+1));

        sf::Vector2i c;
        try { c = next->getCommand(); }
        catch (...) { std::cerr << "caught exception" << std::endl; }

        validateCommand(next, c);
        executeCommand(next, c);

        turn_queue.push(next);
    }
}

void TurnController::validateCommand(Behavior* b, sf::Vector2i& c)
{
    int id = b->getID();
    sf::Vector2i pos = level.getPosition(id);

    Tile dest = level.getTile(pos+c);
    if (dest != WALK or not level.freePosition(pos+c)) c = sf::Vector2i(0, 0);
}
void TurnController::executeCommand(Behavior* b, sf::Vector2i& c)
{
    try { level.move(b->getID(), c); }
    catch (...) {}
}
