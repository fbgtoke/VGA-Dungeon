#ifndef DUNGEONVIEW_HPP
#define DUNGEONVIEW_HPP

#include "utils.hpp"
#include "dungeonlevel.hpp"

class DungeonView : public sf::Drawable
{
private:
    const DungeonLevel& level;

    int tileSize = 16;

    sf::View levelView;
    sf::View GUIView;

public:
    DungeonView(const DungeonLevel& lvl);
    ~DungeonView();

    void update(const sf::Time& deltatime);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
};

#endif // DUNGEONVIEW_HPP
