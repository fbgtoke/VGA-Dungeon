#include "dungeoncontroller.hpp"

DungeonController::DungeonController() : view(level), turn(level) {}
DungeonController::~DungeonController() {}

void DungeonController::create()
{
    DungeonGenerator generator(level);
    generator.create();
    turn.loadBehaviors();
}

void DungeonController::event(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed
        and event.key.code == sf::Keyboard::Return)
    {
        turn.turn();
    }
}
void DungeonController::update(const sf::Time& deltatime)
{
    view.update(deltatime);
}
void DungeonController::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    target.draw(view);
}
