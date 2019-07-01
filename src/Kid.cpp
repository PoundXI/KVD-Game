#include "Kid.hpp"
#include "Game.hpp"
#include "WindowPlay.hpp"
#include "Debug.hpp"

Kid::Kid(const sf::Image& image, int height, int speed, float changeMotionTime)
    : _image(image)
    , _state(StandForLeft)
    , _changeMotionTime(changeMotionTime)
    , _changeMotionTimeCounter(0)
    , _moveSpeed(speed) {

    _sprite.SetImage(_image);

    // Get All Rect Position
    std::string map_name[] = {"Stand", "LeftWalk", "RightWalk", "Attack1", "Attack2", "Attack3"};
    int top = 0;
    for(int i = 0; i < 6; i++) {
        _mapRect[map_name[i]] = sf::IntRect(0, top, _sprite.GetImage()->GetWidth(), height + top);
        top += height;
    }

    _sprite.SetSubRect(_mapRect["Stand"]);
    _sprite.SetPosition(750, 300);
    _sprite.SetCenter(_sprite.GetSize().x / 2, _sprite.GetSize().y / 2);
}

Kid::~Kid() {}

void Kid::ShootBall() {
    if(_state != Attack1 && _state != Attack2 && _state != Attack3) {
        _state = Attack1;
        WindowPlay::AddItemDuck(GetPosition().x - 50 , GetPosition().y);
    }
}

void Kid::Update(float elapsedTime) {
    //setting up move param
    int action = 0; //0=no action, 1=move up, 2=move down
    float delta = _moveSpeed * elapsedTime;
    float destY = GetPosition().y;

    /*
    //move up event
    if(Game::GetInput().IsKeyDown(sf::Key::Up)) {
        action = 1;
        destY = GetPosition().y - delta;
    }

    //move down event
    if(Game::GetInput().IsKeyDown(sf::Key::Down)) {
        action = 2;
        destY = GetPosition().y + delta;
    }
    */

    if((int)GetPosition().y != Game::GetInput().GetMouseY()) {
        if(Game::GetInput().GetMouseY() < (int)GetPosition().y) {
            action = 1;
            destY = (int)(GetPosition().y - delta);
            if(destY < Game::GetInput().GetMouseY())
                destY = Game::GetInput().GetMouseY();
        }

        if(Game::GetInput().GetMouseY() > (int)GetPosition().y) {
            action = 2;
            destY = (int)(GetPosition().y + delta);
            if(destY > Game::GetInput().GetMouseY())
                destY = Game::GetInput().GetMouseY();
        }
    }

    //action
    if(action == 0) {
        //in attack state ???
        if(_state != Attack1 && _state != Attack2 && _state != Attack3) {
            //if(_state != Attack3) //???
            _state = Stand;
        }
    } else if(action == 1) {
        MoveUp(destY);
    } else if(action == 2) {
        MoveDown(destY);
    }

    //Animate Sprite
    _changeMotionTimeCounter += elapsedTime;
    if(_changeMotionTimeCounter < _changeMotionTime) {
        return;
    } else {
        _changeMotionTimeCounter = 0;
    }

    switch(_state) {
        case Stand:
            _sprite.SetSubRect(_mapRect["Stand"]);
            _state = StandForLeft;
            break;
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
        case Attack1:
            _sprite.SetSubRect(_mapRect["Attack1"]);
            _state = Attack2;
            break;
        case Attack2:
            _sprite.SetSubRect(_mapRect["Attack2"]);
            _state = Attack3;
            break;
        case Attack3:
            _sprite.SetSubRect(_mapRect["Attack3"]);
            _state = StandForLeft;
            break;
    }
}

void Kid::Draw(sf::RenderWindow& rw) {
    rw.Draw(_sprite);
}

void Kid::SetPosition(float x, float y) {
    _sprite.SetPosition(x, y);
}

sf::Vector2f Kid::GetPosition() const {
    return _sprite.GetPosition();
}

float Kid::GetWidth() const {
    return _sprite.GetSize().x;
}

float Kid::GetHeight() const {
    return _sprite.GetSize().y;
}

sf::Rect<float> Kid::GetBoundingRect() const {
    sf::Vector2f size = _sprite.GetSize();
    sf::Vector2f position = _sprite.GetPosition();
    sf::Vector2f center = _sprite.GetCenter();

    float left = position.x - center.x;
    float top = position.y - center.y;
    float right = left + size.x;
    float bottom = top + size.y;

    return sf::Rect<float>(left, top, right, bottom);
}

Kid::State Kid::GetState() {
    return _state;
}

void Kid::MoveUp(float destination) {
    //Move up
    if(destination >= 150) {
        SetPosition(GetPosition().x, destination);
    } else {
        SetPosition(GetPosition().x, 150);
    }
}

void Kid::MoveDown(float destination) {
    //Move down
    if(destination <= Game::SCREEN_HEIGHT - GetHeight() + 50) {
        SetPosition(GetPosition().x, destination);
    } else {
        SetPosition(GetPosition().x, 550);
    }
}
