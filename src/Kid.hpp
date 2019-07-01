#ifndef KID_HPP_INCLUDED
#define KID_HPP_INCLUDED

#include "IVisibleObject.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <map>

class Kid : public IVisibleObject {
public:
    Kid(const sf::Image& image, int height, int speed = 300, float changeMotionTime = 0.05);
    ~Kid();

    virtual void Update(float elapsedTime);
    virtual void Draw(sf::RenderWindow& rw);

    virtual void SetPosition(float x, float y);
    virtual sf::Vector2f GetPosition() const;
    virtual float GetWidth() const;
    virtual float GetHeight() const;

    virtual sf::Rect<float> GetBoundingRect() const;

    enum State {
        Stand, StandForLeft, LeftWalk, StandForRight, RightWalk , Attack1, Attack2, Attack3
    };
    State GetState();

    void ShootBall();
    void MoveUp(float destination);
    void MoveDown(float destination);
private:
    sf::Sprite  _sprite;
    const sf::Image& _image;
    std::map<std::string, sf::IntRect> _mapRect;

    State _state;
    float _changeMotionTime;
    float _changeMotionTimeCounter;
    float _moveSpeed;
};

#endif // KID_HPP_INCLUDED
