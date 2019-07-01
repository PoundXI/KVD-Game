//Debugging
#include "Debug.hpp"

#include "WindowOption.hpp"
#include "Button.hpp"
#include "CheckBox.hpp"
#include "ObjectManager.hpp"
#include "ServiceLocator.hpp"
#include "Label.hpp"
#include "Wallpaper.hpp"
#include "PictureBox.hpp"
#include "Game.hpp"

void WindowOption::Show(sf::RenderWindow& window) {
    DEBUG_PRINT("Showing WindowOption\n");

    //Create Object
    Wallpaper* wallpaper = new Wallpaper(Game::GetImage("Background_All"));
    PictureBox* picture = new PictureBox(Game::GetImage("PictureBox_Option"), 180, 100);
    Label* lblSoundEnable = new Label("Sound Effects Enable", 32, 200, 160);
    Label* lblSongEnable = new Label("Music Enable", 32, 200, 240);
    Label* lblFullscreen = new Label("Fullscreen Enable", 32, 200, 320);
    CheckBox* chkSoundEnable = new CheckBox(Game::GetImage("CheckBox"), 60, 550, 140, Game::IsSoundEnable());
    CheckBox* chkMusicEnable = new CheckBox(Game::GetImage("CheckBox"), 60, 550, 220, Game::IsMusicEnable());
    CheckBox* chkFullscreen = new CheckBox(Game::GetImage("CheckBox"), 60, 550, 300, Game::IsFullscreen());
    Button* btnBackToMain = new Button(Game::GetImage("Button_Back"), 60, 200, 390);

    ObjectManager objects;
    objects.Add("wallpaper", wallpaper);
    objects.Add("picture", picture);
    objects.Add("lblSound", lblSoundEnable);
    objects.Add("lblSong", lblSongEnable);
    objects.Add("lblFullscreen", lblFullscreen);
    objects.Add("chkSound", chkSoundEnable);
    objects.Add("chkMusic", chkMusicEnable);
    objects.Add("chkFullscreen", chkFullscreen);
    objects.Add("btnBack", btnBackToMain);

    // Draw & event loop
    while(true) {
        //Sound
        Game::SetSoundEnable(chkSoundEnable->IsChecked());
        if(chkSoundEnable->IsChecked() == true) {
            ServiceLocator::GetAudio()->SetSoundEnable(true);
        } else {
            ServiceLocator::GetAudio()->StopSound();
            ServiceLocator::GetAudio()->SetSoundEnable(false);
        }

        //Music
        Game::SetMusicEnable(chkMusicEnable->IsChecked());
        if(chkMusicEnable->IsChecked() == true) {
            ServiceLocator::GetAudio()->SetMusicEnable(true);

            //Play Background music
            if(ServiceLocator::GetAudio()->IsMusicPlaying() == false)
                ServiceLocator::GetAudio()->PlayMusic("audio/music1.ogg", true);
        } else {
            ServiceLocator::GetAudio()->StopMusic();
            ServiceLocator::GetAudio()->SetMusicEnable(false);
        }

        //Fullscreen
        Game::SetFullscreen(chkFullscreen->IsChecked());

        //Back Button
        if(btnBackToMain->GetState() == Button::MouseReleased) {
            return;
        }

        // Get event loop
        sf::Event event;
        while(window.GetEvent(event)) {
            // Window closed
            if(event.Type == sf::Event::Closed) {
                return;
            }

            // Escape key pressed
            if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape)) {
                return;
            }
        }

        objects.UpdateAll();

        // Clear Screen
        window.Clear();

        // Draw Objecy
        objects.DrawAll(window);

        // Update the window
        window.Display();
    }
}

