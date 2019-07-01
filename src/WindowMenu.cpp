//Debugging
#include "Debug.hpp"

//GameObject
#include "Game.hpp"
#include "WindowMenu.hpp"
#include "Button.hpp"
#include "ObjectManager.hpp"
#include "ServiceLocator.hpp"
#include "Wallpaper.hpp"
#include "TextBox.hpp"
#include "Label.hpp"

#include "ListBox.hpp"
#include "Conversion.hpp"

WindowMenu::MenuResult WindowMenu::Show(sf::RenderWindow& window) {
    DEBUG_PRINT("Showing Menu\n");

    //Create Object
    Wallpaper* wallpaper = new Wallpaper(Game::GetImage("Background_Menu"));
    int imageHeight = 60;
    int posX = 590;
    int posY = 330;
    int distanceY = 5;
    Button* btnStart = new Button(Game::GetImage("Button_Start"), imageHeight, posX, posY + (imageHeight + distanceY) * 0);
    Button* btnOption = new Button(Game::GetImage("Button_Option"), imageHeight, posX, posY + (imageHeight + distanceY) * 1);
    Button* btnAbout = new Button(Game::GetImage("Button_About"), imageHeight, posX, posY + (imageHeight + distanceY) * 2);
    Button* btnExit = new Button(Game::GetImage("Button_Exit"), imageHeight, posX, posY + (imageHeight + distanceY) * 3);

    Label* lblPlayerName = new Label("", 30, 30, 10);
    Button* btnChangePlayer = new Button(Game::GetImage("Button_ChangePlayer"), 42, 15, 45);

    ObjectManager gameObjects;
    gameObjects.Add("wallpaper", wallpaper);
    gameObjects.Add("btnStart", btnStart);
    gameObjects.Add("btnOption", btnOption);
    gameObjects.Add("btnAbout", btnAbout);
    gameObjects.Add("btnExit", btnExit);
    gameObjects.Add("lblPlayerName", lblPlayerName);
    gameObjects.Add("btnChangePlayer", btnChangePlayer);

    ServiceLocator::GetAudio()->SetSoundEnable(Game::IsSoundEnable());
    ServiceLocator::GetAudio()->SetMusicEnable(Game::IsMusicEnable());

    //Play Background music
    if(Game::IsSoundEnable()) {
        if(ServiceLocator::GetAudio()->IsMusicPlaying() == false)
            ServiceLocator::GetAudio()->PlayMusic("audio/music1.ogg", true);
    } else {
        ServiceLocator::GetAudio()->StopMusic();
    }

    // Draw & event loop
    while(true) {
        // Get event loop
        sf::Event event;
        while(window.GetEvent(event)) {
            // Window closed
            if(event.Type == sf::Event::Closed) {
                return WindowMenu::Exit;
            }

            // Escape key pressed
            if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape)) {
                return WindowMenu::Exit;
            }
        }

        //Get Event
        if(btnStart->GetState() == Button::MouseReleased) {
            return WindowMenu::Play;
        }

        if(btnOption->GetState() == Button::MouseReleased) {
            return WindowMenu::Option;
        }

        if(btnAbout->GetState() == Button::MouseReleased) {
            return WindowMenu::About;
        }

        if(btnExit->GetState() == Button::MouseReleased) {
            return WindowMenu::Exit;
        }

        if(btnChangePlayer->GetState() == Button::MouseReleased) {
            return WindowMenu::ChangePlayer;
        }

        //Update All
        lblPlayerName->SetText(Game::GetPlayerName());
        gameObjects.UpdateAll();

        // Clear Screen
        window.Clear();

        // Draw All
        gameObjects.DrawAll(window);

        //Update Screen
        window.Display();
    }
}
