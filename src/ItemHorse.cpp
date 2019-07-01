#include "ItemHorse.hpp"
#include "Debug.hpp"

#include "WindowPlay.hpp"
#include "ServiceLocator.hpp"

ItemHorse::ItemHorse(const sf::Image& image, int height, float x, float y, float changeMotionTime)
    : _image(image)
    , _state(Moving1)
    , _changeMotionTime(changeMotionTime)
    , _changeMotionTimeCounter(0)
    , _hpMax(HPMAX)
    , _hp(HPMAX) {

    _sprite.SetImage(_image);

    // Get All Rect Position
    std::string map_name[] = {"Moving1", "Moving2", "Moving3"};

    int top = 0;
    for(int i = 0; i < 3; i++) {
        _mapRect[map_name[i]] = sf::IntRect(0, top, _sprite.GetImage()->GetWidth(), height + top);
        top += height;
    }

    //Create Progressbar
    progressbar = new Progressbar(GetPosition().x, GetPosition().y - 30, 50, 5, 100, sf::Color::Green, sf::Color(220, 220, 220));

    _sprite.SetSubRect(_mapRect["Moving1"]);
    _sprite.SetPosition(x, y);
    _sprite.Resize(_sprite.GetSize().x / 1.5, _sprite.GetSize().y / 1.5);
    ServiceLocator::GetAudio()->PlaySound("audio/horse-place.ogg");
}

ItemHorse::~ItemHorse() {
    delete progressbar;
}

void ItemHorse::Update(float elapsedTime) {
    if(IsDead()) {
        return;
    }

    //if no hp then die
    if(_hp <= 0) {
        //ServiceLocator::GetAudio()->PlaySound("audio/bomb-02.ogg");
        Die();
        WindowPlay::AddSmoke(GetPosition().x, GetPosition().y);
        return;
    }

    //Update Progressbar
    progressbar->SetPosition(GetPosition().x + 30, GetPosition().y);
    progressbar->Update(elapsedTime);

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

void ItemHorse::Draw(sf::RenderWindow& rw) {
    if(IsDead()) {
        return;
    }
    rw.Draw(_sprite);
    if(_hp < _hpMax) {
        progressbar->Draw(rw);
    }
}

void ItemHorse::SetPosition(float x, float y) {
    _sprite.SetPosition(x, y);
}

sf::Vector2f ItemHorse::GetPosition() const {
    return _sprite.GetPosition();
}

float ItemHorse::GetWidth() const {
    return _sprite.GetSize().x;
}

float ItemHorse::GetHeight() const {
    return _sprite.GetSize().y;
}

sf::Rect<float> ItemHorse::GetBoundingRect() const {
    sf::Vector2f size = _sprite.GetSize();
    sf::Vector2f position = _sprite.GetPosition();
    sf::Vector2f center = _sprite.GetCenter();

    float left = position.x - center.x;
    float top = position.y - center.y;
    float right = left + size.x;
    float bottom = top + size.y;

    return sf::Rect<float>(left, top, right, bottom);
}

int ItemHorse::GetHP() {
    return _hp;
}

void ItemHorse::Damage(int damage) {
    _hp -= damage;

    progressbar->SetValue((int)(((float)_hp / (float)_hpMax) * 100.0));

    if(progressbar->GetValue() < 30) {
        progressbar->SetColor(sf::Color::Red);
    } else if(progressbar->GetValue() < 50) {
        progressbar->SetColor(sf::Color::Yellow);
    }
}
