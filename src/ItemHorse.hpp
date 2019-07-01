#ifndef ITEMHORSE_HPP_INCLUDED
#define ITEMHORSE_HPP_INCLUDED

#include "IVisibleObject.hpp"
#include "Progressbar.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <map>

class ItemHorse : public IVisibleObject {
public:
    ItemHorse(const sf::Image& image, int height, float x, float y, float changeMotionTime = 0.1);
    ~ItemHorse();

    virtual void Update(float elapsedTime);
    virtual void Draw(sf::RenderWindow& rw);

    virtual void SetPosition(float x, float y);
    virtual sf::Vector2f GetPosition() const;
    virtual float GetWidth() const;
    virtual float GetHeight() const;

    virtual sf::Rect<float> GetBoundingRect() const;

    int GetHP();
    void Damage(int damage);

    enum State {Moving1, Moving2, Moving3};

    State GetState();

private:
    sf::Sprite  _sprite;
    const sf::Image& _image;
    std::map<std::string, sf::IntRect> _mapRect;

    State _state;
    float _changeMotionTime;
    float _changeMotionTimeCounter;
    int   _hp;
    int   _hpMax;
    static const int HPMAX = 500;
    Progressbar* progressbar;
};

#endif // ItemHorse_HPP_INCLUDED
