#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

#include "ObjectManager.hpp"
#include "IniFile.hpp"

class Game {
public:
    static void Start();

    static sf::RenderWindow& GetWindow();
    const static sf::Input& GetInput();
    const static ObjectManager& GetObjectManager();

    //User Profile
    static void SetPlayerName(std::string playerName);
    static std::string GetPlayerName();
    static int GetSelectedLevel();
    static int GetCurrentLevel();
    static void SetCurrentLevel(int value);
    static void SetFullscreen(bool enable);
    static bool IsFullscreen();
    static void SetSoundEnable(bool enable);
    static bool IsSoundEnable();
    static void SetMusicEnable(bool enable);
    static bool IsMusicEnable();

    static const sf::Image& GetImage(std::string imageName);

    //Constant
    static const int SCREEN_WIDTH = 800;
    static const int SCREEN_HEIGHT = 600;

    static void CreateIniProfile(std::string playerName);
private:
    static bool IsExiting();
    static void GameLoop();

    static bool LoadImage();

    static void ShowSplashScreen();
    static void ShowPlayer();
    static void ShowMenu();
    static void ShowLevel();
    static void ShowOption();
    static void ShowAbout();
    static void Play();

    //GameState
    enum GameState { Uninitialized
                     , ShowingSplash
                     , ShowingPlayer
                     , ShowingMenu
                     , ShowingOption
                     , ShowingAbout
                     , ShowingLevel
                     , Playing
                     , Exiting
                   };
    static GameState _gameState;

    //Rendering
    static const int FRAME_PER_SEC = 60;
    static const int COLOR_DEPTH = 32;
    static const std::string GAME_TITLE;
    static sf::RenderWindow _mainWindow;
    static ObjectManager _gameObjectManager;

    //ConfigFile
    static IniFile _iniMain;
    static IniFile _iniProfile;
    static void LoadIniMain();
    static void SaveIniMain();
    static void LoadIniProfile();
    static void SaveIniProfile();

    //User Profile
    static std::string  _playerName;
    static int          _selectedLevel;
    static int          _currentLevel;
    static bool         _fullscreenMode;
    static bool         _soundEnable;
    static bool         _musicEnable;

    static std::map<std::string, sf::Image> _mapImage;
};

#endif // GAME_HPP_INCLUDED


