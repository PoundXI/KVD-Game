#include "ItemCake.hpp"
#include "Debug.hpp"

#include "WindowPlay.hpp"
#include "ServiceLocator.hpp"
#include "Dinosaur.hpp"

ItemCake::ItemCake(const sf::Image& image, int height, float x, float y, float changeMotionTime)
    : _image(image)
    , _state(Moving1)
    , _changeMotionTime(changeMotionTime)
    , _changeMotionTimeCounter(0) {

    _sprite.SetImage(_image);

    // Get All Rect Position
    std::string map_name[] = {"Moving1", "Moving2", "Moving3"};

    int top = 0;
    for(int i = 0; i < 3; i++) {
        _mapRect[map_name[i]] = sf::IntRect(0, top, _sprite.GetImage()->GetWidth(), height + top);
        top += height;
    }

    _sprite.SetSubRect(_mapRect["Moving1"]);
    _sprite.SetPosition(x, y);
    _sprite.Resize(_sprite.GetSize().x / 2, _sprite.GetSize().y / 2);
    ServiceLocator::GetAudio()->PlaySound("audio/cake-place.ogg");
}

ItemCake::~ItemCake() {
}

void ItemCake::Update(float elapsedTime) {
    if(IsDead()) {
        return;
    }

    //Collision Check
    int dinoCount = WindowPlay::GetDinosaurs().GetObjectCount();
    for(int i = 0; i < dinoCount; i++) {
        Dinosaur* dino = static_cast<Dinosaur*>(WindowPlay::GetDinosaurs().GetObject(i));
        if(!dino->IsDead()) {
            //Collision
            if(dino->GetBoundingRect().Intersects(GetBoundingRect())) {
                if(!dino->IsFliped()) {
                    ServiceLocator::GetAudio()->PlaySound("audio/cake-attack.ogg");
                    dino->Flip();
                    Die();
                    break;
                }
            }
        }
    }

    //Animate Sprite
    _changeMotionTimeCounter += elapsedTime;
    if(_changeMotionTimeCounter < _changeMotionTime) {
        return;
    } else {
        _changeMotionTimeCounter = 0;
    }

    switch(_state) {
        case Moving1:
            _sprite.SetSubRect(_mapRect["Moving2"]);
            _state = Moving2;
            break;
        case Moving2:
            _sprite.SetSubRect(_mapRect["Moving3"]);
            _state = Moving3;
            break;
        case Moving3:
            _sprite.SetSubRect(_mapRect["Moving1"]);
            _state = Moving1;
            break;
    }
}

void ItemCake::Draw(sf::RenderWindow& rw) {
    if(IsDead()) {
        return;
    }
    rw.Draw(_sprite);
}

void ItemCake::SetPosition(float x, float y) {
    _sprite.SetPosition(x, y);
}

sf::Vector2f ItemCake::GetPosition() const {
    return _sprite.GetPosition();
}

float ItemCake::GetWidth() const {
    return _sprite.GetSize().x;
}

float ItemCake::GetHeight() const {
    return _sprite.GetSize().y;
}

sf::Rect<float> ItemCake::GetBoundingRect() const {
    sf::Vector2f size = _sprite.GetSize();
    sf::Vector2f position = _sprite.GetPosition();
    sf::Vector2f center = _sprite.GetCenter();

    float left = position.x - center.x;
    float top = position.y - center.y;
    float right = left + size.x;
    float bottom = top + size.y;

    return sf::Rect<float>(left, top, right, bottom);
}
