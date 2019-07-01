#include "Wallpaper.hpp"

Wallpaper::Wallpaper(const sf::Image& image)
    : _image(image) {
    _sprite.SetImage(_image);
}

Wallpaper::~Wallpaper() {
}

void Wallpaper::Update(float elapsedTime) {
}

void Wallpaper::Draw(sf::RenderWindow& rw) {
    rw.Draw(_sprite);
}

void Wallpaper::SetPosition(float x, float y) {
    _sprite.SetPosition(x, y);
}

sf::Vector2f Wallpaper::GetPosition() const {
    return _sprite.GetPosition();
}

float Wallpaper::GetWidth() const {
    return _sprite.GetSize().x;
}

float Wallpaper::GetHeight() const {
    return _sprite.GetSize().y;
}

sf::Rect<float> Wallpaper::GetBoundingRect() const {
    sf::Vector2f size = _sprite.GetSize();
    sf::Vector2f position = _sprite.GetPosition();
    sf::Vector2f center = _sprite.GetCenter();

    float left = position.x - center.x;
    float top = position.y - center.y;
    float right = left + size.x;
    float bottom = top + size.y;

    return sf::Rect<float>(left, top, right, bottom);
}

