#ifndef Button_HPP_INCLUDED
#define Button_HPP_INCLUDED

#include "IVisibleObject.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <map>

class Button : public IVisibleObject {
public:
    Button(const sf::Image& image, int height, float x, float y, bool enable = true);
    ~Button();

    virtual void Update(float elapsedTime);
    virtual void Draw(sf::RenderWindow& rw);

    virtual void SetPosition(float x, float y);
    virtual sf::Vector2f GetPosition() const;
    virtual float GetWidth() const;
    virtual float GetHeight() const;

    virtual sf::Rect<float> GetBoundingRect() const;

    void SetEnable(bool enable);
    bool IsEnable();

    enum State {
        Nothing , MouseOver, MouseDown, MouseReleased, MouseLeave
    };
    State GetState();

private:
    sf::Sprite  _sprite;
    const sf::Image& _image;
    std::map<std::string, sf::IntRect> _mapRect;

    State _state;
    bool _mouseClickedDown;        //for check mouse release
    bool _mouseEntered;            //_mouseOver = false then play sound
    bool _enable;
};

#endif // Button_HPP_INCLUDED

