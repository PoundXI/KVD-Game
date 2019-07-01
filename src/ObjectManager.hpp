#ifndef OBJECTMANAGER_HPP_INCLUDED
#define OBJECTMANAGER_HPP_INCLUDED

#include "IVisibleObject.hpp"

#include <string>
#include <vector>
#include <utility>

class ObjectManager {
public:
    ObjectManager();
    ~ObjectManager();

    void Add(std::string name, IVisibleObject* object);
    void Remove(std::string name);
    void Remove(int index);
    void RemoveDeadObject();
    void RemoveAll();

    int GetObjectCount() const;
    IVisibleObject* GetObject(std::string name) const;
    IVisibleObject* GetObject(int index) const;
    std::string GetName(int index);

    void DrawAll(sf::RenderWindow& renderWindow);
    void UpdateAll();

private:
    std::vector< std::pair<std::string, IVisibleObject*> > _objects;

    struct ObjectDeallocator {
        void operator()(const std::pair<std::string, IVisibleObject*> & p) const {
            delete p.second;
        }
    };
};

#endif // GAMEOBJECTMANAGER_HPP_INCLUDED
