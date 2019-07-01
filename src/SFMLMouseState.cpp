#include "SFMLMouseState.hpp"
#include <SFML/Graphics.hpp>

bool SFMLMouseState::IsMouseOver(const sf::Sprite& sprite, const sf::Input& input, bool alpha) {
    sf::Vector2f mousePos(input.GetMouseX(), input.GetMouseY());
    sf::Vector2f spritePos(sprite.GetPosition().x, sprite.GetPosition().y);

    // Mouse over check
    if(
        (mousePos.x > spritePos.x)
        && (mousePos.x < spritePos.x + sprite.GetSubRect().GetWidth())
        && (mousePos.y > spritePos.y)
        && (mousePos.y < spritePos.y + sprite.GetSubRect().GetHeight())
    ) {
        // If User Need to Check Alpha
        if(alpha == true) {
            // Alpha channel check
            if(sprite.GetPixel(mousePos.x - spritePos.x, mousePos.y - spritePos.y).a == 255)
                return true;//over and transparent
        } else {
            return true;//over
        }
    }
    return false;//not over or not transparent
}

bool SFMLMouseState::IsMouseButtonDown(const sf::Sprite& sprite, const sf::Input& input, bool alpha) {
    if(input.IsMouseButtonDown(sf::Mouse::Left) && IsMouseOver(sprite, input, alpha))
        return true;
    return false;
}

bool SFMLMouseState::IsMouseOver(const sf::FloatRect& rect, const sf::Input& input) {
    sf::Vector2f mousePos(input.GetMouseX(), input.GetMouseY());

    // Mouse over check
    if((mousePos.x > rect.Left)
            && (mousePos.x < rect.Right)
            && (mousePos.y > rect.Top)
            && (mousePos.y < rect.Bottom)) {
        return true;//over
    }
    return false;//not over
}

bool SFMLMouseState::IsMouseButtonDown(const sf::FloatRect& rect, const sf::Input& input) {
    if(input.IsMouseButtonDown(sf::Mouse::Left) && IsMouseOver(rect, input))
        return true;
    return false;
}

