#include "WindowPlay.hpp"

#include "Game.hpp"
#include "ServiceLocator.hpp"

#include "ObjectManager.hpp"

#include "Button.hpp"
#include "CheckBox.hpp"
#include "PictureBox.hpp"
#include "Wallpaper.hpp"
#include "Label.hpp"
#include "Progressbar.hpp"

#include "Dinosaur.hpp"
#include "Smoke.hpp"
#include "Kid.hpp"

#include "ItemHorse.hpp"
#include "ItemCopter.hpp"
#include "ItemBomb.hpp"
#include "ItemDuck.hpp"
#include "ItemCar.hpp"
#include "ItemCake.hpp"

#include "Debug.hpp"

#include "Conversion.hpp"
#include "SFMLMouseState.hpp"

/** Begin Initialize **/
ObjectManager WindowPlay::_dinosaurs;
ObjectManager WindowPlay::_horses;
ObjectManager WindowPlay::_cakes;
ObjectManager WindowPlay::_smokes;
ObjectManager WindowPlay::_ducks;
ObjectManager WindowPlay::_cars;
ObjectManager WindowPlay::_copters;

int WindowPlay::_itemHorseCount = 0;
int WindowPlay::_itemCarCount = 0;
int WindowPlay::_itemCakeCount = 0;
int WindowPlay::_itemCopterCount = 0;

int WindowPlay::_selectedItem = 0;

const sf::FloatRect WindowPlay::_rectBattleArea(0, 100, Game::SCREEN_WIDTH - 100, Game::SCREEN_HEIGHT);
/** End Initialize **/

WindowPlay::WindowPlay()
    : _state(Playing)
    , _playTime(0) {
}

WindowPlay::~WindowPlay() {
    _dinosaurs.RemoveAll();
    _horses.RemoveAll();
    _cakes.RemoveAll();
    _smokes.RemoveAll();
    _ducks.RemoveAll();
    _cars.RemoveAll();
    _copters.RemoveAll();
    ServiceLocator::GetAudio()->StopAll();
}

bool WindowPlay::IsAllDinosaurDied() {
    for(int i = 0; i < _dinosaurs.GetObjectCount(); i++) {
        Dinosaur* dino = static_cast<Dinosaur*>(_dinosaurs.GetObject(i));
        if(dino->GetState() != Dinosaur::Dying) {
            return false;
        }
    }
    return true;
}

bool WindowPlay::IsTimeUp() {
    if(_playTime >= _timeline.GetFinishTime()) {
        return true;
    } else {
        return false;
    }
}

