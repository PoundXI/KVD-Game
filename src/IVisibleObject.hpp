#ifndef VISIBLEOBJECT_HPP_INCLUDED
#define VISIBLEOBJECT_HPP_INCLUDED

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class IVisibleObject {
public:
    IVisibleObject() : _dead(false) {}
    virtual ~IVisibleObject() {}

    virtual void Draw(sf::RenderWindow& window) = 0;
    virtual void Update(float elapsedTime) = 0;

    virtual void SetPosition(float x, float y) = 0;
    virtual sf::Vector2f GetPosition() const = 0;
    virtual float GetWidth() const = 0;
    virtual float GetHeight() const = 0;

    virtual sf::Rect<float> GetBoundingRect() const = 0;

    virtual bool IsDead() {
        return _dead;
    }
    virtual void Die() {
        _dead = true;
    }
protected:
    bool _dead;
};

#endif // VISIBLEGAMEOBJECT_HPP_INCLUDED
