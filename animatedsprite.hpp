#ifndef ANIMATEDSPRITE_HPP
#define ANIMATEDSPRITE_HPP

#include "utils.hpp"

typedef sf::IntRect Frame;
class AnimatedSprite : public sf::Sprite
{
private:
    std::list<Frame> frames;
    sf::Time frameTime = sf::Time::Zero;
    bool playing = true;
    bool looping = true;

    int currFrame = 0;
    std::list<Frame>::iterator it = frames.begin();
    sf::Time currTime = sf::Time::Zero;

public:
    AnimatedSprite();
    AnimatedSprite(const sf::Texture& tex);

    void update(const sf::Time& deltatime);

    void addFrame(const Frame& rect);

    void start();
    void start(const sf::Time& time);
    void pause();
    void stop();
    void toggle();

    int getNumFrames() const;
    int currentFrame() const;

    void setFrameTime(const sf::Time& time);

    void setLooping(bool loop);

    bool isPlaying() const;
    bool isLooping() const;
    bool hasEnded() const;
};

#endif // ANIMATEDSPRITE_HPP
