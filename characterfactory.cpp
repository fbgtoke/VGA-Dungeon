#include "characterfactory.hpp"

CharacterFactory::CharacterFactory() { ncharacters = 0; }
CharacterFactory::~CharacterFactory() {}

int CharacterFactory::generateIndex(Character* c) { return ncharacters; }

int CharacterFactory::newCharacter()
{
    Character* c = new Character();
    int index = generateIndex(c);
    characters[index] = c;
    ++ncharacters;
}

int CharacterFactory::newCharacter(const Character& c)
{
    Character* newchar = new Character(c);
    int index = generateIndex(newchar);
    characters[index] = newchar;
    ++ncharacters;
}

void CharacterFactory::eraseCharacter(int i)
{
    if (characters[i] != NULL)
    {
        delete characters[i];
        characters[i] = NULL;
        --ncharacters;
    }
}

bool CharacterFactory::existsCharacter(int i) { return characters[i] != NULL; }

Character* CharacterFactory::getCharacter(int i)
{
    if (characters[i] != NULL) return characters[i];
    else return new Character(NULLCHARACTER);
}
void CharacterFactory::copyCharacter(int i, Character& c)
{
    if (characters[i] != NULL)
    {
        c = Character(*characters[i]);
    }
}

int CharacterFactory::getNumCharacters() const { return ncharacters; }

const Character CharacterFactory::NULLCHARACTER = Character();
