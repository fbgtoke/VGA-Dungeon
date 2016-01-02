#include "animatedsprite.hpp"

AnimatedSprite::AnimatedSprite()
{
    setTextureRect(sf::IntRect(0, 0, 0, 0));
}

AnimatedSprite::AnimatedSprite(const sf::Texture& tex) : Sprite(tex)
{
    setTextureRect(sf::IntRect(0, 0, 0, 0));
}

void AnimatedSprite::update(sf::Time& deltatime)
{
    if (playing and frames.size() > 0)
    {
        if (not (not looping and hasEnded()))
        {
            currTime += deltatime;

            while (currTime > frameTime)
            {
                currTime -= frameTime;

                currFrame = (currFrame+1)%frames.size();

                ++it;
                if (it == frames.end())
                    it = frames.begin();
                setTextureRect(*it);
            }
        }
    }
}

void AnimatedSprite::addFrame(const Frame& rect)
{
    frames.push_back(rect);

    if (frames.size() == 1)
    {
        sf::IntRect rect = frames.front();
        setTextureRect(rect);
    }
}

void AnimatedSprite::start() { playing = true; }

void AnimatedSprite::start(const sf::Time& time)
{
    playing = true;
    frameTime = time;
}

void AnimatedSprite::pause() { playing = false; }

void AnimatedSprite::stop()
{
    playing = false;
    currFrame = 0;
    it = frames.begin();
}

void AnimatedSprite::toggle() { playing = not playing; }

int AnimatedSprite::getNumFrames() const { return frames.size(); }
int AnimatedSprite::currentFrame() const { return currFrame; }

void AnimatedSprite::setFrameTime(const sf::Time& time) { frameTime = time; }

void AnimatedSprite::setLooping(bool loop) { looping = loop; }

bool AnimatedSprite::isPlaying() const { return playing; }
bool AnimatedSprite::isLooping() const { return looping; }
bool AnimatedSprite::hasEnded() const { return currFrame == frames.size()-1; }
