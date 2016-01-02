#include "dungeoncontroller.hpp"

DungeonController::DungeonController() : view(level), turn(level) {}
DungeonController::~DungeonController() {}

void DungeonController::create()
{
    Nystrom generator(level);

    int w, h;
    int mrooms, Mrooms;
    int mw, Mw, mh, Mh;
    int a;
    std::cin >> w >> h >> mrooms >> Mrooms >> mw >> Mw >> mh >> Mh >> a;
    generator.setSize(w, h);
    generator.setNumRooms(mrooms, Mrooms);
    generator.setRoomSize(mw, Mw, mh, Mh);
    generator.setPlaceAttempts(a);
    generator.create();

    bool placed = false;
    while (not placed)
    {
        try {
            level.newCharacter("Test", rand()%w, rand()%h);
            placed = true;
        }
        catch (...) {}
    }
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
