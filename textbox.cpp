#include "textbox.hpp"

TextBox::TextBox() {}
TextBox::TextBox(int s, int n)
{
    assert (s >= 0);
    assert (n >= 0);

    lineSize = s;
    numLines = n;
    text = std::vector<std::string> (numLines);
}
TextBox::~TextBox()
{
    flush();
}

void TextBox::addCharacter()
{
    int i = 0;
    while (i < numLines and text[i].size() == lineSize)
        ++i;

    if (i < numLines and buffer.size() > 0)
    {
        char c = buffer.front();
        if (c == '\n') while (text[i].size() < lineSize)
            text[i] += " ";
        else
            text[i] += buffer.front();
        buffer.erase(0, 1);
    }
}

void TextBox::event(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed
        and event.key.code == sf::Keyboard::Space)
    {
        if (full()) flush();
        else while(not full() and buffer.size() > 0) addCharacter();
    }
}
void TextBox::update(const sf::Time& deltatime)
{
    current += deltatime;
    if (current >= step)
    {
        current -= step;
        if (not full()) addCharacter();
    }
}
void TextBox::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    sf::Text txt;
    txt.setFont(font);
    txt.setColor(sf::Color::Black);

    for (int i = 0; i < numLines; ++i)
    {
        txt.setString(text[i]);
        txt.setPosition(position.x, position.y + lineHeight * i);
        target.draw(txt);
    }
}

void TextBox::pushText(const std::string& txt)
{
    buffer += txt;
}
void TextBox::read(std::istream& in)
{
    char s[256];
    in.read(s, 256);
    buffer.append(s);
}
void TextBox::printText() const
{
    for (int i = 0; i < numLines; ++i)
    {
        int length = text[i].size();
        for (int j = 0; j < length; ++j)
        {
            std::cout << text[i][j];
        }
        std::cout << std::endl;
    }
}

void TextBox::flush()
{
    text = std::vector<std::string> (numLines);
}

void TextBox::setLineSize(int n)
{
    assert (n >= 0);
    lineSize = n;
    text = std::vector<std::string> (n);
}
void TextBox::setNumLines(int n)
{
    assert (n >= 0);
    numLines = n;
    text = std::vector<std::string> (n);
}
int TextBox::getLineSize() const { return lineSize; }
int TextBox::getNumLines() const { return numLines; }

bool TextBox::full() const
{
    return text[numLines-1].size() == lineSize;
}

void TextBox::setStep(const sf::Time& s) { step = s; }
sf::Time TextBox::getStep() const { return step; }
sf::Time TextBox::timeToNext() const { return step - current; }

void TextBox::setFont(const std::string& name)
{
    if (not font.loadFromFile(resources + name))
        throw "Failed to load font";
}

void TextBox::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
}
void TextBox::setPosition(const sf::Vector2i& p) { position = p; }
sf::Vector2i TextBox::getPosition() const { return position; }

void TextBox::setLineHeight(int height)
{
    assert (height >= 0);
    lineHeight = height;
}
int TextBox::getLineHeight() const { return lineHeight; }

#if DEBUG
void TextBox::printLine(int n) const
{
    assert (n >= 0 and n < numLines);
    std::cerr << text[n] << std::endl;
}
#endif

