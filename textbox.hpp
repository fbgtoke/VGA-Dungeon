#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include "utils.hpp"

class TextBox : public sf::Drawable
{
private:
    std::vector<std::string> text;
    std::string buffer;

    int lineSize;
    int numLines;

    sf::Time step = sf::Time::Zero;
    sf::Time current = sf::Time::Zero;

    sf::Font font;

    sf::Vector2i position = sf::Vector2i(0, 0);
    int lineHeight = 20;

    void addCharacter();

public:
    TextBox();
    TextBox(int s, int n);
    ~TextBox();

    void event(const sf::Event& event);
    void update(const sf::Time& deltatime);
    void draw(sf::RenderTarget& target, sf::RenderStates) const final;

    void pushText(const std::string& txt);
    void read(std::istream& in);
    void printText() const;

    void flush();

    void setLineSize(int n);
    void setNumLines(int n);
    int getLineSize() const;
    int getNumLines() const;

    bool full() const;

    void setStep(const sf::Time& s);
    sf::Time getStep() const;
    sf::Time timeToNext() const;

    void setFont(const std::string& name);

    void setPosition(int x, int y);
    void setPosition(const sf::Vector2i& p);
    sf::Vector2i getPosition() const;

    void setLineHeight(int height);
    int getLineHeight() const;

#if DEBUG
    void printLine(int n) const;
#endif
};

#endif // TEXTBOX_HPP
