#ifndef DINOSAUR_HPP_INCLUDED
#define DINOSAUR_HPP_INCLUDED

#include "IVisibleObject.hpp"
#include "Progressbar.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <map>

class Dinosaur: public IVisibleObject {
public:
    Dinosaur(const sf::Image& image, int height, float x, float y
             , int hp = 100, int damage = 1, int speed = 10, float changeMotionTime = 0.1);
    ~Dinosaur();

    virtual void Update(float elapsedTime);
    virtual void Draw(sf::RenderWindow& rw);

    virtual void SetPosition(float x, float y);
    virtual sf::Vector2f GetPosition() const;
    virtual float GetWidth() const;
    virtual float GetHeight() const;

    virtual sf::Rect<float> GetBoundingRect() const;

    void SetSpeed(int speed);
    void SetChangeMotionTime(float changeMotionTime);
    void Flip();
    bool IsFliped();

    int GetHP();
    void Damage(int damage);

    enum State {
        StandForLeft, LeftWalk, StandForRight, RightWalk
        , Attacked, Attacking1, Attacking2, Dying
    };
    State GetState();

private:
    sf::Sprite  _sprite;
    const sf::Image& _image;
    std::map<std::string, sf::IntRect> _mapRect;

    State _state;
    float _changeMotionTime;
    float _changeMotionTimeCounter;
    float _moveSpeed;
    int   _hp;
    int   _hpMax;
    int   _damage;
    bool _isMouseReleased;
    bool _flip;

    Progressbar* progressbar;
};

#endif // DINOSAUR_HPP_INCLUDED
