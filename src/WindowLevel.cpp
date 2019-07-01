//Debugging
#include "Debug.hpp"

#include "WindowLevel.hpp"
#include "Button.hpp"
#include "Wallpaper.hpp"
#include "ObjectManager.hpp"
#include "ServiceLocator.hpp"
#include "Game.hpp"

int WindowLevel::Show(sf::RenderWindow& window) {
    DEBUG_PRINT("Showing WindowLevel\n");

    //Create Object
    int spaceX = 50;
    int beginX = 70;
    Wallpaper* wallpaper = new Wallpaper(Game::GetImage("Background_All"));
    Button* btnLevel01 = new Button(Game::GetImage("Button_Level01"), 100, beginX * 1 + spaceX * 0, 60);
    Button* btnLevel02 = new Button(Game::GetImage("Button_Level02"), 100, beginX * 2 + spaceX * 1, 60);
    Button* btnLevel03 = new Button(Game::GetImage("Button_Level03"), 100, beginX * 3 + spaceX * 2, 60);
    Button* btnLevel04 = new Button(Game::GetImage("Button_Level04"), 100, beginX * 4 + spaceX * 3, 60);

    Button* btnLevel05 = new Button(Game::GetImage("Button_Level05"), 100, beginX * 1 + spaceX * 0, 180);
    Button* btnLevel06 = new Button(Game::GetImage("Button_Level06"), 100, beginX * 2 + spaceX * 1, 180);
    Button* btnLevel07 = new Button(Game::GetImage("Button_Level07"), 100, beginX * 3 + spaceX * 2, 180);
    Button* btnLevel08 = new Button(Game::GetImage("Button_Level08"), 100, beginX * 4 + spaceX * 3, 180);

    Button* btnLevel09 = new Button(Game::GetImage("Button_Level09"), 100, beginX * 1 + spaceX * 0, 300);
    Button* btnLevel10 = new Button(Game::GetImage("Button_Level10"), 100, beginX * 2 + spaceX * 1, 300);
    Button* btnLevel11 = new Button(Game::GetImage("Button_Level11"), 100, beginX * 3 + spaceX * 2, 300);
    Button* btnLevel12 = new Button(Game::GetImage("Button_Level12"), 100, beginX * 4 + spaceX * 3, 300);

    Button* btnBack   = new Button(Game::GetImage("Button_Back"),  60, beginX, 420);

    // Create List of Map Button
    ObjectManager gameObjects;
    gameObjects.Add("wallpaper", wallpaper);
    gameObjects.Add("btnBack", btnBack);
    gameObjects.Add("btnLevel01", btnLevel01);
    gameObjects.Add("btnLevel02", btnLevel02);
    gameObjects.Add("btnLevel03", btnLevel03);
    gameObjects.Add("btnLevel04", btnLevel04);
    gameObjects.Add("btnLevel05", btnLevel05);
    gameObjects.Add("btnLevel06", btnLevel06);
    gameObjects.Add("btnLevel07", btnLevel07);
    gameObjects.Add("btnLevel08", btnLevel08);
    gameObjects.Add("btnLevel09", btnLevel09);
    gameObjects.Add("btnLevel10", btnLevel10);
    gameObjects.Add("btnLevel11", btnLevel11);
    gameObjects.Add("btnLevel12", btnLevel12);

    //Play Background music
    if(ServiceLocator::GetAudio()->IsMusicPlaying() == false)
        ServiceLocator::GetAudio()->PlayMusic("audio/music1.ogg", true);

    //Lock unpassed level
    int objectIndex = 0;
    int levelPtr = 0;
    int levelCurrent = Game::GetCurrentLevel();  //
    while(objectIndex < gameObjects.GetObjectCount()) {
        //Find ButtonLevel from All Button
        if(gameObjects.GetName(objectIndex).substr(0, 8) == "btnLevel") {
            // Count current level Button found
            levelPtr++;

            if(levelPtr > levelCurrent) {
                //Set Map Button Disable
                dynamic_cast<Button*>(gameObjects.GetObject(objectIndex))->SetEnable(false);
            }
        }
        //Increment Loop
        objectIndex++;
    }

    // Draw & event loop
    while(true) {
        // Get Event
        if(btnBack->GetState() == Button::MouseReleased) {
            return 0;
        }

        if(btnLevel01->GetState() == Button::MouseReleased) {
            return 1;
        }

        if(btnLevel02->GetState() == Button::MouseReleased) {
            return 2;
        }

        if(btnLevel03->GetState() == Button::MouseReleased) {
            return 3;
        }

        if(btnLevel04->GetState() == Button::MouseReleased) {
            return 4;
        }

        if(btnLevel05->GetState() == Button::MouseReleased) {
            return 5;
        }

        if(btnLevel06->GetState() == Button::MouseReleased) {
            return 6;
        }

        if(btnLevel07->GetState() == Button::MouseReleased) {
            return 7;
        }

        if(btnLevel08->GetState() == Button::MouseReleased) {
            return 8;
        }

        if(btnLevel09->GetState() == Button::MouseReleased) {
            return 9;
        }

        if(btnLevel10->GetState() == Button::MouseReleased) {
            return 10;
        }

        if(btnLevel11->GetState() == Button::MouseReleased) {
            return 11;
        }

        if(btnLevel12->GetState() == Button::MouseReleased) {
            return 12;
        }

        // Get event loop
        sf::Event event;
        while(window.GetEvent(event)) {
            // Window closed
            if(event.Type == sf::Event::Closed) {
                return 0;
            }

            // Escape key pressed
            if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape)) {
                return 0;
            }
        }

        //Update All
        gameObjects.UpdateAll();

        // Clear Screen
        window.Clear();

        // Draw All
        gameObjects.DrawAll(window);

        //Update Screen
        window.Display();
    }
}

