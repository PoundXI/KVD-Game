#ifndef ITEMBOMB_HPP_INCLUDED
#define ITEMBOMB_HPP_INCLUDED

#include "IVisibleObject.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <map>

class ItemBomb : public IVisibleObject {
public:
    ItemBomb(const sf::Image& image, int height, float x, float y, int speed = 100, float changeMotionTime = 0.08);
    ~ItemBomb();

    virtual void Update(float elapsedTime);
    virtual void Draw(sf::RenderWindow& rw);

    virtual void SetPosition(float x, float y);
    virtual sf::Vector2f GetPosition() const;
    virtual float GetWidth() const;
    virtual float GetHeight() const;

    virtual sf::Rect<float> GetBoundingRect() const;

    enum State {Moving1, Moving2, Moving3, Dying};
    State GetState();
    sf::Rect<float> GetItemBombAreaRect() const;
private:
    sf::Sprite _sprite;
    const sf::Image& _image;
    std::map<std::string, sf::IntRect> _mapRect;

    State _state;
    float _x;
    float _y;
    float _changeMotionTime;
    float _changeMotionTimeCounter;
    float _moveSpeed;
    static const int DAMAGE = 500;
    static const int RADIUS = 350;
    sf::Shape _missileArea;
};

#endif // ITEMMISSILE_HPP_INCLUDED
