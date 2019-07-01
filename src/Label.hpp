#ifndef LABEL_HPP_INCLUDED
#define LABEL_HPP_INCLUDED

#include "IVisibleObject.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>

class Label : public IVisibleObject {
public:
    Label(std::string text, int size, float x, float y, sf::Color color = sf::Color::Black);
    ~Label();

    virtual void Update(float elapsedTime);
    virtual void Draw(sf::RenderWindow& rw);

    virtual void SetPosition(float x, float y);
    virtual sf::Vector2f GetPosition() const;
    virtual float GetWidth() const;
    virtual float GetHeight() const;

    virtual sf::Rect<float> GetBoundingRect() const;

    void SetText(std::string text);
    std::string GetText();

private:
    std::string _text;
    sf::String  _sftext;
    sf::Font    _font;
};

#endif // LABEL_HPP_INCLUDED
