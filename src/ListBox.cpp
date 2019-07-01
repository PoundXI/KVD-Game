#include "ListBox.hpp"
#include "Button.hpp"
#include "Debug.hpp"
#include "Conversion.hpp"
#include "Game.hpp"
#include "SFMLMouseState.hpp"
#include <cmath>

ListBox::ListBox(const sf::Image& image
                 , const sf::Image& imageFirst, const sf::Image& imagePrev
                 , const sf::Image& imageNext, const sf::Image& imageLast
                 , const sf::Image& imageDelete
                 , float x, float y)
    : _image(image)
    , _pageCurrent(1)
    , _pageCount(1)
    , _pageIndexBegin(0)
    , _pageIndexEnd(0)
    , _selectedIndex(-1)
    , _deletedIndex(-1) {

    _sprite.SetImage(_image);
    _sprite.SetPosition(x, y);

    _btnFirstPage = new Button(imageFirst, 50, x + 300, y);
    _btnPrevPage  = new Button(imagePrev, 50, x + 300, y + 50);
    _btnNextPage  = new Button(imageNext, 50, x + 300, y + 300 - 100);
    _btnLastPage  = new Button(imageLast, 50, x + 300, y + 300 - 50);

    //initialize
    for(int i = 0; i < 6; i++) {
        _btnDelete[i] = new Button(imageDelete, 50, GetPosition().x + 250, GetPosition().y + i * 50);
        _sftext[i].SetFont(sf::Font::GetDefaultFont());
        _sftext[i].SetSize(40);
    }
}

ListBox::~ListBox() {
    delete _btnFirstPage;
    delete _btnPrevPage;
    delete _btnNextPage;
    delete _btnLastPage;

    for(int i = 0; i < 6; i++) {
        delete _btnDelete[i];
    }
}

void ListBox::Draw(sf::RenderWindow& rw) {
    rw.Draw(_sprite);
    _btnFirstPage->Draw(rw);
    _btnPrevPage->Draw(rw);
    _btnNextPage->Draw(rw);
    _btnLastPage->Draw(rw);

    //Update Display Item
    for(int i = 0; i < 6; i++) {
        rw.Draw(_sftext[i]);
        rw.Draw(_shape[i]);

        if((i % ITEMCOUNT_PER_PAGE >= _pageIndexBegin % ITEMCOUNT_PER_PAGE)
                && (i % ITEMCOUNT_PER_PAGE <= _pageIndexEnd % ITEMCOUNT_PER_PAGE)) {
            _btnDelete[i]->Draw(rw);
        }
    }
}

