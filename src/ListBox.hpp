#ifndef LISTBOX_HPP_INCLUDED
#define LISTBOX_HPP_INCLUDED

#include "IVisibleObject.hpp"
#include "Button.hpp"

#include <string>
#include <vector>

class ListBox : public IVisibleObject {
public:
    ListBox(const sf::Image& image
            , const sf::Image& imageFirst, const sf::Image& imagePrev
            , const sf::Image& imageNext, const sf::Image& imageLast
            , const sf::Image& imageDelete
            , float x, float y);

    ~ListBox();

    virtual void Update(float elapsedTime);
    virtual void Draw(sf::RenderWindow& rw);

    virtual void SetPosition(float x, float y);
    virtual sf::Vector2f GetPosition() const;
    virtual float GetWidth() const;
    virtual float GetHeight() const;

    virtual sf::Rect<float> GetBoundingRect() const;

    void Add(std::string item);
    void Remove(int index);

    int GetSelectedIndex();
    std::string GetSelectedText();

    int GetDeletedIndex();
    std::string GetDeletedText();

    int GetItemCount();
    int GetCurrentPage();
    int GetPageCount();

    bool IsExists(std::string item);
    std::string GetText(int index);

private:
    static const int ITEMCOUNT_PER_PAGE = 6;
    std::vector<std::string> _items;
    int _pageCurrent;
    int _pageCount;
    int _pageIndexBegin;
    int _pageIndexEnd;
    int _selectedIndex;
    int _deletedIndex;

    sf::Sprite  _sprite;
    const sf::Image& _image;

    //Move Button
    Button* _btnFirstPage;
    Button* _btnPrevPage;
    Button* _btnNextPage;
    Button* _btnLastPage;

    //Delete Button
    Button* _btnDelete[6];

    //String
    sf::String  _sftext[6];
    sf::Shape   _shape[6];
};

#endif // LISTBOX_HPP_INCLUDED
