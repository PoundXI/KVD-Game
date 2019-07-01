#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "Game.hpp"
#include "SFMLSoundProvider.hpp"
#include "ServiceLocator.hpp"

#include "WindowSplash.hpp"
#include "WindowMenu.hpp"
#include "WindowLevel.hpp"
#include "WindowOption.hpp"
#include "WindowAbout.hpp"
#include "WindowPlay.hpp"
#include "WindowPlayer.hpp"

#include "Debug.hpp"
#include "FileManager.hpp"

#include <cassert>

/** begin initialzation **/
// GameState
Game::GameState Game::_gameState = Uninitialized;

// Rendering
sf::RenderWindow Game::_mainWindow;
ObjectManager Game::_gameObjectManager;
const std::string Game::GAME_TITLE = "Kid Vs. Dinosaurs";

// ConfigFile
IniFile Game::_iniMain;
IniFile Game::_iniProfile;

// User Profile
std::string  Game::_playerName = "";
int         Game::_selectedLevel = 0;
int         Game::_currentLevel = 1;
bool        Game::_fullscreenMode = false;
bool        Game::_soundEnable = true;
bool        Game::_musicEnable = true;

std::map<std::string, sf::Image> Game::_mapImage;
/** end initialzation **/

void Game::LoadIniMain() {
    DEBUG_PRINT("Game::LoadIniMain() %s \n", _playerName.c_str());

    FileManager::CreateDirectoryPath("profiles", 0775);

    std::string filepath = "profiles/main.bin";
    if(FileManager::IsFileExists(filepath)) {
        DEBUG_PRINT("%s exists\n", filepath.c_str());
        _iniMain.LoadFromFile(filepath);
        _playerName = _iniMain.GetString("Main", "PlayerName", "");
    } else {
        //Create Dafault
        DEBUG_PRINT("%s not exists\n", filepath.c_str());
        _iniMain.LoadFromFile(filepath);
        _iniMain.SetString("Main", "PlayerName", "");
        _iniMain.SaveToFile();
        DEBUG_PRINT("creating %s \n", filepath.c_str());
    }
}

void Game::SaveIniMain() {
    DEBUG_PRINT("Game::SaveIniMain() %s \n", _playerName.c_str());

    _iniMain.SetString("Main", "PlayerName", _playerName);
    _iniMain.SaveToFile();
}

void Game::LoadIniProfile() {
    DEBUG_PRINT("Game::LoadIniProfile() %s \n", _playerName.c_str());

    _iniProfile.LoadFromFile("profiles/" + _playerName + ".bin");
    _currentLevel = _iniProfile.GetInt("Profile", "CurrentLevel", 1);
    _fullscreenMode = _iniProfile.GetBool("Profile", "FullscreenMode", false);
    _soundEnable = _iniProfile.GetBool("Profile", "SoundEnable", true);
    _musicEnable = _iniProfile.GetBool("Profile", "MusicEnable", true);
}

void Game::SaveIniProfile() {
    DEBUG_PRINT("Game::SaveIniProfile() %s \n", _playerName.c_str());

    _iniProfile.SetInt("Profile", "CurrentLevel", _currentLevel);
    _iniProfile.SetBool("Profile", "FullscreenMode", _fullscreenMode);
    _iniProfile.SetBool("Profile", "SoundEnable", _soundEnable);
    _iniProfile.SetBool("Profile", "MusicEnable", _musicEnable);
    _iniProfile.SaveToFile();
}

void Game::CreateIniProfile(std::string playerName) {
    std::string fileName = "profiles/" + playerName + ".bin";
    if(!FileManager::IsFileExists(fileName)) {
        _iniProfile.LoadFromFile(fileName);
        _iniProfile.SetInt("Profile", "CurrentLevel", 1);
        _iniProfile.SetBool("Profile", "FullscreenMode", false);
        _iniProfile.SetBool("Profile", "SoundEnable", true);
        _iniProfile.SetBool("Profile", "MusicEnable", true);
        _iniProfile.SaveToFile();
    }
}

sf::RenderWindow& Game::GetWindow() {
    return _mainWindow;
}
const sf::Input& Game::GetInput() {
    return _mainWindow.GetInput();
}

const ObjectManager& Game::GetObjectManager() {
    return _gameObjectManager;
}