void ListBox::Update(float elapsedTime) {
    DEBUG_PRINT("\r_pageCurrent = %d, _pageCount = %d, _items.size() = %d", _pageCurrent, _pageCount, _items.size());

    /** Begin Update PageCount **/
    _pageCount = ceil((float)_items.size() / ITEMCOUNT_PER_PAGE);
    /** End Update PageCount **/


    /** Begin Update Button **/
    _btnFirstPage->Update(elapsedTime);
    _btnPrevPage->Update(elapsedTime);
    _btnNextPage->Update(elapsedTime);
    _btnLastPage->Update(elapsedTime);

    for(int i = 0; i < 6; i++) {
        _btnDelete[i]->Update(elapsedTime);
    }
    /** End Update Button **/


    /** Begin Update CurrentPage **/
    if(_btnFirstPage->GetState() == Button::MouseReleased) {
        _pageCurrent = 1;
    } else if(_btnPrevPage->GetState() == Button::MouseReleased) {
        if(_pageCurrent > 1) {
            _pageCurrent--;
        }
    } else if(_btnNextPage->GetState() == Button::MouseReleased) {
        if(_pageCurrent < _pageCount) {
            _pageCurrent++;
        }
    } else if(_btnLastPage->GetState() == Button::MouseReleased) {
        if(_pageCount > 1) {
            _pageCurrent = _pageCount;
        }
    }

    if(_pageCurrent > _pageCount) {
        _pageCurrent = _pageCount;
    }

    //Bug _pageCurrent = 0
    if(_items.size() > 0 && _pageCurrent == 0) {
        _pageCurrent = 1;
    }
    /** End Update CurrentPage **/


    /** Begin Update DisplayItemIndex **/
    _pageIndexBegin = ((_pageCurrent - 1) * ITEMCOUNT_PER_PAGE + 1) - 1;
    _pageIndexEnd = (_pageCurrent * ITEMCOUNT_PER_PAGE) - 1;
    if(_pageIndexEnd > _items.size() - 1) {
        _pageIndexEnd = _items.size() - 1;
    }
    /** End Update Display ItemIndex **/


    /** Begin Update Display Item **/
    _selectedIndex = -1;
    int itemIndex = _pageIndexBegin;
    for(int i = 0; i < 6; i++) {
        _sftext[i].SetPosition(GetPosition().x + 15 , GetPosition().y + i * 50);

        //Display Item
        if(itemIndex >= 0 && itemIndex <= _pageIndexEnd) {
            _sftext[i].SetText(_items.at(itemIndex));
            itemIndex++;
        } else {
            _sftext[i].SetText("");
        }

        sf::FloatRect rect(GetPosition().x
                           , GetPosition().y + i * 50
                           , GetPosition().x + 250
                           , GetPosition().y + 50 + i * 50);

        if(SFMLMouseState::IsMouseOver(rect, Game::GetWindow().GetInput())) {
            _sftext[i].SetColor(sf::Color::Red);
            _shape[i] = sf::Shape::Rectangle(rect.Left
                                             , rect.Top
                                             , rect.Right
                                             , rect.Bottom
                                             , sf::Color(200, 200, 200, 150));
        } else {
            _sftext[i].SetColor(sf::Color::Black);
            _shape[i] = sf::Shape::Rectangle(rect.Left
                                             , rect.Top
                                             , rect.Right
                                             , rect.Bottom
                                             , sf::Color(0, 0, 0, 0));
        }

        if(SFMLMouseState::IsMouseButtonDown(rect, Game::GetWindow().GetInput())) {
            if((i % ITEMCOUNT_PER_PAGE >= _pageIndexBegin % ITEMCOUNT_PER_PAGE)
                    && (i % ITEMCOUNT_PER_PAGE <= _pageIndexEnd % ITEMCOUNT_PER_PAGE)) {
                //_selectedIndex = i % ITEMCOUNT_PER_PAGE;
                _selectedIndex = (_pageCurrent - 1) * ITEMCOUNT_PER_PAGE + i;
            }

        }
    }
    /** End Update Display Item **/


    /** Begin Update Delete Item **/
    _deletedIndex = -1;
    for(int i = 0; i < 6; i++) {
        if(_btnDelete[i]->GetState() == Button::MouseReleased) {
            if((i % ITEMCOUNT_PER_PAGE >= _pageIndexBegin % ITEMCOUNT_PER_PAGE)
                    && (i % ITEMCOUNT_PER_PAGE <= _pageIndexEnd % ITEMCOUNT_PER_PAGE)) {
                _deletedIndex = (_pageCurrent - 1) * ITEMCOUNT_PER_PAGE + i;
                //Remove(_deletedIndex);
                break;
            }
        }
    }
    /** End Update Delete Item **/
}

void ListBox::SetPosition(float x, float y) {
    _sprite.SetPosition(x, y);
}

sf::Vector2f ListBox::GetPosition() const {
    return _sprite.GetPosition();
}

float ListBox::GetWidth() const {
    return _sprite.GetSize().x;
}

float ListBox::GetHeight() const {
    return _sprite.GetSize().y;
}

sf::Rect<float> ListBox::GetBoundingRect() const {
    sf::Vector2f size = _sprite.GetSize();
    sf::Vector2f position = _sprite.GetPosition();
    sf::Vector2f center = _sprite.GetCenter();

    float left = position.x - center.x;
    float top = position.y - center.y;
    float right = left + size.x;
    float bottom = top + size.y;

    return sf::Rect<float>(left, top, right, bottom);
}

void ListBox::Add(std::string item) {
    DEBUG_PRINT("\nListBox::Add");
    _items.push_back(item);
}

void ListBox::Remove(int index) {
    DEBUG_PRINT("\nListBox::Remove");
    _items.erase(_items.begin() + index);
}

int ListBox::GetItemCount() {
    return _items.size();
}

int ListBox::GetCurrentPage() {
    return _pageCurrent;
}

int ListBox::GetPageCount() {
    return _pageCount;
}

bool ListBox::IsExists(std::string item) {
    for(int i = 0; i < _items.size(); i++) {
        if(_items[i] == item) {
            return true;
        }
    }
    return false;
}

std::string ListBox::GetText(int index) {
    return _items[index];
}

int ListBox::GetSelectedIndex() {
    return _selectedIndex;
}

std::string ListBox::GetSelectedText() {
    return _items[_selectedIndex];
}

int ListBox::GetDeletedIndex() {
    return _deletedIndex;
}

std::string ListBox::GetDeletedText() {
    return _items[_deletedIndex];
}
