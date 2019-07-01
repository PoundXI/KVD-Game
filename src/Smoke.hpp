#ifndef SMOKE_HPP_INCLUDED
#define SMOKE_HPP_INCLUDED

#include "IVisibleObject.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <map>

class Smoke: public IVisibleObject {
public:
    Smoke(const sf::Image& image, int height, float x, float y, float changeMotionTime = 0.1);
    ~Smoke();

    virtual void Update(float elapsedTime);
    virtual void Draw(sf::RenderWindow& rw);

    virtual void SetPosition(float x, float y);
    virtual sf::Vector2f GetPosition() const;
    virtual float GetWidth() const;
    virtual float GetHeight() const;

    virtual sf::Rect<float> GetBoundingRect() const;

    void SetChangeMotionTime(float changeMotionTime);
    enum State {
        Smoke1, Smoke2, Smoke3, Dying
    };
    State GetState();

private:
    sf::Sprite  _sprite;
    const sf::Image& _image;
    std::map<std::string, sf::IntRect> _mapRect;

    State _state;
    float _changeMotionTime;
    float _changeMotionTimeCounter;
};

#endif // SMOKE_HPP_INCLUDED
