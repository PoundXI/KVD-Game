#ifndef WindowPlayer_HPP_INCLUDED
#define WindowPlayer_HPP_INCLUDED

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class WindowPlayer {
public:
    WindowPlayer();
    ~WindowPlayer();
    int Show(sf::RenderWindow& window);
private:
    int _workWithId;
    enum State { Viewing, Creating };
    State _state;
};

#endif // WindowPlayer_HPP_INCLUDED

