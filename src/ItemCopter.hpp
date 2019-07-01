#ifndef ITEMCOPTER_HPP_INCLUDED
#define ITEMCOPTER_HPP_INCLUDED

#include "IVisibleObject.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "ItemBomb.hpp"

#include <map>

class ItemCopter : public IVisibleObject {
public:
    ItemCopter(const sf::Image& image, int height, float x, float y, int speed = 300, float changeMotionTime = 0.05);
    ~ItemCopter();

    virtual void Update(float elapsedTime);
    virtual void Draw(sf::RenderWindow& rw);

    virtual void SetPosition(float x, float y);
    virtual sf::Vector2f GetPosition() const;
    virtual float GetWidth() const;
    virtual float GetHeight() const;

    virtual sf::Rect<float> GetBoundingRect() const;

    bool IsFlyingBack();
    sf::Vector2f GetTargetPosition() const;
private:
    sf::Sprite _sprite;
    const sf::Image& _image;
    std::map<std::string, sf::IntRect> _mapRect;

    enum State {Moving1, Moving2, Moving3};
    State _state;
    bool _flyingBack;
    float _x;
    float _y;
    float _changeMotionTime;
    float _changeMotionTimeCounter;
    float _moveSpeed;

    //Bomb
    ItemBomb* _bomb;
};

#endif // ItemCopter_HPP_INCLUDED
