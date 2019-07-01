#ifndef WindowSplash_HPP_INCLUDED
#define WindowSplash_HPP_INCLUDED

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class WindowSplash {
private:
    float _changeMotionTime;
    float _changeMotionTimeCounter;
public:
    WindowSplash();
    ~WindowSplash();
    void Show(sf::RenderWindow& window);
};

#endif // WindowSplash_HPP_INCLUDED
