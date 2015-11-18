#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

/* Class: GameObject */
//
// Generalization for every instance in the game that needs to be updated, drawn or process input
//

class GameObject : public sf::Drawable
{
public:
    virtual void event(const sf::Event& event) {};
    virtual void update(const sf::Time& deltatime) {};
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {};
};

#endif // GAMEOBJECT_HPP