bool Game::LoadImage() {
    std::string imageDir = "images/";

    //Load
    //WindowMenu
    _mapImage["Background_Menu"].LoadFromFile(imageDir + "Background_Menu.png");
    _mapImage["Button_Start"].LoadFromFile(imageDir + "Button_Start.png");
    _mapImage["Button_Option"].LoadFromFile(imageDir + "Button_Option.png");
    _mapImage["Button_About"].LoadFromFile(imageDir + "Button_About.png");
    _mapImage["Button_Exit"].LoadFromFile(imageDir + "Button_Exit.png");
    _mapImage["ListBox_Body"].LoadFromFile(imageDir + "ListBox_Body.png");
    _mapImage["ListBox_First"].LoadFromFile(imageDir + "ListBox_First.png");
    _mapImage["ListBox_Prev"].LoadFromFile(imageDir + "ListBox_Prev.png");
    _mapImage["ListBox_Next"].LoadFromFile(imageDir + "ListBox_Next.png");
    _mapImage["ListBox_Last"].LoadFromFile(imageDir + "ListBox_Last.png");
    _mapImage["ListBox_Delete"].LoadFromFile(imageDir + "ListBox_Delete.png");

    //WindowPlayer
    _mapImage["Background_All"].LoadFromFile(imageDir + "Background_All.png");
    _mapImage["PictureBox_Player"].LoadFromFile(imageDir + "PictureBox_Player.png");
    _mapImage["PictureBox_EnterName"].LoadFromFile(imageDir + "PictureBox_EnterName.png");
    _mapImage["Button_Create"].LoadFromFile(imageDir + "Button_Create.png");
    _mapImage["Button_ChangePlayer"].LoadFromFile(imageDir + "Button_ChangePlayer.png");

    //WindowOption
    _mapImage["PictureBox_Option"].LoadFromFile(imageDir + "PictureBox_Option.png");
    _mapImage["CheckBox"].LoadFromFile(imageDir + "CheckBox.png");
    _mapImage["Button_Back"].LoadFromFile(imageDir + "Button_Back.png");

    //WindowPlayer
    _mapImage["Background_About"].LoadFromFile(imageDir + "Background_About.png");

    //WindowLevel
    _mapImage["Button_Level01"].LoadFromFile(imageDir + "Button_Level01.png");
    _mapImage["Button_Level02"].LoadFromFile(imageDir + "Button_Level02.png");
    _mapImage["Button_Level03"].LoadFromFile(imageDir + "Button_Level03.png");
    _mapImage["Button_Level04"].LoadFromFile(imageDir + "Button_Level04.png");
    _mapImage["Button_Level05"].LoadFromFile(imageDir + "Button_Level05.png");
    _mapImage["Button_Level06"].LoadFromFile(imageDir + "Button_Level06.png");
    _mapImage["Button_Level07"].LoadFromFile(imageDir + "Button_Level07.png");
    _mapImage["Button_Level08"].LoadFromFile(imageDir + "Button_Level08.png");
    _mapImage["Button_Level09"].LoadFromFile(imageDir + "Button_Level09.png");
    _mapImage["Button_Level10"].LoadFromFile(imageDir + "Button_Level10.png");
    _mapImage["Button_Level11"].LoadFromFile(imageDir + "Button_Level11.png");
    _mapImage["Button_Level12"].LoadFromFile(imageDir + "Button_Level12.png");
    _mapImage["Button_Level13"].LoadFromFile(imageDir + "Button_Level13.png");
    _mapImage["Button_Level14"].LoadFromFile(imageDir + "Button_Level14.png");
    _mapImage["Button_Level15"].LoadFromFile(imageDir + "Button_Level15.png");

    //WindowPlay
    _mapImage["Wallpaper_Map01"].LoadFromFile(imageDir + "Wallpaper_Map01.png");
    _mapImage["PictureBox_Resume"].LoadFromFile(imageDir + "PictureBox_Resume.png");
    _mapImage["Player_Kid"].LoadFromFile(imageDir + "Player_Kid.png");
    _mapImage["Monster_Dinosaur01"].LoadFromFile(imageDir + "Monster_Dinosaur01.png");
    _mapImage["Monster_Dinosaur02"].LoadFromFile(imageDir + "Monster_Dinosaur02.png");
    _mapImage["Monster_Dinosaur03"].LoadFromFile(imageDir + "Monster_Dinosaur03.png");
    _mapImage["Smoke"].LoadFromFile(imageDir + "Smoke.png");
    _mapImage["Item_Duck"].LoadFromFile(imageDir + "Item_Duck.png");
    _mapImage["Item_Horse"].LoadFromFile(imageDir + "Item_Horse.png");
    _mapImage["Item_Cake"].LoadFromFile(imageDir + "Item_Cake.png");
    _mapImage["Item_Car"].LoadFromFile(imageDir + "Item_Car.png");
    _mapImage["Item_Copter"].LoadFromFile(imageDir + "Item_Copter.png");
    _mapImage["Item_Bomb"].LoadFromFile(imageDir + "Item_Bomb.png");
    _mapImage["Button_Resume"].LoadFromFile(imageDir + "Button_Resume.png");
    _mapImage["Button_Item_Horse"].LoadFromFile(imageDir + "Button_Item_Horse.png");
    _mapImage["Button_Item_Car"].LoadFromFile(imageDir + "Button_Item_Car.png");
    _mapImage["Button_Item_Cake"].LoadFromFile(imageDir + "Button_Item_Cake.png");
    _mapImage["Button_Item_Bomb"].LoadFromFile(imageDir + "Button_Item_Bomb.png");

    //Check Image
    std::map<std::string, sf::Image>::iterator it;
    for(it = _mapImage.begin(); it != _mapImage.end(); it++) {
        if(it->second.GetWidth() <= 0 && it->second.GetHeight() <= 0) {
            return false;
        }
    }
    return true;
}

