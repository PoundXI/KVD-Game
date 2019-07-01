#ifndef WindowPlay_HPP_INCLUDED
#define WindowPlay_HPP_INCLUDED

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "ObjectManager.hpp"
#include "Timeline.hpp"

class WindowPlay {
public:
    WindowPlay();
    ~WindowPlay();

    void Show(sf::RenderWindow& window);

    static ObjectManager& GetDinosaurs();
    static ObjectManager& GetHorses();
    static ObjectManager& GetCakes();
    static void AddDinosaur(float x, float y, int id);
    static void AddItemDuck(float x, float y);
    static void AddItemHorse(float x, float y);
    static void AddItemCake(float x, float y);
    static void AddItemCar(float x, float y);
    static void AddItemCopter(float x, float y);
    static void AddSmoke(float x, float y);
    static void AddItem();
private:
    //play state
    enum PlayState { Playing, Pausing, Exiting };
    enum ExitState { Nothing, Win, Lose };
    PlayState _state;

    //Time
    Timeline _timeline;
    float _playTime;

    //functions
    bool IsAllDinosaurDied();
    bool IsTimeUp(); //This mean no dinosaur to add

    //Object
    static ObjectManager _dinosaurs;
    static ObjectManager _smokes;
    static ObjectManager _horses;
    static ObjectManager _cakes;
    static ObjectManager _ducks;
    static ObjectManager _cars;
    static ObjectManager _copters;

    //Item
    static int _selectedItem;
    static int _itemHorseCount; //Horse
    static int _itemCarCount; //Car
    static int _itemCakeCount; //Cake
    static int _itemCopterCount; //Copter

    static const sf::FloatRect _rectBattleArea;
};

#endif // WindowPlay_HPP_INCLUDED
