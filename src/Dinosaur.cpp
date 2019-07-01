#include "Dinosaur.hpp"
#include "SFMLMouseState.hpp"
#include "Game.hpp"
#include "ServiceLocator.hpp"

#include "Progressbar.hpp"
#include "Debug.hpp"

#include "WindowPlay.hpp"
#include "ItemHorse.hpp"
#include "ItemCake.hpp"

Dinosaur::Dinosaur(const sf::Image& image, int height, float x, float y, int hp, int damage, int speed, float changeMotionTime)
    : _image(image)
    , _state(StandForLeft)
    , _changeMotionTime(changeMotionTime)
    , _changeMotionTimeCounter(0)
    , _moveSpeed(speed)
    , _hp(hp)
    , _hpMax(hp)
    , _damage(damage)
    , _isMouseReleased(true)
    , _flip(false) {

    _sprite.SetImage(_image);

    // Get All Rect Position
    std::string map_name[] = {"Stand", "LeftWalk", "RightWalk", "Attacked", "Attacking"};
    int top = 0;
    for(int i = 0; i < 5; i++) {
        _mapRect[map_name[i]] = sf::IntRect(0, top, _sprite.GetImage()->GetWidth(), height + top);
        top += height;
    }

    _sprite.SetSubRect(_mapRect["Stand"]);
    _sprite.SetPosition(x, y);
    _sprite.SetCenter(_sprite.GetSize().x / 2, _sprite.GetSize().y / 2);

    //Create Progressbar
    progressbar = new Progressbar(_sprite.GetPosition().x - 20, _sprite.GetPosition().y - 80, 50, 5, 100, sf::Color::Green, sf::Color(220, 220, 220));
}

Dinosaur::~Dinosaur() {
    delete progressbar;
}

void Dinosaur::Update(float elapsedTime) {
    if(IsDead()) {
        return;
    }

    //Die if out of map
    if(GetPosition().x <= GetWidth() * -1 - 1) {
        Die();
        WindowPlay::AddSmoke(GetPosition().x, GetPosition().y);
    }

    //if no hp then die
    if(_hp <= 0) {
        ServiceLocator::GetAudio()->PlaySound("audio/dinosaur-die.ogg");
        Die();
        WindowPlay::AddSmoke(GetPosition().x, GetPosition().y);
        WindowPlay::AddItem();
        return;
    }

    //Collision Check
    bool attack = false;
    int dinoCount = WindowPlay::GetDinosaurs().GetObjectCount();
    for(int i = 0; i < dinoCount; i++) {
        Dinosaur* dino = static_cast<Dinosaur*>(WindowPlay::GetDinosaurs().GetObject(i));
        if(!dino->IsDead()) {
            //Is Enemy
            if(dino->IsFliped() != IsFliped()) {
                //Collision
                if(dino->GetBoundingRect().Intersects(GetBoundingRect())) {
                    attack = true;
                    if(_state != Attacking1 && _state != Attacking2) {
                        dino->Damage(_damage);
                        _state = Attacking1;
                    }
                    break;
                }
            }
        }
    }

    int horseCount = WindowPlay::GetHorses().GetObjectCount();
    for(int i = 0; i < horseCount ; i++) {
        ItemHorse* horse = static_cast<ItemHorse*>(WindowPlay::GetHorses().GetObject(i));
        if(!horse->IsDead()) {
            //Collision
            if(!IsFliped()) {
                if(horse->GetBoundingRect().Intersects(GetBoundingRect())) {
                    attack = true;
                    if(_state != Attacking1 && _state != Attacking2) {
                        horse->Damage(_damage);
                        _state = Attacking1;
                    }
                    break;
                }
            }
        }
    }

    //Move Sprite
    if(!attack) {
        if(!_flip) {
            SetPosition(GetPosition().x + _moveSpeed * elapsedTime, GetPosition().y);
        } else {
            SetPosition(GetPosition().x - _moveSpeed * elapsedTime, GetPosition().y);
        }
    }

    //Update Progressbar
    progressbar->SetPosition(_sprite.GetPosition().x - 20, _sprite.GetPosition().y - 50);
    progressbar->Update(elapsedTime);

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
        case Attacked:
            _sprite.SetSubRect(_mapRect["Attacked"]);
            _state = StandForLeft;
            break;
        case Attacking1:
            _sprite.SetSubRect(_mapRect["Attacking"]);
            _state = Attacking2;
            break;
        case Attacking2:
            _sprite.SetSubRect(_mapRect["Stand"]);
            _state = StandForLeft;;
            break;
    }
}

void Dinosaur::Draw(sf::RenderWindow& rw) {
    if(IsDead()) {
        return;
    }

    rw.Draw(_sprite);
    if(_hp < _hpMax) {
        progressbar->Draw(rw);
    }
}


void Dinosaur::SetPosition(float x, float y) {
    _sprite.SetPosition(x, y);
}

sf::Vector2f Dinosaur::GetPosition() const {
    return _sprite.GetPosition();
}

float Dinosaur::GetWidth() const {
    return _sprite.GetSize().x;
}

float Dinosaur::GetHeight() const {
    return _sprite.GetSize().y;
}

sf::Rect<float> Dinosaur::GetBoundingRect() const {
    sf::Vector2f size = _sprite.GetSize();
    sf::Vector2f position = _sprite.GetPosition();
    sf::Vector2f center = _sprite.GetCenter();

    float left = position.x - center.x;
    float top = position.y - center.y;
    float right = left + size.x;
    float bottom = top + size.y;

    return sf::Rect<float>(left, top, right, bottom);
}

Dinosaur::State Dinosaur::GetState() {
    return _state;
}

void Dinosaur::SetSpeed(int speed) {
    if(speed >= 1) {
        if(speed > 30)
            _sprite.SetColor(sf::Color(255, 150, 150));
        _moveSpeed = speed;
    }
}

void Dinosaur::SetChangeMotionTime(float changeMotionTime) {
    if(changeMotionTime >= 0.1 && changeMotionTime <= 3.0) {
        _changeMotionTime = changeMotionTime;
    }
}

int Dinosaur::GetHP() {
    return _hp;
}

void Dinosaur::Damage(int damage) {
    _hp -= damage;

    if(_state != Attacking1 && _state != Attacking2) {
        _state = Attacked;
    }

    progressbar->SetValue((int)(((float)_hp / (float)_hpMax) * 100.0));

    if(progressbar->GetValue() < 30) {
        progressbar->SetColor(sf::Color::Red);
    } else if(progressbar->GetValue() < 50) {
        progressbar->SetColor(sf::Color::Yellow);
    }
}

void Dinosaur::Flip() {
    _flip = true;
    _sprite.FlipX(_flip);
    _sprite.SetColor(sf::Color::Red);
}

bool Dinosaur::IsFliped() {
    return _flip;
}
