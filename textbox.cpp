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

    if (i < numLines)
    {
        std::cerr << buffer.front();
        text[i] += buffer.front();
        buffer.erase(0, 1);
    }
}

void TextBox::event(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed
        and event.key.code == sf::Keyboard::Space
        and full())
    {
        flush();
    }
}
void TextBox::update(const sf::Time& deltatime)
{
    current += deltatime;
    while (current >= step)
    {
        std::cerr << "frame" << std::endl;
        current -= step;
        if (not full()) addCharacter();
    }
}
void TextBox::draw(sf::RenderTarget& target, sf::RenderStates) const
{

}

void TextBox::pushText(const std::string& txt)
{
    buffer += txt;
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
    text.clear();
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

#if DEBUG
void TextBox::printLine(int n) const
{
    assert (n >= 0 and n < numLines);
    std::cerr << text[n] << std::endl;
}
#endif

