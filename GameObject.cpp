//
// Created by Jin Zichao on 2022/12/9.
//

#include "GameObject.h"
#include "Room.h"

/**
 * Stores a static array of all objects.
 */
std::list<GameObject*> GameObject::gameObjects;

GameObject::GameObject(const string* _name, const string* _desc, const string* _keyword) : name(_name), desc(_desc), keyword(_keyword), room(nullptr) {}

GameObject::~GameObject() {
    gameObjects.remove(this);
}

const string *GameObject::getName() const {
    return name;
}

const string *GameObject::getDesc() const {
    return desc;
}

const string *GameObject::getKeyword() const {
    return keyword;
}

/**
 * Statically creates a object and then adds it to the global list.
 */
GameObject* GameObject::addGameObject(const string* _name, const string* _desc, const string* _keyword) {
    auto *newObject = new GameObject(_name, _desc, _keyword);
    GameObject::gameObjects.push_back(newObject);
    return newObject;
}

Room *GameObject::getRoom() const {
    return room;
}

void GameObject::setRoom(Room *room) {
    GameObject::room = room;
}
