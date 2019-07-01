#ifndef WindowAbout_HPP_INCLUDED
#define WindowAbout_HPP_INCLUDED

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class WindowAbout {
public:
    WindowAbout();
    ~WindowAbout();
    void Show(sf::RenderWindow& window);
};

#endif // WindowAbout_HPP_INCLUDED