const sf::Image& Game::GetImage(std::string imageName) {
    return _mapImage[imageName];
}

void Game::Start(void) {
    DEBUG_PRINT("Game Start\n");

    assert(LoadImage());

    LoadIniMain();

    //if(_playerName != "")
    LoadIniProfile();

    // Config Window
    if(_fullscreenMode == true) {
        _mainWindow.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_DEPTH), GAME_TITLE, sf::Style::Fullscreen);
    } else {
        _mainWindow.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_DEPTH), GAME_TITLE, sf::Style::Close);
    }

    // Set Framerate to reduce CPU usage.
    _mainWindow.SetFramerateLimit(FRAME_PER_SEC);

    // Config Sound & Music
    SFMLSoundProvider soundProvider;
    ServiceLocator::RegisterServiceLocator(&soundProvider);
    ServiceLocator::GetAudio()->SetSoundEnable(_soundEnable);
    ServiceLocator::GetAudio()->SetMusicEnable(_musicEnable);

    // Config Game State
    if(_gameState != Uninitialized)
        return;

    // Config Game State
    _gameState = Game::ShowingSplash;

    // Start Game Loop
    while(!IsExiting()) {
        GameLoop();
    }

    // Close Window
    _mainWindow.Close();
}

bool Game::IsExiting() {
    if(_gameState == Game::Exiting) {
        return true;
    } else {
        return false;
    }
}

int Game::GetSelectedLevel() {
    return _selectedLevel;
}

int Game::GetCurrentLevel() {
    return _currentLevel;
}

void Game::SetCurrentLevel(int value) {
    _currentLevel = value;
}

void Game::ShowSplashScreen() {
    WindowSplash windowSplash;
    windowSplash.Show(_mainWindow);

    if(_playerName != "") {
        _gameState = Game::ShowingMenu;
    } else {
        _gameState = Game::ShowingPlayer;
    }
}

void Game::ShowPlayer() {
    WindowPlayer windowPlayer;
    windowPlayer.Show(_mainWindow);

    SaveIniMain();
    LoadIniProfile();

    _gameState = Game::ShowingMenu;
}

void Game::ShowMenu() {
    WindowMenu menu;
    WindowMenu::MenuResult result = menu.Show(_mainWindow);
    switch(result) {
        case WindowMenu::Exit:
            _gameState = Game::Exiting;
            break;
        case WindowMenu::Play:
            _gameState = Game::ShowingLevel;
            break;
        case WindowMenu::Option:
            _gameState = Game::ShowingOption;
            break;
        case WindowMenu::About:
            _gameState = Game::ShowingAbout;
            break;
        case WindowMenu::ChangePlayer:
            _gameState = Game::ShowingPlayer;
            break;
    }
}

void Game::ShowLevel() {
    WindowLevel windowLevel;
    _selectedLevel = windowLevel.Show(_mainWindow);

    // Change Game State
    if(_selectedLevel == 0) {
        _gameState = Game::ShowingMenu;
    } else {
        _gameState = Game::Playing;
    }
}

void Game::ShowOption() {
    LoadIniProfile();

    WindowOption windowOption;
    windowOption.Show(_mainWindow);

    SaveIniProfile();

    _gameState = Game::ShowingMenu;
}

void Game::ShowAbout() {
    WindowAbout windowAbout;
    windowAbout.Show(_mainWindow);
    _gameState = Game::ShowingMenu;
}

void Game::Play() {
    WindowPlay windowPlay;
    windowPlay.Show(_mainWindow);
    SaveIniProfile();
    _gameState = Game::ShowingLevel;
}

void Game::GameLoop() {
    switch(_gameState) {
        case Game::ShowingSplash:
            ShowSplashScreen();
            break;
        case Game::ShowingPlayer:
            ShowPlayer();
            break;
        case Game::ShowingMenu:
            ShowMenu();
            break;
        case Game::ShowingLevel:
            ShowLevel();
            break;
        case Game::Playing:
            Play();
            break;
        case Game::ShowingOption:
            ShowOption();
            break;
        case Game::ShowingAbout:
            ShowAbout();
            break;
    }
}

//Screen
void Game::SetFullscreen(bool enable) {
    _fullscreenMode = enable;
}

bool Game::IsFullscreen() {
    return _fullscreenMode;
}

//Sound
void Game::SetSoundEnable(bool enable) {
    _soundEnable = enable;
}

bool Game::IsSoundEnable() {
    return _soundEnable;
}

//Music
void Game::SetMusicEnable(bool enable) {
    _musicEnable = enable;
}

bool Game::IsMusicEnable() {
    return _musicEnable;
}

void Game::SetPlayerName(std::string playerName) {
    _playerName = playerName;
}

std::string Game::GetPlayerName() {
    return _playerName;
}
