#ifndef ITEMCAR_HPP_INCLUDED
#define ITEMCAR_HPP_INCLUDED

#include "IVisibleObject.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <map>

class ItemCar : public IVisibleObject {
public:
    ItemCar(const sf::Image& image, int height, float x, float y, int speed = 200, float changeMotionTime = 0.05);
    ~ItemCar();

    virtual void Update(float elapsedTime);
    virtual void Draw(sf::RenderWindow& rw);

    virtual void SetPosition(float x, float y);
    virtual sf::Vector2f GetPosition() const;
    virtual float GetWidth() const;
    virtual float GetHeight() const;

    virtual sf::Rect<float> GetBoundingRect() const;

    int GetDamage() const;
private:
    sf::Sprite _sprite;
    const sf::Image& _image;
    std::map<std::string, sf::IntRect> _mapRect;

    enum State {StandForLeft, LeftWalk, StandForRight, RightWalk};
    State _state;
    float _changeMotionTime;
    float _changeMotionTimeCounter;
    float _moveSpeed;
    static const int DAMAGE = 3;
};

#endif // ItemCar_HPP_INCLUDED
