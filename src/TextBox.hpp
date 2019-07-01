#ifndef TEXTBOX_HPP_INCLUDED
#define TEXTBOX_HPP_INCLUDED

#include "IVisibleObject.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>

class TextBox : public IVisibleObject {
public:
    TextBox(float x, float y, float width, float height
            , std::string text = ""
                                 , sf::Color textColor = sf::Color::Black
                                         , sf::Color boxColor = sf::Color::White);
    ~TextBox();

    virtual void Update(float elapsedTime);
    virtual void Draw(sf::RenderWindow& rw);

    virtual void SetPosition(float x, float y);
    virtual sf::Vector2f GetPosition() const;
    virtual float GetWidth() const;
    virtual float GetHeight() const;

    virtual sf::Rect<float> GetBoundingRect() const;

    static char GetKeyPressed(sf::Event event);
    void SetText(std::string text);
    std::string GetText();
    void Append(std::string text);
    void Append(char c);
    void Remove();

private:
    static const int MAX_SIZE = 6;
    std::string _text;
    float _x;
    float _y;
    float _width;
    float _height;

    sf::Color _textColor;
    sf::Color _boxColor;

    sf::String  _sftext;
    sf::Font    _font;
    sf::Shape _boxShape;
    sf::Shape _cursorShape;
    float _changeMotionTime;
    float _changeMotionTimeCounter;
    bool _cursorBlink;
};


#endif // TEXTBOX_HPP_INCLUDED

