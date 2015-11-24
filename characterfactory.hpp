#ifndef CHARACTERFACTORY_HPP
#define CHARACTERFACTORY_HPP

#include "utils.hpp"
#include "character.hpp"

class CharacterFactory
{
private:
    std::map<int, Character*> characters;
    int ncharacters;

    int generateIndex(Character* c);

    static const Character NULLCHARACTER;

public:
    CharacterFactory();
    ~CharacterFactory();

    int newCharacter();
    int newCharacter(const sf::Vector2i& pos);
    int newCharacter(const Character& c);
    void eraseCharacter(int i);

    bool existsCharacter(int i);
    Character* getCharacter(int i);
    void copyCharacter(int i, Character& c);

    int getNumCharacters() const;
};

#endif // CHARACTERFACTORY_HPP
