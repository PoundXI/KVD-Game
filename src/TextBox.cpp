#include "TextBox.hpp"
#include "Debug.hpp"

#include <sstream>

TextBox::TextBox(float x, float y, float width, float height
                 , std::string text
                 , sf::Color textColor
                 , sf::Color boxColor)
    : _x(x)
    , _y(y)
    , _width(width)
    , _height(height)
    , _text(text)
    , _textColor(textColor)
    , _boxColor(boxColor)
    , _changeMotionTime(0.5)
    , _changeMotionTimeCounter(0)
    , _cursorBlink(true) {

    //set text
    _font = sf::Font::GetDefaultFont();
    _sftext.SetFont(_font);
    _sftext.SetSize(_height * 0.7);
    _sftext.SetPosition(_x + _height * 0.3 , _y - _height * 0.4);
    _sftext.SetColor(_textColor);
    SetText(_text);

    _boxShape = sf::Shape::Line(_x, _y, _x + _width , _y, _height,  _boxColor);
}

TextBox::~TextBox() {
}

void TextBox::SetPosition(float x, float y) {
    _x = x;
    _y = y;
    _boxShape = sf::Shape::Line(_x, _y, _x + _width , _y, _height,  _boxColor);
}

sf::Vector2f TextBox::GetPosition() const {
    return sf::Vector2f(_x, _y);
}

float TextBox::GetWidth() const {
    return _width;
}

float TextBox::GetHeight() const {
    return _height;
}

sf::Rect<float> TextBox::GetBoundingRect() const {
    return sf::Rect<float>(_x, _y, _x + _width, _y + _height);
}

char TextBox::GetKeyPressed(sf::Event event) {
    if(event.Type == sf::Event::KeyPressed) {
        if(event.Key.Code == sf::Key::A) {
            return 'A';
        } else if(event.Key.Code == sf::Key::B) {
            return 'B';
        } else if(event.Key.Code == sf::Key::C) {
            return 'C';
        } else if(event.Key.Code == sf::Key::D) {
            return 'D';
        } else if(event.Key.Code == sf::Key::E) {
            return 'E';
        } else if(event.Key.Code == sf::Key::F) {
            return 'F';
        } else if(event.Key.Code == sf::Key::G) {
            return 'G';
        } else if(event.Key.Code == sf::Key::H) {
            return 'H';
        } else if(event.Key.Code == sf::Key::I) {
            return 'I';
        } else if(event.Key.Code == sf::Key::J) {
            return 'J';
        } else if(event.Key.Code == sf::Key::K) {
            return 'K';
        } else if(event.Key.Code == sf::Key::L) {
            return 'L';
        } else if(event.Key.Code == sf::Key::M) {
            return 'M';
        } else if(event.Key.Code == sf::Key::N) {
            return 'N';
        } else if(event.Key.Code == sf::Key::O) {
            return 'O';
        } else if(event.Key.Code == sf::Key::P) {
            return 'P';
        } else if(event.Key.Code == sf::Key::Q) {
            return 'Q';
        } else if(event.Key.Code == sf::Key::R) {
            return 'R';
        } else if(event.Key.Code == sf::Key::S) {
            return 'S';
        } else if(event.Key.Code == sf::Key::T) {
            return 'T';
        } else if(event.Key.Code == sf::Key::U) {
            return 'U';
        } else if(event.Key.Code == sf::Key::V) {
            return 'V';
        } else if(event.Key.Code == sf::Key::W) {
            return 'W';
        } else if(event.Key.Code == sf::Key::X) {
            return 'X';
        } else if(event.Key.Code == sf::Key::Y) {
            return 'Y';
        } else if(event.Key.Code == sf::Key::Z) {
            return 'Z';
        } else if(event.Key.Code == sf::Key::Back) {
            return char(0x8); //backspace
        }
    }
    return NULL;
}

void TextBox::Update(float elapsedTime) {
    _sftext.SetText(_text);

    //Update Cursor
    float CursorPosX = 0;
    if(_text.length() == 0) {
        CursorPosX = _sftext.GetPosition().x + _sftext.GetCharacterPos(_text.size() - 1).x;
    } else {
        CursorPosX = _sftext.GetPosition().x + _sftext.GetCharacterPos(_text.size() - 1).x + _sftext.GetSize();
    }
    _cursorShape = sf::Shape::Line(CursorPosX, _y - _height * 0.25, CursorPosX, _y + _height * 0.3, _sftext.GetSize() * 0.1,  sf::Color::Red);

    //Update Time for Blink Cursor
    _changeMotionTimeCounter += elapsedTime;
    if(_changeMotionTimeCounter < _changeMotionTime) {
        _cursorBlink = true;
        return;
    } else if(_changeMotionTimeCounter < _changeMotionTime * 2) {
        _cursorBlink = false;
        return;
    } else {
        _changeMotionTimeCounter = 0;
    }
}

void TextBox::Draw(sf::RenderWindow& rw) {
    rw.Draw(_boxShape);
    rw.Draw(_sftext);

    //Blink Cursor
    if(_cursorBlink == true) {
        rw.Draw(_cursorShape);
    }
}

void TextBox::SetText(std::string text) {
    if(_text.size() >= MAX_SIZE) {
        _text = _text.substr(0, _text.size() - MAX_SIZE);
    } else {
        _text = text;
    }
}

std::string TextBox::GetText() {
    return _text;
}

void TextBox::Append(std::string text) {
    if(_text.size() <= MAX_SIZE - text.size()) {
        _text.append(text);
    } else {
        _text.append(text.substr(0, MAX_SIZE - _text.size()));
    }
}

void TextBox::Append(char c) {
    if(_text.size() < MAX_SIZE) {
        std::stringstream ss;
        ss << c;
        _text.append(ss.str());
    }
}

void TextBox::Remove() {
    if(_text.size() > 0) {
        _text.erase(_text.size() - 1);
    }
}

