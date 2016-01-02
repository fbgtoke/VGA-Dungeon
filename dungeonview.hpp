#ifndef DUNGEONVIEW_HPP
#define DUNGEONVIEW_HPP

#include "utils.hpp"
#include "dungeonlevel.hpp"

class DungeonView : public sf::Drawable
{
private:
    const DungeonLevel& level;

    int tileSize = 16;
    sf::Texture tileSheet;

    sf::View levelView;
    sf::View GUIView;

    void drawTilemap(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawCharacters(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    DungeonView(const DungeonLevel& lvl);
    ~DungeonView();

    void update(const sf::Time& deltatime);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

    void setTileSize(int size);
    int getTileSize() const;

    void setTileSheet(const std::string& name);
};

#endif // DUNGEONVIEW_HPP
