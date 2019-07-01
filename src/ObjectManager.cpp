#include "ObjectManager.hpp"
#include "Game.hpp"
#include "Debug.hpp"

ObjectManager::ObjectManager() {
}

ObjectManager::~ObjectManager() {
    RemoveAll();
}

void ObjectManager::Add(std::string name, IVisibleObject* object) {
    _objects.push_back(std::make_pair(name, object));
}

void ObjectManager::Remove(std::string name) {
    std::vector< std::pair<std::string, IVisibleObject*> >::iterator results = _objects.begin();
    while(results != _objects.end()) {
        if(results->first == name) {
            delete results->second;
            _objects.erase(results);
            break;
        }
        results++;
    }
}

void ObjectManager::Remove(int index) {
    delete(_objects.begin() + index)->second;
    _objects.erase(_objects.begin() + index);
}

void ObjectManager::RemoveDeadObject() {
    std::vector< std::pair<std::string, IVisibleObject*> >::iterator results = _objects.begin();
    while(results != _objects.end()) {
        if(results->second->IsDead()) {
            delete results->second;
            _objects.erase(results);
            break;
        }
        results++;
    }
}

void ObjectManager::RemoveAll() {
    std::for_each(_objects.begin(), _objects.end(), ObjectDeallocator());
    _objects.clear();
}

IVisibleObject* ObjectManager::GetObject(std::string name) const {
    std::vector< std::pair<std::string, IVisibleObject*> >::const_iterator results = _objects.begin();
    while(results != _objects.end()) {
        if(results->first == name) {
            return results->second;
        }
        results++;
    }
    return NULL;
}

IVisibleObject* ObjectManager::GetObject(int index) const {
    return _objects.at(index).second;
}

std::string ObjectManager::GetName(int index) {
    return _objects.at(index).first;
}

int ObjectManager::GetObjectCount() const {
    return _objects.size();
}

void ObjectManager::DrawAll(sf::RenderWindow& renderWindow) {
    std::vector< std::pair<std::string, IVisibleObject*> >::const_iterator itr = _objects.begin();
    while(itr != _objects.end()) {
        itr->second->Draw(renderWindow);
        itr++;
    }
}

void ObjectManager::UpdateAll() {
    std::vector< std::pair<std::string, IVisibleObject*> >::const_iterator itr = _objects.begin();
    float timeDelta = Game::GetWindow().GetFrameTime();

    while(itr != _objects.end()) {
        itr->second->Update(timeDelta);
        itr++;
    }
}
