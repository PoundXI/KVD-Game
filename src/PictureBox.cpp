#include "PictureBox.hpp"

PictureBox::PictureBox(const sf::Image& image, float x, float y)
    : _image(image) {
    _sprite.SetImage(_image);
    SetPosition(x, y);
}

PictureBox::~PictureBox() {
}

void PictureBox::Update(float elapsedTime) {
}

void PictureBox::Draw(sf::RenderWindow& rw) {
    rw.Draw(_sprite);
}

void PictureBox::SetPosition(float x, float y) {
    _sprite.SetPosition(x, y);
}

sf::Vector2f PictureBox::GetPosition() const {
    return _sprite.GetPosition();
}

float PictureBox::GetWidth() const {
    return _sprite.GetSize().x;
}

float PictureBox::GetHeight() const {
    return _sprite.GetSize().y;
}

sf::Rect<float> PictureBox::GetBoundingRect() const {
    sf::Vector2f size = _sprite.GetSize();
    sf::Vector2f position = _sprite.GetPosition();
    sf::Vector2f center = _sprite.GetCenter();

    float left = position.x - center.x;
    float top = position.y - center.y;
    float right = left + size.x;
    float bottom = top + size.y;

    return sf::Rect<float>(left, top, right, bottom);
}

