#include "Button.hpp"
#include "SFMLMouseState.hpp"
#include "Game.hpp"
#include "ServiceLocator.hpp"

Button::Button(const sf::Image& image, int height, float x, float y, bool enable)
    : _image(image)
    , _state(Nothing)
    , _mouseClickedDown(false)
    , _mouseEntered(false)
    , _enable(enable) {

    _sprite.SetImage(_image);

    // Get All Rect Position
    std::string map_name[] = {"Normal", "MouseOver", "MouseDown", "Locked"};

    int top = 0;
    for(int i = 0; i < 4; i++) {
        _mapRect[map_name[i]] = sf::IntRect(0, top, _sprite.GetImage()->GetWidth(), height + top);
        top += height;
    }

    _sprite.SetSubRect(_mapRect["Normal"]);
    _sprite.SetPosition(x, y);
}

Button::~Button() {
}

Button::State Button::GetState() {
    return _state;
}

void Button::Draw(sf::RenderWindow& rw) {
    rw.Draw(_sprite);
}

void Button::Update(float elapsedTime) {
    // Mouse Enable Check
    if(_enable == false) {
        _sprite.SetSubRect(_mapRect["Locked"]);
        _mouseClickedDown = false;
        _mouseEntered = false;
        _state =  Button::MouseLeave;

        // Exit
        return;
    }

    // Mouse Over Check
    if(SFMLMouseState::IsMouseOver(_sprite, Game::GetInput(), false)) {
        // Mouse Entered (Change state from "not over" to "over")
        if(_mouseEntered == false) {
            // Play Mouse Over Sound
            ServiceLocator::GetAudio()->PlaySound("audio/button-over.ogg");

            // Set state mouse is over
            _mouseEntered = true;
        }

        // Mouse Button Down Check
        if(SFMLMouseState::IsMouseButtonDown(_sprite, Game::GetInput(), false)) {
            _sprite.SetSubRect(_mapRect["MouseDown"]);

            //
            if(_mouseClickedDown == false)
                _mouseClickedDown = true;

            _state = Button::MouseDown;

            // Exit
            return;
        } else {
            // Mouse Released
            _sprite.SetSubRect(_mapRect["MouseOver"]);

            if(_mouseClickedDown == true) {
                _mouseClickedDown = false;
                _state =  Button::MouseReleased;

                // Exit
                return;
            }
        }
        _state =  Button::MouseOver;

        // Exit
        return;
    } else {
        // Mouse Leave
        _sprite.SetSubRect(_mapRect["Normal"]);
        _mouseClickedDown = false;
        _mouseEntered = false;
        _state =  Button::MouseLeave;

        // Exit
        return;
    }
}

void Button::SetPosition(float x, float y) {
    _sprite.SetPosition(x, y);
}

sf::Vector2f Button::GetPosition() const {
    return _sprite.GetPosition();
}

float Button::GetWidth() const {
    return _sprite.GetSize().x;
}

float Button::GetHeight() const {
    return _sprite.GetSize().y;
}

sf::Rect<float> Button::GetBoundingRect() const {
    sf::Vector2f size = _sprite.GetSize();
    sf::Vector2f position = _sprite.GetPosition();
    sf::Vector2f center = _sprite.GetCenter();

    float left = position.x - center.x;
    float top = position.y - center.y;
    float right = left + size.x;
    float bottom = top + size.y;

    return sf::Rect<float>(left, top, right, bottom);
}

void Button::SetEnable(bool enable) {
    _enable = enable;
}

bool Button::IsEnable() {
    return _enable;
}
