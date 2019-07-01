#ifndef PROGRESSBAR_HPP_INCLUDED
#define PROGRESSBAR_HPP_INCLUDED

#include "IVisibleObject.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Progressbar : public IVisibleObject {
public:
    Progressbar(float x, float y, float width, float height, int value = 0
                , sf::Color progressColor = sf::Color::Red
                                            , sf::Color backgroundColor = sf::Color(220, 220, 220));
    ~Progressbar();

    virtual void Update(float elapsedTime);
    virtual void Draw(sf::RenderWindow& rw);

    virtual void SetPosition(float x, float y);
    virtual sf::Vector2f GetPosition() const;
    virtual float GetWidth() const;
    virtual float GetHeight() const;

    virtual sf::Rect<float> GetBoundingRect() const;

    void SetValue(int value);
    int GetValue();

    void IncreaseValue();
    void IncreaseValue(int value);
    void DecreaseValue();
    void DecreaseValue(int value);

    void SetColor(sf::Color progressColor, sf::Color backgroundColor = sf::Color(220, 220, 220));

private:
    int _value;
    float _x;
    float _y;
    float _width;
    float _height;
    sf::Shape _progressShape;
    sf::Shape _backgroundShape;
    sf::Color _backgroundColor;
    sf::Color _progressColor;
    void UpdateBar();
};

#endif // PROGRESSBAR_HPP_INCLUDED
