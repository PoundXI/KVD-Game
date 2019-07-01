#include "Label.hpp"

Label::Label(std::string text, int size, float x, float y, sf::Color color) {
    _font = sf::Font::GetDefaultFont();
    _sftext.SetFont(_font);
    _sftext.SetSize(size);
    _sftext.SetPosition(x , y);
    _sftext.SetColor(color);
    SetText(text);
}

Label::~Label() {}

void Label::Update(float elapsedTime) {}

void Label::Draw(sf::RenderWindow& rw) {
    rw.Draw(_sftext);
}

void Label::SetText(std::string text) {
    _text = text;
    _sftext.SetText(_text);
}

std::string Label::GetText() {
    return _text;
}

void Label::SetPosition(float x, float y) {
    _sftext.SetPosition(x, y);
}

sf::Vector2f Label::GetPosition() const {
    return _sftext.GetPosition();
}

float Label::GetWidth() const {
    return _sftext.GetRect().GetWidth();
}

float Label::GetHeight() const {
    return _sftext.GetRect().GetHeight();
}

sf::Rect<float> Label::GetBoundingRect() const {
    return _sftext.GetRect();
}
