#include "Smoke.hpp"
#include "ServiceLocator.hpp"
#include "Debug.hpp"

Smoke::Smoke(const sf::Image& image, int height, float x, float y, float changeMotionTime)
    : _image(image)
    , _state(Smoke1)
    , _changeMotionTime(changeMotionTime)
    , _changeMotionTimeCounter(0) {

    _sprite.SetImage(_image);

    // Get All Rect Position
    std::string map_name[] = {"Smoke1", "Smoke2", "Smoke3"};
    int top = 0;
    for(int i = 0; i < 3; i++) {
        _mapRect[map_name[i]] = sf::IntRect(0, top, _sprite.GetImage()->GetWidth(), height + top);
        top += height;
    }

    _sprite.SetSubRect(_mapRect["Smoke1"]);
    _sprite.SetPosition(x, y);
}

Smoke::~Smoke() {
}

void Smoke::Update(float elapsedTime) {
    if(IsDead()) {
        return;
    }

    //Animate Sprite
    _changeMotionTimeCounter += elapsedTime;
    if(_changeMotionTimeCounter < _changeMotionTime) {
        return;
    } else {
        _changeMotionTimeCounter = 0;
    }

    switch(_state) {
        case Smoke1:
            _sprite.SetSubRect(_mapRect["Smoke1"]);
            _state = Smoke2;
            break;
        case Smoke2:
            _sprite.SetSubRect(_mapRect["Smoke2"]);
            _state = Smoke3;
            break;
        case Smoke3:
            _sprite.SetSubRect(_mapRect["Smoke3"]);
            _state = Dying;
            break;
        case Dying:
            Die();
            break;
    }
}

void Smoke::Draw(sf::RenderWindow& rw) {
    if(IsDead()) {
        return;
    }
    rw.Draw(_sprite);
}

void Smoke::SetPosition(float x, float y) {
    _sprite.SetPosition(x, y);
}

sf::Vector2f Smoke::GetPosition() const {
    return _sprite.GetPosition();
}

float Smoke::GetWidth() const {
    return _sprite.GetSize().x;
}

float Smoke::GetHeight() const {
    return _sprite.GetSize().y;
}

sf::Rect<float> Smoke::GetBoundingRect() const {
    sf::Vector2f size = _sprite.GetSize();
    sf::Vector2f position = _sprite.GetPosition();
    sf::Vector2f center = _sprite.GetCenter();

    float left = position.x - center.x;
    float top = position.y - center.y;
    float right = left + size.x;
    float bottom = top + size.y;

    return sf::Rect<float>(left, top, right, bottom);
}

void Smoke::SetChangeMotionTime(float changeMotionTime) {
    if(changeMotionTime >= 0.1 && changeMotionTime <= 3.0) {
        _changeMotionTime = changeMotionTime;
    }
}

Smoke::State Smoke::GetState() {
    return _state;
}
