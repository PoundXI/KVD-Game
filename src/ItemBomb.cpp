#include "ItemBomb.hpp"

#include "Debug.hpp"
#include "WindowPlay.hpp"
#include "Dinosaur.hpp"
#include "ServiceLocator.hpp"

#include <cmath>

ItemBomb::ItemBomb(const sf::Image& image, int height, float x, float y, int speed, float changeMotionTime)
    : _image(image)
    , _state(Moving1)
    , _x(x)
    , _y(y)
    , _changeMotionTime(changeMotionTime)
    , _changeMotionTimeCounter(0)
    , _moveSpeed(speed) {

    DEBUG_PRINT("ItemBomb::ItemBomb()\n");

    _sprite.SetImage(_image);

    // Get All Rect Position
    std::string map_name[] = {"Moving1", "Moving2", "Moving3"};

    int top = 0;
    for(int i = 0; i < 3; i++) {
        _mapRect[map_name[i]] = sf::IntRect(0, top, _sprite.GetImage()->GetWidth(), height + top);
        top += height;
    }

    _sprite.SetSubRect(_mapRect["Moving1"]);
    _sprite.SetPosition(_x, 1);
    _sprite.SetCenter(_sprite.GetSize().x / 2, _sprite.GetSize().y / 2);

    //Missile Area
    _missileArea = sf::Shape::Circle(_x
                                     , _y
                                     , RADIUS
                                     , sf::Color(255, 255, 255, 50));
}

ItemBomb::~ItemBomb() {
    DEBUG_PRINT("ItemBomb::~ItemBomb()\n");
}

void ItemBomb::Update(float elapsedTime) {
    if(IsDead()) {
        return;
    }

    //Move Sprite
    _sprite.SetPosition(_sprite.GetPosition().x, _sprite.GetPosition().y + _moveSpeed * elapsedTime);

    //Target X
    if(_state != Dying) {
        if(_sprite.GetPosition().y >= _y) {
            //Collision Check
            int dinoCount = WindowPlay::GetDinosaurs().GetObjectCount();
            for(int i = 0; i < dinoCount; i++) {
                Dinosaur* dino = static_cast<Dinosaur*>(WindowPlay::GetDinosaurs().GetObject(i));
                if(!dino->IsDead() && dino->IsFliped() == false) {
                    //Collision
                    float distance = sqrt(pow(dino->GetPosition().x - GetPosition().x, 2) + pow(dino->GetPosition().y - GetPosition().y, 2));
                    float damagePercent = (RADIUS - distance) / (float)RADIUS;
                    if(distance <= RADIUS) {
                        dino->Damage(damagePercent * DAMAGE);
                        Die();
                    }
                }
            }
            WindowPlay::AddSmoke(GetPosition().x - _sprite.GetCenter().x, GetPosition().y - _sprite.GetCenter().y);
            //ServiceLocator::GetAudio()->PlaySound("audio/bomb-02.ogg");
            _state = Dying;
            return;
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
        case Dying:
            Die();
            break;
    }
}

void ItemBomb::Draw(sf::RenderWindow& rw) {
    if(IsDead()) {
        return;
    }

    rw.Draw(_missileArea);
    rw.Draw(_sprite);
}

void ItemBomb::SetPosition(float x, float y) {
    _sprite.SetPosition(x, y);
}

sf::Vector2f ItemBomb::GetPosition() const {
    return _sprite.GetPosition();
}

float ItemBomb::GetWidth() const {
    return _sprite.GetSize().x;
}

float ItemBomb::GetHeight() const {
    return _sprite.GetSize().y;
}

sf::Rect<float> ItemBomb::GetBoundingRect() const {
    sf::Vector2f size = _sprite.GetSize();
    sf::Vector2f position = _sprite.GetPosition();
    sf::Vector2f center = _sprite.GetCenter();

    float left = position.x - center.x;
    float top = position.y - center.y;
    float right = left + size.x;
    float bottom = top + size.y;

    return sf::Rect<float>(left, top, right, bottom);
}

sf::Rect<float> ItemBomb::GetItemBombAreaRect() const {
    sf::Vector2f size = _sprite.GetSize();
    sf::Vector2f position = _sprite.GetPosition();
    sf::Vector2f center = _sprite.GetCenter();

    //double size
    float left = position.x - center.x - size.x / 2;
    float top = position.y - center.y - size.y / 2;
    float right = left + size.x * 2;
    float bottom = top + size.y * 2 ;

    return sf::Rect<float>(left, top, right, bottom);
}

ItemBomb::State ItemBomb::GetState() {
    return _state;
}
