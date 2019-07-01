#ifndef SFMLMOUSESTATUS_HPP_INCLUDED
#define SFMLMOUSESTATUS_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class SFMLMouseState {
public:
    static bool IsMouseOver(const sf::Sprite& sprite, const sf::Input& input, bool alpha = true);
    static bool IsMouseButtonDown(const sf::Sprite& sprite, const sf::Input& input, bool alpha = true);

    static bool IsMouseOver(const sf::FloatRect& rect, const sf::Input& input);
    static bool IsMouseButtonDown(const sf::FloatRect& rect, const sf::Input& input);
};

#endif // SFMLMOUSESTATUS_HPP_INCLUDED
