//
// Created by DrMark on 10/2/2017.
//

#include "State.h"
#include "wordwrap.h"
#include "strings.h"

/**
 * Current state of the game.
 */

/**
 * Display the description of the room the player is in.
 */
void State::announceLoc() const {
    this->currentRoom->describe();
}

/**
 * Constructor.
 * @param startRoom Pointer to the room to start in.
 */
State::State(Room *startRoom) : currentRoom(startRoom) {};

/**
 * Move to a specified room and print its description.
 * @param target Pointer to the room to move to.
 */
void State::goTo(Room *target) {
    this->currentRoom = target;
    this->announceLoc();
}

/**
 * Return a pointer to the current room.
 * @return Pointer to the current room.
 */
Room* State::getCurrentRoom() const {
    return this->currentRoom;
}

std::list<GameObject *> State::getInventory() const {
    return inventory;
}

void State::setInventory(std::list<GameObject *> _inventory) {
    this->inventory = _inventory;
}

/**
 * Display the objects in the inventory.
 */
void State::announceInv() const {
    if(this->inventory.empty()){
        wrapOut(&emIn);
    }
    else {
        wrapOut(&inv);
        for(GameObject* object: this->inventory){
            wrapOut(object->getName());
            if (object != this->inventory.back()) {
                wrapOut(&comma);
            }
        }
    }
    wrapEndPara();
}

/**
 * Display the objects in the current room.
 */
void State::announceObj() const {
    this->currentRoom->showObjects();
}

void State::addInv(GameObject* object){
    object->setRoom(nullptr);
    this->inventory.push_back(object);
}

void State::deleteInv(GameObject* object){
    this->inventory.remove(object);
}

void State::clearInv(){
    this->inventory.clear();
}