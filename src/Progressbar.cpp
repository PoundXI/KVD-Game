#include "Progressbar.hpp"
#include "Debug.hpp"

Progressbar::Progressbar(
    float x, float y, float width, float height, int value, sf::Color progressColor, sf::Color backgroundColor)
    : _value(value)
    , _x(x)
    , _y(y)
    , _width(width)
    , _height(height)
    , _backgroundColor(backgroundColor)
    , _progressColor(progressColor) {

    _backgroundShape = sf::Shape::Line(_x, _y, _x + _width , _y, _height,  _backgroundColor);
    _progressShape = sf::Shape::Line(_x, _y, _x + (_width * _value / 100) , _y, _height, _progressColor);
}

Progressbar::~Progressbar() {
}

void Progressbar::Update(float elapsedTime) {
}

void Progressbar::Draw(sf::RenderWindow& rw) {
    rw.Draw(_backgroundShape);
    rw.Draw(_progressShape);
}

void Progressbar::SetPosition(float x, float y) {
    _x = x;
    _y = y;
    UpdateBar();
}

sf::Vector2f Progressbar::GetPosition() const {
    return sf::Vector2f(_x, _y);
}

float Progressbar::GetWidth() const {
    return _width;
}

float Progressbar::GetHeight() const {
    return _height;
}

sf::Rect<float> Progressbar::GetBoundingRect() const {
    return sf::Rect<float>(_x, _y, _x + _width, _y + _height);
}

void Progressbar::SetValue(int value) {
    if(value >= 0 && value <= 100) {
        _value = value;
        UpdateBar();
    }
}

int Progressbar::GetValue() {
    return _value;
}

void Progressbar::IncreaseValue() {
    if(GetValue() < 100) {
        SetValue(_value + 1);
        UpdateBar();
    }
}

void Progressbar::DecreaseValue() {
    if(GetValue() > 0) {
        SetValue(_value - 1);
        UpdateBar();
    }
}

void Progressbar::IncreaseValue(int value) {
    if(_value + value < 100) {
        SetValue(_value + value);
    } else {
        SetValue(100);
    }
    UpdateBar();
}

void Progressbar::DecreaseValue(int value) {
    if(_value + value > 0) {
        SetValue(_value - 1);
    } else {
        SetValue(0);
    }
    UpdateBar();
}

void Progressbar::UpdateBar() {
    _backgroundShape = sf::Shape::Line(_x, _y, _x + _width , _y, _height,  _backgroundColor);
    _progressShape = sf::Shape::Line(_x, _y, _x + (_width * _value / 100) , _y, _height, _progressColor);
}

void Progressbar::SetColor(sf::Color progressColor, sf::Color backgroundColor) {
    _backgroundColor = backgroundColor;
    _progressColor = progressColor;
}
