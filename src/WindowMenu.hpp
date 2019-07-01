#ifndef MAINMENU_HPP_INCLUDED
#define MAINMENU_HPP_INCLUDED

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class WindowMenu {
public:
    enum MenuResult { Play, Option, About, Exit, ChangePlayer};
    MenuResult Show(sf::RenderWindow& window);
};

#endif // MAINMENU_HPP_INCLUDED
