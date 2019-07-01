#include "WindowAbout.hpp"

//Debugging
#include "Debug.hpp"

#include "Game.hpp"
#include "Label.hpp"
#include "ObjectManager.hpp"
#include "Wallpaper.hpp"
#include <sstream>

WindowAbout::WindowAbout() {
}

WindowAbout::~WindowAbout() {
}

void WindowAbout::Show(sf::RenderWindow& window) {
    DEBUG_PRINT("Showing WindowAbout\n");

    Wallpaper* wallpaper = new Wallpaper(Game::GetImage("Background_About"));

    ObjectManager objects;
    objects.Add("wallpaper", wallpaper);

    while(true) {
        sf::Event event;
        while(window.GetEvent(event)) {
            if(event.Type == sf::Event::Closed)
                return;

            if(event.Type == sf::Event::KeyPressed)
                return;
        }

        objects.UpdateAll();
        window.Clear();
        objects.DrawAll(window);
        window.Display();
    }
    return;
}
