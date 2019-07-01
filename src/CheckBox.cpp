#include "CheckBox.hpp"
#include "SFMLMouseState.hpp"
#include "Game.hpp"
#include "ServiceLocator.hpp"

CheckBox::CheckBox(const sf::Image& image, int height, float x, float y, bool checked)
    : _image(image)
    , _clickDown(false)
    , _mouseEnter(false)
    , _checked(checked) {

    _sprite.SetImage(_image);

    // Get All Rect Position
    std::string map_name[] = {"Normal_Unchecked"
                              , "MouseOver_Unchecked"
                              , "MouseDown_Unchecked"
                              , "Normal_Checked"
                              , "MouseOver_Check"
                              , "MouseDown_Check"
                             };
    int top = 0;
    for(int i = 0; i < 6; i++) {
        _mapRect[map_name[i]] = sf::IntRect(0, top, _sprite.GetImage()->GetWidth(), height + top);
        top += height;
    }

    if(CheckBox::IsChecked() == true) {
        _sprite.SetSubRect(_mapRect["Normal_Checked"]);
    } else {
        _sprite.SetSubRect(_mapRect["Normal_Unchecked"]);
    }
    _sprite.SetPosition(x, y);
}

CheckBox::~CheckBox() {}

void CheckBox::Update(float elapsedTime) {
    if(SFMLMouseState::IsMouseOver(_sprite, Game::GetInput(), false)) {
        // Mouse Over
        if(_mouseEnter == false) {
            ServiceLocator::GetAudio()->PlaySound("audio/button-16.wav");
            _mouseEnter = true;
        }

        if(SFMLMouseState::IsMouseButtonDown(_sprite, Game::GetInput(), false)) {
            // Mouse Down
            if(CheckBox::IsChecked() == true) {
                _sprite.SetSubRect(_mapRect["MouseDown_Check"]);
            } else {
                _sprite.SetSubRect(_mapRect["MouseDown_Unchecked"]);
            }
            if(_clickDown == false)
                _clickDown = true;
            return;
        } else {
            // Mouse Released
            if(CheckBox::IsChecked() == true) {
                _sprite.SetSubRect(_mapRect["MouseOver_Check"]);
            } else {
                _sprite.SetSubRect(_mapRect["MouseOver_Unchecked"]);
            }

            if(_clickDown == true) {
                _clickDown = false;
                if(CheckBox::IsChecked() == true) {
                    Uncheck();
                    _sprite.SetSubRect(_mapRect["Normal_Unchecked"]);
                } else {
                    Check();
                    _sprite.SetSubRect(_mapRect["Normal_Checked"]);
                }
                return;
            }
        }
        return;
    } else {
        // Mouse Leave
        if(CheckBox::IsChecked() == true) {
            _sprite.SetSubRect(_mapRect["Normal_Checked"]);
        } else {
            _sprite.SetSubRect(_mapRect["Normal_Unchecked"]);
        }
        _clickDown = false;
        _mouseEnter = false;
        return;
    }
}

void CheckBox::Draw(sf::RenderWindow& rw) {
    rw.Draw(_sprite);
}

void CheckBox::SetPosition(float x, float y) {
    _sprite.SetPosition(x, y);
}

sf::Vector2f CheckBox::GetPosition() const {
    return _sprite.GetPosition();
}

float CheckBox::GetWidth() const {
    return _sprite.GetSize().x;
}

float CheckBox::GetHeight() const {
    return _sprite.GetSize().y;
}

sf::Rect<float> CheckBox::GetBoundingRect() const {
    sf::Vector2f size = _sprite.GetSize();
    sf::Vector2f position = _sprite.GetPosition();
    sf::Vector2f center = _sprite.GetCenter();

    float left = position.x - center.x;
    float top = position.y - center.y;
    float right = left + size.x;
    float bottom = top + size.y;

    return sf::Rect<float>(left, top, right, bottom);
}

void CheckBox::Check() {
    _checked = true;
}

void CheckBox::Uncheck() {
    _checked = false;
}

bool CheckBox::IsChecked() {
    return _checked;
}


