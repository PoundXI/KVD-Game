#ifndef CHECKBOX_HPP_INCLUDED
#define CHECKBOX_HPP_INCLUDED

#include "IVisibleObject.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <map>

class CheckBox : public IVisibleObject {
public:
    CheckBox(const sf::Image& image, int height, float x, float y, bool checked = false);
    ~CheckBox();

    virtual void Update(float elapsedTime);
    virtual void Draw(sf::RenderWindow& rw);

    virtual void SetPosition(float x, float y);
    virtual sf::Vector2f GetPosition() const;
    virtual float GetWidth() const;
    virtual float GetHeight() const;

    virtual sf::Rect<float> GetBoundingRect() const;

    void Check();
    void Uncheck();
    bool IsChecked();

private:
    sf::Sprite  _sprite;
    const sf::Image& _image;
    std::map<std::string, sf::IntRect> _mapRect;

    bool _clickDown;    //for check mouse release
    bool _mouseEnter;    //_mouseOver = false then play sound
    bool _checked;
};

#endif // CHECKBOX_HPP_INCLUDED
