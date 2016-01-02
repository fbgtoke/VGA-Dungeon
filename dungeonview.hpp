#ifndef DUNGEONVIEW_HPP
#define DUNGEONVIEW_HPP

#include "utils.hpp"
#include "dungeonlevel.hpp"

#include "animatedsprite.hpp"

class DungeonView : public sf::Drawable
{
private:
    const DungeonLevel& level;

    int tileSize = 16;
    sf::Texture tileSheet;
    sf::Texture minimapTexture;

    sf::Vector2i center;
    sf::View levelView;
    sf::View minimapView;

    sf::Texture spriteSheet;
    std::map<int, AnimatedSprite> sprites;

    void drawTilemap(sf::RenderTarget& target, const sf::Texture& texture, int width, int height) const;
    void drawCharacters(sf::RenderTarget& target) const;

public:
    DungeonView(const DungeonLevel& lvl);
    ~DungeonView();

    void update(const sf::Time& deltatime);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

    void setTileSize(int size);
    int getTileSize() const;
    void setTileSheet(const std::string& name);

    void newCharacter(int i, const std::string& spritesheet);
};

#endif // DUNGEONVIEW_HPP
