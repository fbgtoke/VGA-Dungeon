#include "utils.hpp"
#include "textbox.hpp"

int main()
{
    int s, n;
    std::cin >> s >> n;
    float time;
    std::cin >> time;

    TextBox box(s, n);
    box.setStep(sf::seconds(time));
    std::cout << "Step: " << box.getStep().asSeconds() << std::endl;

    std::string in;
    while (std::cin >> in)
        box.pushText(in);

    sf::Clock clk;
    while (true)
    {
        sf::Time deltatime = clk.getElapsedTime();
        box.update(deltatime);
    }
}
