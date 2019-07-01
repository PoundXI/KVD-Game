#ifndef PICTUREBOX_HPP_INCLUDED
#define PICTUREBOX_HPP_INCLUDED

#include "IVisibleObject.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class PictureBox : public IVisibleObject {
public:
    PictureBox(const sf::Image& image, float x, float y);
    ~PictureBox();

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

#endif // PICTUREBOX_HPP_INCLUDED