void WindowPlay::Show(sf::RenderWindow& window) {
    _state = Playing;
    DEBUG_PRINT("Playing\n");

    /******** begin setting up time to add dinosaur for each game level ********/
    float posX = 0;
    switch(Game::GetSelectedLevel()) {
        case 1: {
                _itemHorseCount = 3;
                _itemCarCount = 0;
                _itemCakeCount = 0;
                _itemCopterCount = 0;

                _timeline.Add(1, 10, posX, 250);
                _timeline.Add(1, 20, posX, 350);
                _timeline.Add(1, 30, posX, 450);
                _timeline.Add(1, 40, posX, 550);
            }
            break;
        case 2: {
                _itemHorseCount = 3;
                _itemCarCount = 0;
                _itemCakeCount = 0;
                _itemCopterCount = 0;

                _timeline.Add(1, 10, posX, 450);
                _timeline.Add(1, 15, posX, 550);
                _timeline.Add(1, 20, posX, 150);
                _timeline.Add(1, 30, posX, 150);
                _timeline.Add(1, 35, posX, 250);
                _timeline.Add(1, 40, posX, 450);
            }
            break;
        case 3: {
                _itemHorseCount = 2;
                _itemCarCount = 1;
                _itemCakeCount = 0;
                _itemCopterCount = 0;

                _timeline.Add(1, 10, posX, 150);
                _timeline.Add(1, 15, posX, 150);
                _timeline.Add(1, 20, posX, 250);
                _timeline.Add(1, 30, posX, 450);
                _timeline.Add(1, 35, posX, 250);
                _timeline.Add(1, 36, posX, 550);
                _timeline.Add(1, 40, posX, 450);
            }
            break;
        case 4: {
                _itemHorseCount = 3;
                _itemCarCount = 1;
                _itemCakeCount = 0;
                _itemCopterCount = 0;

                _timeline.Add(1, 10, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(1, 20, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(1, 21, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(1, 22, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(1, 31, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(1, 32, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(1, 40, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
            }
            break;
        case 5: {
                _itemHorseCount = 0;
                _itemCarCount = 0;
                _itemCakeCount = 0;
                _itemCopterCount = 0;

                _timeline.Add(2, 10, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(1, 15, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 20, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(1, 25, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 30, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 35, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(1, 40, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
            }
            break;
        case 6: {
                _itemHorseCount = 10;
                _itemCarCount = 3;
                _itemCakeCount = 0;
                _itemCopterCount = 0;

                _timeline.Add(2, 10, posX, 350);
                _timeline.Add(2, 20, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 21, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 22, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 23, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 24, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 25, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 30, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 31, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 32, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 33, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 34, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 35, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 36, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 37, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 38, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 39, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 40, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
            }
            break;
        case 7: {
                _itemHorseCount = 5;
                _itemCarCount = 3;
                _itemCakeCount = 0;
                _itemCopterCount = 0;

                _timeline.Add(1, 10, posX, 350);
                _timeline.Add(2, 12, posX, 150);
                _timeline.Add(1, 15, posX, 250);
                _timeline.Add(2, 25, posX, 250);
                _timeline.Add(1, 28, posX, 450);
                _timeline.Add(2, 35, posX, 150);
                _timeline.Add(2, 40, posX, 550);
                _timeline.Add(1, 45, posX, 450);
                _timeline.Add(1, 58, posX, 250);
                _timeline.Add(2, 59, posX, 250);
                _timeline.Add(3, 60, posX, 250);
            }
            break;
        case 8: {
                _itemHorseCount = 0;
                _itemCarCount = 0;
                _itemCakeCount = 3;
                _itemCopterCount = 0;

                _timeline.Add(3, 10, posX, 350);
                _timeline.Add(1, 12, posX, 150);
                _timeline.Add(3, 14, posX, 250);
                _timeline.Add(1, 16, posX, 250);
                _timeline.Add(3, 18, posX, 450);
                _timeline.Add(1, 20, posX, 350);
                _timeline.Add(3, 22, posX, 150);
                _timeline.Add(1, 24, posX, 250);
                _timeline.Add(3, 26, posX, 250);
                _timeline.Add(1, 28, posX, 450);
                _timeline.Add(2, 30, posX, 350);
                _timeline.Add(3, 40, posX, 350);
            }
            break;
        case 9: {
                _itemHorseCount = 3;
                _itemCarCount = 0;
                _itemCakeCount = 0;
                _itemCopterCount = 1;

                _timeline.Add(1, 10, posX, 550);
                _timeline.Add(1, 12, posX, 150);
                _timeline.Add(1, 14, posX, 250);
                _timeline.Add(1, 16, posX, 350);
                _timeline.Add(1, 18, posX, 550);
                _timeline.Add(3, 20, posX, 250);
                _timeline.Add(3, 30, posX, 350);
                _timeline.Add(3, 40, posX, 450);
                _timeline.Add(3, 50, posX, 350);
                _timeline.Add(3, 60, posX, 550);
            }
            break;
        case 10: {
                _itemHorseCount = 3;
                _itemCarCount = 1;
                _itemCakeCount = 1;
                _itemCopterCount = 1;

                _timeline.Add(1, 10, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 15, posX, 150);
                _timeline.Add(3, 20, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(1, 25, posX, 250);
                _timeline.Add(2, 30, posX, 350);
                _timeline.Add(3, 35, posX, 250);
                _timeline.Add(1, 40, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(1, 41, posX, 150);
                _timeline.Add(2, 42, posX, 350);
                _timeline.Add(3, 43, posX, 550);
                _timeline.Add(1, 50, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(1, 55, posX, 250);
                _timeline.Add(2, 60, posX, 250);
                _timeline.Add(1, 65, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 70, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 75, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(1, 80, posX, 350);
                _timeline.Add(2, 85, posX, 450);
                _timeline.Add(2, 90, posX, 150);
            }
            break;
        case 11: {
                _itemHorseCount = 0;
                _itemCarCount = 0;
                _itemCakeCount = 0;
                _itemCopterCount = 10;

                for(int i = 10; i <= 30; i++) {
                    _timeline.Add(2, i, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                }
                for(int i = 31; i <= 60; i++) {
                    _timeline.Add(1, i, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                }
                for(int i = 61; i <= 90; i++) {
                    _timeline.Add(3, i, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                }
            }
            break;
        case 12: {
                _itemHorseCount = 3;
                _itemCarCount = 3;
                _itemCakeCount = 3;
                _itemCopterCount = 10;

                _timeline.Add(3, 10, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 12, posX, 450);
                _timeline.Add(3, 15, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(3, 18, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(3, 21, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(3, 23, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(3, 27, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(3, 30, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 30, posX, 250);
                _timeline.Add(3, 32, posX, 150);
                _timeline.Add(sf::Randomizer::Random(1, 3), 38, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(3, 41, posX, 450);
                _timeline.Add(2, 50, posX, 450);
                _timeline.Add(3, 55, posX, 550);
                _timeline.Add(1, 56, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(1, 58, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(3, 60, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(sf::Randomizer::Random(1, 3), 70, posX, 250);
                _timeline.Add(2, 71, posX, 250);
                _timeline.Add(2, 73, posX, 550);
                _timeline.Add(1, 75, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 78, posX, 150);
                _timeline.Add(2, 80, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(1, 85, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 86, posX, 150);
                _timeline.Add(2, 87, posX, 250);
                _timeline.Add(2, 90, posX, 350);
                _timeline.Add(3, 91, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(1, 95, posX, 350);
                _timeline.Add(2, 96, posX, 450);
                _timeline.Add(1, 100, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 101, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(3, 102, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(3, 103, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 104, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(1, 105, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(3, 106, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(3, 110, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 111, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(3, 115, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(1, 116, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(2, 117, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(1, 118, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(3, 119, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
                _timeline.Add(3, 120, posX, sf::Randomizer::Random(1, 5) * 100 + 50);
            }
            break;
    }
    /******** end setting up time to add dinosaur for each game level ********/

    /******** begin creating basic game controls ********/
    ObjectManager ButtonItems;
    Button* btnItem1 = new Button(Game::GetImage("Button_Item_Horse"), 70, 480, 10);
    Button* btnItem2 = new Button(Game::GetImage("Button_Item_Car"), 70, 560, 10);
    Button* btnItem3 = new Button(Game::GetImage("Button_Item_Cake"), 70, 640, 10);
    Button* btnItem4 = new Button(Game::GetImage("Button_Item_Bomb"), 70, 720, 10);
    ButtonItems.Add("btnItem1", btnItem1);
    ButtonItems.Add("btnItem2", btnItem2);
    ButtonItems.Add("btnItem3", btnItem3);
    ButtonItems.Add("btnItem4", btnItem4);

    ObjectManager LabelItemCounts;
    Label* lblItem1 = new Label(Conversion::IntToString(_itemHorseCount), 16, btnItem1->GetPosition().x + 10, 55, sf::Color::White);
    Label* lblItem2 = new Label(Conversion::IntToString(_itemCarCount), 16, btnItem2->GetPosition().x + 10, 55, sf::Color::White);
    Label* lblItem3 = new Label(Conversion::IntToString(_itemCakeCount), 16, btnItem3->GetPosition().x + 10, 55, sf::Color::White);
    Label* lblItem4 = new Label(Conversion::IntToString(_itemCopterCount), 16, btnItem4->GetPosition().x + 10, 55, sf::Color::White);
    LabelItemCounts.Add("lblItem1", lblItem1);
    LabelItemCounts.Add("lblItem2", lblItem2);
    LabelItemCounts.Add("lblItem3", lblItem3);
    LabelItemCounts.Add("lblItem4", lblItem4);

    Wallpaper* wallpaper = new Wallpaper(Game::GetImage("Wallpaper_Map01"));
    PictureBox* picResume = new PictureBox(Game::GetImage("PictureBox_Resume"), 180, 200);
    Button* btnResume = new Button(Game::GetImage("Button_Resume"), 60, 200, 250);
    Button* btnExit = new Button(Game::GetImage("Button_Exit"), 60, 410, 250);
    Progressbar* progressbar = new Progressbar(10, 20, 200, 20, 100, sf::Color(50, 50, 50), sf::Color(200, 200, 200));
    Kid* kid = new Kid(Game::GetImage("Player_Kid"), 100);
    /******** end creating basic game controls ********/

    /******** begin playing ********/
    //Play Background music
    ServiceLocator::GetAudio()->PlayMusic("audio/music2.ogg", true);
    ExitState exitState = Nothing;
    while(_state != Exiting) {
        /******** begin check event ********/
        sf::Event event;
        while(window.GetEvent(event)) {
            // Window closed
            if(event.Type == sf::Event::Closed) {
                _state = Exiting;
                break;
            }

            // Escape key pressed
            if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape)) {
                _state = Pausing;
                DEBUG_PRINT("_state = Pausing\n");
                break;
            }

            // Shoot ball
            if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Space)) {
                if(kid->GetState() != Kid::Attack1 && kid->GetState() != Kid::Attack2 && kid->GetState() != Kid::Attack3) {
                    kid->ShootBall();
                }
            }

            //Use Item
            if(event.Type == sf::Event::MouseButtonReleased
                    && SFMLMouseState::IsMouseOver(_rectBattleArea, Game::GetInput())) {
                if(_selectedItem == 1) {
                    if(_itemHorseCount > 0) {
                        AddItemHorse(event.MouseButton.X, event.MouseButton.Y);
                        _itemHorseCount--;
                    }
                } else if(_selectedItem == 2) {
                    float robot_y = 0;
                    if(event.MouseButton.Y - 50 >= 100) {
                        robot_y = event.MouseButton.Y - 50;
                    } else {
                        robot_y = 100;
                    }
                    if(_itemCarCount > 0) {
                        AddItemCar(700, robot_y);
                        _itemCarCount--;
                    }
                } else if(_selectedItem == 3) {
                    if(_itemCakeCount > 0) {
                        AddItemCake(event.MouseButton.X, event.MouseButton.Y);
                        _itemCakeCount--;
                    }
                } else if(_selectedItem == 4) {
                    if(_copters.GetObjectCount() == 0) {
                        if(_itemCopterCount > 0) {
                            AddItemCopter(event.MouseButton.X, event.MouseButton.Y);
                            _itemCopterCount--;
                        }
                    }
                }
            }
        }

        //Item Button
        if(btnItem1->GetState() == Button::MouseReleased) {
            _selectedItem = 1;
        }

        if(btnItem2->GetState() == Button::MouseReleased) {
            _selectedItem = 2;
        }

        if(btnItem3->GetState() == Button::MouseReleased) {
            _selectedItem = 3;
        }

        if(btnItem4->GetState() == Button::MouseReleased) {
            _selectedItem = 4;
        }

        if(btnResume->IsEnable() == true && btnResume->GetState() == Button::MouseReleased) {
            _state = Playing;
            DEBUG_PRINT("_state = Playing\n");
        }

        if(btnExit->GetState() == Button::MouseReleased) {
            _state = Exiting;
            DEBUG_PRINT("_state = Exiting\n");
        }
        /******** end check event ********/

        /******** begin updating ********/
        if(_state == Playing) {
            //If Playing Then Update GameObject Normaly
            _playTime += Game::GetWindow().GetFrameTime();
            int playTime = (int)_playTime;

            //Add Dinosaurs
            if(_timeline.IsExist(playTime) && _timeline.IsMarked(playTime) == false) {
                _timeline.Mark(playTime);
                AddDinosaur(_timeline.GetX(playTime)
                            , _timeline.GetY(playTime)
                            , _timeline.GetId(playTime));
                DEBUG_PRINT("playtime %d Add dino at %f, %f\n", playTime, _timeline.GetX(playTime), _timeline.GetY(playTime));
            }

            //If TimeUp and All Dinosaur Died
            if(IsTimeUp() && IsAllDinosaurDied()) {
                //Player Win
                _state = Exiting;
                exitState = Win;
                DEBUG_PRINT("You Win\n");
                if(Game::GetSelectedLevel() >= Game::GetCurrentLevel()) {
                    Game::SetCurrentLevel(Game::GetCurrentLevel() + 1);
                }
            }

            int percent = (int)(_playTime / (float)_timeline.GetFinishTime() * 100);
            progressbar->SetValue(percent);
            if(progressbar->GetValue() >= 100) {
                progressbar->SetColor(sf::Color::Red);
            }

            //Update All Here (Keyword)
            ButtonItems.UpdateAll();
            LabelItemCounts.UpdateAll();
            _dinosaurs.UpdateAll();
            _ducks.UpdateAll();
            _cars.UpdateAll();
            _copters.UpdateAll();
            _smokes.UpdateAll();
            _horses.UpdateAll();
            _cakes.UpdateAll();
            progressbar->Update(Game::GetWindow().GetFrameTime());
            kid->Update(Game::GetWindow().GetFrameTime());
            lblItem1->SetText(Conversion::IntToString(_itemHorseCount));
            lblItem2->SetText(Conversion::IntToString(_itemCarCount));
            lblItem3->SetText(Conversion::IntToString(_itemCakeCount));
            lblItem4->SetText(Conversion::IntToString(_itemCopterCount));

            btnItem1->SetEnable(_itemHorseCount);
            btnItem2->SetEnable(_itemCarCount);
            btnItem3->SetEnable(_itemCakeCount);
            btnItem4->SetEnable(_itemCopterCount);

            //Check Dinosaur is in base
            int dinoCount = _dinosaurs.GetObjectCount();
            for(int i = 0; i < dinoCount; i++) {
                const Dinosaur* dino = static_cast<Dinosaur*>(_dinosaurs.GetObject(i));
                if(dino->GetPosition().x > Game::SCREEN_WIDTH - dino->GetWidth()) {
                    _state = Exiting;
                    exitState = Lose;
                    DEBUG_PRINT("You Lose\n");
                    break;
                }
            }

            /** begin destroy object **/
            _dinosaurs.RemoveDeadObject();
            _ducks.RemoveDeadObject();
            _smokes.RemoveDeadObject();
            _cars.RemoveDeadObject();
            _copters.RemoveDeadObject();
            _horses.RemoveDeadObject();
            _cakes.RemoveDeadObject();
            /** end destroy object **/
            btnResume->SetEnable(false);
        } else {
            //Update Pausing Object
            picResume->Update(Game::GetWindow().GetFrameTime());
            btnResume->SetEnable(true);
            btnResume->Update(Game::GetWindow().GetFrameTime());
            btnExit->Update(Game::GetWindow().GetFrameTime());
        }
        /******** end updating ********/

        /******** begin drawing ********/
        // Clear Screen
        window.Clear();

        //Draw All Here (Keyword)
        wallpaper->Draw(window);
        ButtonItems.DrawAll(window);
        LabelItemCounts.DrawAll(window);
        _copters.DrawAll(window);
        _horses.DrawAll(window);
        _cakes.DrawAll(window);
        kid->Draw(window);
        _dinosaurs.DrawAll(window);
        _cars.DrawAll(window);
        _ducks.DrawAll(window);
        _smokes.DrawAll(window);
        progressbar->Draw(window);

        //Draw Pausing Object
        if(_state == Pausing) {
            picResume->Draw(window);
            btnResume->Draw(window);
            btnExit->Draw(window);
        }

        //Update Screen
        window.Display();
        /******** end drawing ********/
    }
    /******** end playing ********/

    /******** begin exiting ********/
    if(exitState != Nothing) {
        Label* lblExitState = new Label("", 52, 250, 280, sf::Color::Black);
        float waitingTime = 0;
        while(waitingTime < 4) {
            waitingTime += Game::GetWindow().GetFrameTime();
            DEBUG_PRINT("waitingTime = %f\n", waitingTime);
            if(exitState == Win) {
                lblExitState->SetText("You Win :)");
            } else {
                lblExitState->SetText("You Lose :(");
            }
            lblExitState->Draw(window);
            window.Display();
        }
    }
    /******** end exiting ********/

    /******** begin free memory ********/
    _dinosaurs.RemoveAll();
    _ducks.RemoveAll();
    _cars.RemoveAll();
    _smokes.RemoveAll();
    _copters.RemoveAll();
    _horses.RemoveAll();
    _cakes.RemoveAll();
    delete btnResume;
    delete btnExit;
    delete wallpaper;
    delete progressbar;
    /******** end free memory ********/
}

ObjectManager& WindowPlay::GetDinosaurs() {
    return _dinosaurs;
}

ObjectManager& WindowPlay::GetHorses() {
    return _horses;
}

ObjectManager& WindowPlay::GetCakes() {
    return _cakes;
}

void WindowPlay::AddSmoke(float x, float y) {
    _smokes.Add("Smoke", new Smoke(Game::GetImage("Smoke"), 100, x, y));
    //ServiceLocator::GetAudio()->PlaySound("audio/door-10-close.ogg");
}

void WindowPlay::AddItem() {
    int num = sf::Randomizer::Random(0, 100);
    if(num <= 50) {
        //not drop 50%
    } else {
        if(num <= 80) {
            //drop tumble 30%
            _itemHorseCount += 1;
            DEBUG_PRINT("get item \"tumble\"\n");
        } else if(num <= 90) {
            //drop joystick 10
            _itemCarCount += 1;
            DEBUG_PRINT("get item \"joystick\"\n");
        } else if(num <= 97) {
            //drop robot 7
            _itemCakeCount += 1;
            DEBUG_PRINT("get item \"robot\"\n");
        } else {
            //drop copter 3
            _itemCopterCount += 1;
            DEBUG_PRINT("get item \"copter\"\n");
        }
        ServiceLocator::GetAudio()->PlaySound("audio/item-drop.ogg");
    }
}

void WindowPlay::AddDinosaur(float x, float y, int id) {
    switch(id) {
        case 1:
            //Stegosaurus
            _dinosaurs.Add("Dinosaur", new Dinosaur(Game::GetImage("Monster_Dinosaur01"), 100, x, y, 500, 5, 20, 0.1));
            break;
        case 2:
            //Pterodactyl
            _dinosaurs.Add("Dinosaur", new Dinosaur(Game::GetImage("Monster_Dinosaur02"), 87, x, y, 150, 15, 60, 0.1));
            break;
        default://3
            //T-rex
            _dinosaurs.Add("Dinosaur", new Dinosaur(Game::GetImage("Monster_Dinosaur03"), 89, x, y, 300, 25, 50, 0.1));
            break;

    }
}

void WindowPlay::AddItemDuck(float x, float y) {
    _ducks.Add("Duck", new ItemDuck(Game::GetImage("Item_Duck"), 50, x, y));
    _selectedItem = 0;
}

void WindowPlay::AddItemHorse(float x, float y) {
    _horses.Add("Horse", new ItemHorse(Game::GetImage("Item_Horse"), 100, x, y));
    _selectedItem = 0;
}

void WindowPlay::AddItemCake(float x, float y) {
    _cakes.Add("Cake", new ItemCake(Game::GetImage("Item_Cake"), 100, x, y));
    _selectedItem = 0;
}

void WindowPlay::AddItemCar(float x, float y) {
    _cars.Add("Car", new ItemCar(Game::GetImage("Item_Car"), 100, 700, y));
    _selectedItem = 0;
}

void WindowPlay::AddItemCopter(float x, float y) {
    _copters.Add("Copter", new ItemCopter(Game::GetImage("Item_Copter"), 100, x, y));
    _selectedItem = 0;
}
