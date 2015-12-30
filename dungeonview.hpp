#ifndef DUNGEONVIEW_HPP
#define DUNGEONVIEW_HPP

#include "utils.hpp"
#include "dungeonlevel.hpp"

class DungeonView : public sf::Drawable
{
private:
    const DungeonLevel& level;

    int tileSize = 16;

public:
    DungeonView(const DungeonLevel& lvl);
    ~DungeonView();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
};

#endif // DUNGEONVIEW_HPP
