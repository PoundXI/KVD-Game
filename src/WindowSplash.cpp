//Debugging
#include "Debug.hpp"

#include "WindowSplash.hpp"
#include "Game.hpp"
#include "Label.hpp"
#include "Progressbar.hpp"
#include "ObjectManager.hpp"
#include "Conversion.hpp"

WindowSplash::WindowSplash()
    : _changeMotionTime(0.001)
    , _changeMotionTimeCounter(0) {
}

WindowSplash::~WindowSplash() {
}

void WindowSplash::Show(sf::RenderWindow& window) {
    DEBUG_PRINT("Showing Splash\n");

    //Create Object
    Progressbar* progressbar = new Progressbar(200, 550, 400, 20, 30, sf::Color(0x39, 0x7e, 0xff));
    Label* label = new Label("Loading 0%", 24, 320, 500);

    // Add Object to ObjectManager
    ObjectManager objects;
    objects.Add("progressbar", progressbar);
    objects.Add("label", label);

    //Draw, Update
    while(progressbar->GetValue() < 100) {
        //Update elapsedTime
        _changeMotionTimeCounter += Game::GetWindow().GetFrameTime();

        //Update changeMotionTimeCounter
        if(_changeMotionTimeCounter >= _changeMotionTime) {
            progressbar->IncreaseValue(3);
            _changeMotionTimeCounter = 0;
        }

        //Update Label
        label->SetText("Loading " + Conversion::IntToString(progressbar->GetValue()) + "%");

        //Update All
        objects.UpdateAll();

        //Clear Screen
        window.Clear();

        //Draw All
        objects.DrawAll(window);

        //Update Screen
        window.Display();
    }
    return;
}
