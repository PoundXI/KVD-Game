#include "ItemCar.hpp"
#include "Debug.hpp"

#include "WindowPlay.hpp"
#include "Dinosaur.hpp"
#include "ServiceLocator.hpp"

ItemCar::ItemCar(const sf::Image& image, int height, float x, float y, int speed, float changeMotionTime)
    : _image(image)
    , _state(StandForLeft)
    , _changeMotionTime(changeMotionTime)
    , _changeMotionTimeCounter(0)
    , _moveSpeed(speed) {

    _sprite.SetImage(_image);

    // Get All Rect Position
    std::string map_name[] = {"Stand", "LeftWalk", "RightWalk"};

    int top = 0;
    for(int i = 0; i < 3; i++) {
        _mapRect[map_name[i]] = sf::IntRect(0, top, _sprite.GetImage()->GetWidth(), height + top);
        top += height;
    }

    _sprite.SetSubRect(_mapRect["Stand"]);
    _sprite.SetPosition(x, y);
    ServiceLocator::GetAudio()->PlaySound("audio/car-place.ogg");
}

ItemCar::~ItemCar() {
    DEBUG_PRINT("ItemCar::~ItemCar()\n");
}

void ItemCar::Update(float elapsedTime) {
    if(IsDead()) {
        return;
    }

    //Die if out of map
    if(GetPosition().x <= GetWidth() * -1) {
        Die();
    }

    //Move Sprite
    _sprite.SetPosition(_sprite.GetPosition().x - _moveSpeed * elapsedTime, _sprite.GetPosition().y);

    //Collision Check
    int dinoCount = WindowPlay::GetDinosaurs().GetObjectCount();
    for(int i = 0; i < dinoCount; i++) {
        Dinosaur* dino = static_cast<Dinosaur*>(WindowPlay::GetDinosaurs().GetObject(i));
        if(!dino->IsDead() && dino->IsFliped() == false) {
            //Collision
            if(dino->GetBoundingRect().Intersects(GetBoundingRect())) {
                dino->Damage(DAMAGE);
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
        case StandForLeft:
            _sprite.SetSubRect(_mapRect["LeftWalk"]);
            _state = LeftWalk;
            break;
        case LeftWalk:
            _sprite.SetSubRect(_mapRect["Stand"]);
            _state = StandForRight;
            break;
        case StandForRight:
            _sprite.SetSubRect(_mapRect["RightWalk"]);
            _state = RightWalk;
            break;
        case RightWalk:
            _sprite.SetSubRect(_mapRect["Stand"]);
            _state = StandForLeft;
            break;
    }
}

void ItemCar::Draw(sf::RenderWindow& rw) {
    if(IsDead()) {
        return;
    }
    rw.Draw(_sprite);
}

void ItemCar::SetPosition(float x, float y) {
    _sprite.SetPosition(x, y);
}

sf::Vector2f ItemCar::GetPosition() const {
    return _sprite.GetPosition();
}

float ItemCar::GetWidth() const {
    return _sprite.GetSize().x;
}

float ItemCar::GetHeight() const {
    return _sprite.GetSize().y;
}

sf::Rect<float> ItemCar::GetBoundingRect() const {
    sf::Vector2f size = _sprite.GetSize();
    sf::Vector2f position = _sprite.GetPosition();
    sf::Vector2f center = _sprite.GetCenter();

    float left = position.x - center.x;
    float top = position.y - center.y;
    float right = left + size.x;
    float bottom = top + size.y;

    return sf::Rect<float>(left, top, right, bottom);
}

int ItemCar::GetDamage() const {
    return DAMAGE;
}
