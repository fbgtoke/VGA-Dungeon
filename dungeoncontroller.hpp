#ifndef DUNGEONCONTROLLER_HPP
#define DUNGEONCONTROLLER_HPP

#include "utils.hpp"
#include "dungeonlevel.hpp"
#include "dungeonview.hpp"
#include "turncontroller.hpp"
#include "dungeongenerator.hpp"
#include "nystrom.hpp"
#include "player.hpp"

class DungeonController : public sf::Drawable
{
private:
    DungeonLevel level;
    DungeonView view;
    TurnController turn;

public:
    DungeonController();
    ~DungeonController();

    void create();

    void event(const sf::Event& event);
    void update(const sf::Time& deltatime);
    void draw(sf::RenderTarget& target, sf::RenderStates) const final;
};

#endif // DUNGEONCONTROLLER_HPP
