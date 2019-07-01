#include "ItemCopter.hpp"

#include "Debug.hpp"
#include "Game.hpp"
#include "ServiceLocator.hpp"

ItemCopter::ItemCopter(const sf::Image& image, int height, float x, float y, int speed, float changeMotionTime)
    : _image(image)
    , _state(Moving1)
    , _flyingBack(false)
    , _x(x)
    , _y(y)
    , _changeMotionTime(changeMotionTime)
    , _changeMotionTimeCounter(0)
    , _moveSpeed(speed)
    , _bomb(NULL) {

    _sprite.SetImage(_image);

    // Get All Rect Position
    std::string map_name[] = {"Moving1", "Moving2", "Moving3"};

    int top = 0;
    for(int i = 0; i < 3; i++) {
        _mapRect[map_name[i]] = sf::IntRect(0, top, _sprite.GetImage()->GetWidth(), height + top);
        top += height;
    }

    _sprite.SetSubRect(_mapRect["Moving1"]);
    _sprite.SetPosition(800, 1);
    ServiceLocator::GetAudio()->PlaySound("audio/copter-place.ogg");
}

ItemCopter::~ItemCopter() {
    if(_bomb != NULL) {
        delete _bomb;
    }
    DEBUG_PRINT("ItemCopter::~ItemCopter()\n");
}

void ItemCopter::Update(float elapsedTime) {
    if(IsDead()) {
        return;
    }

    //Die if missile dead
    if(_bomb != NULL) {
        if(_bomb->IsDead()) {
            Die();
        }
    }

    //Move Sprite
    if(!_flyingBack) {
        _sprite.SetPosition(_sprite.GetPosition().x - _moveSpeed * elapsedTime, _sprite.GetPosition().y);
    } else {
        if(_bomb == NULL) {
            _bomb = new ItemBomb(Game::GetImage("Item_Bomb"), 100, GetTargetPosition().x, GetTargetPosition().y);
        }

        if(_bomb != NULL) {
            _bomb->Update(Game::GetWindow().GetFrameTime());
        }
        _sprite.SetPosition(_sprite.GetPosition().x + _moveSpeed * elapsedTime, _sprite.GetPosition().y);
    }


    //Target X
    if(_sprite.GetPosition().x <= _x) {
        _flyingBack = true;
    }

    //Animate Sprite
    _changeMotionTimeCounter += elapsedTime;
    if(_changeMotionTimeCounter < _changeMotionTime) {
        return;
    } else {
        _changeMotionTimeCounter = 0;
    }

    _sprite.FlipX(_flyingBack);
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

void ItemCopter::Draw(sf::RenderWindow& rw) {
    if(IsDead()) {
        return;
    }
    rw.Draw(_sprite);

    if(_bomb != NULL)
        _bomb->Draw(rw);
}

void ItemCopter::SetPosition(float x, float y) {
    _sprite.SetPosition(x, y);
}

sf::Vector2f ItemCopter::GetPosition() const {
    return _sprite.GetPosition();
}

float ItemCopter::GetWidth() const {
    return _sprite.GetSize().x;
}

float ItemCopter::GetHeight() const {
    return _sprite.GetSize().y;
}

sf::Rect<float> ItemCopter::GetBoundingRect() const {
    sf::Vector2f size = _sprite.GetSize();
    sf::Vector2f position = _sprite.GetPosition();
    sf::Vector2f center = _sprite.GetCenter();

    float left = position.x - center.x;
    float top = position.y - center.y;
    float right = left + size.x;
    float bottom = top + size.y;

    return sf::Rect<float>(left, top, right, bottom);
}

bool ItemCopter::IsFlyingBack() {
    return _flyingBack;
}

sf::Vector2f ItemCopter::GetTargetPosition() const {
    return sf::Vector2f(_x, _y);
}
