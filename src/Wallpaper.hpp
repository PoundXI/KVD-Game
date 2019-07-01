#ifndef WALLPAPER_HPP_INCLUDED
#define WALLPAPER_HPP_INCLUDED

#include "IVisibleObject.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Wallpaper : public IVisibleObject {
public:
    Wallpaper(const sf::Image& image);
    ~Wallpaper();

    virtual void Update(float elapsedTime);
    virtual void Draw(sf::RenderWindow& rw);

    virtual void SetPosition(float x, float y);
    virtual sf::Vector2f GetPosition() const;
    virtual float GetWidth() const;
    virtual float GetHeight() const;

    virtual sf::Rect<float> GetBoundingRect() const;

private:
    sf::Sprite  _sprite;
    const sf::Image& _image;
};

#endif // WALLPAPER_HPP_INCLUDED
