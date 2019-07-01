#include "ItemDuck.hpp"
#include "ServiceLocator.hpp"
#include "Debug.hpp"
#include "WindowPlay.hpp"
#include "Dinosaur.hpp"
#include "Game.hpp"

ItemDuck::ItemDuck(const sf::Image& image, int height, float x, float y, int speed, float changeMotionTime)
    : _image(image)
    , _state(Moving1)
    , _changeMotionTime(changeMotionTime)
    , _changeMotionTimeCounter(0)
    , _moveSpeed(speed) {

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
    _sprite.SetCenter(_sprite.GetSize().x / 2, _sprite.GetSize().y / 2);
    _sprite.Resize(_sprite.GetSize().x / 2, _sprite.GetSize().y / 2);
}

ItemDuck::~ItemDuck() {
}

void ItemDuck::Update(float elapsedTime) {
    if(IsDead()) {
        return;
    }

    //Die if out of map
    if(GetPosition().x <= GetWidth() * -1) {
        Die();
    }

    //Collision Check
    int dinoCount = WindowPlay::GetDinosaurs().GetObjectCount();
    for(int i = 0; i < dinoCount; i++) {
        Dinosaur* dino = static_cast<Dinosaur*>(WindowPlay::GetDinosaurs().GetObject(i));
        if(!dino->IsDead() && dino->IsFliped() == false) {
            //Collision
            if(dino->GetBoundingRect().Intersects(GetBoundingRect())) {
                dino->Damage(GetDamage());
                WindowPlay::AddSmoke(GetPosition().x - 50, GetPosition().y - 50);
                Die();
            }
        }
    }

    //Move Sprite
    _sprite.Rotate(5);
    _sprite.SetPosition(_sprite.GetPosition().x - _moveSpeed * elapsedTime, _sprite.GetPosition().y);

    //Animate Sprite
    _changeMotionTimeCounter += elapsedTime;
    if(_changeMotionTimeCounter < _changeMotionTime) {
        return;
    } else {
        _changeMotionTimeCounter = 0;
    }
}

void ItemDuck::Draw(sf::RenderWindow& rw) {
    if(IsDead()) {
        return;
    }
    rw.Draw(_sprite);
}

void ItemDuck::SetPosition(float x, float y) {
    _sprite.SetPosition(x, y);
}

sf::Vector2f ItemDuck::GetPosition() const {
    return _sprite.GetPosition();
}

float ItemDuck::GetWidth() const {
    return _sprite.GetSize().x;
}

float ItemDuck::GetHeight() const {
    return _sprite.GetSize().y;
}

sf::Rect<float> ItemDuck::GetBoundingRect() const {
    sf::Vector2f size = _sprite.GetSize();
    sf::Vector2f position = _sprite.GetPosition();
    sf::Vector2f center = _sprite.GetCenter();

    float left = position.x - center.x;
    float top = position.y - center.y;
    float right = left + size.x;
    float bottom = top + size.y;

    return sf::Rect<float>(left, top, right, bottom);
}

int ItemDuck::GetDamage() const {
    return DAMAGE;
}

void ItemDuck::Die() {
    if(GetPosition().x > 0
            && GetPosition().x < Game::SCREEN_WIDTH
            && GetPosition().y > 0
            && GetPosition().y < Game::SCREEN_HEIGHT) {
        //ServiceLocator::GetAudio()->PlaySound("audio/smack-1.ogg");
    }
    IVisibleObject::Die();
}

ItemDuck::State ItemDuck::GetState() {
    return _state;
}
