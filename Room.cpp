//
// Created by DrMark on 10/2/2017.
//

#include "Room.h"
#include "wordwrap.h"
#include "strings.h"

/**
 * Stores a static vector of all rooms.
 */
std::vector<Room*> Room::rooms;

/**
 * Room default constructor.
 * @param _name Room's name.
 * @param _desc Room's description.
 */
Room::Room(const string* _name, const string *_desc) :
        name(_name), description(_desc), north(nullptr), south(nullptr), east(nullptr), west(nullptr), index(rooms.size()) {}

/**
 * Prints the description of a room (the name, long description, and objects)
 */
void Room::describe() const {
    wrapOut(this->name);
    wrapEndPara();
    wrapOut(this->description);
    wrapEndPara();
    showObjects();
}

/**
 * Prints the objects of a room
 */
void Room::showObjects() const {
    if(this->objects.empty()){
        wrapOut(&emOb);
    }
    else {
        wrapOut(&obj);
        for(GameObject* object: this->objects){
            wrapOut(object->getName());
            if (object != this->objects.back()) {
                wrapOut(&comma);
            }
        }
    }
    wrapEndPara();
}

/**
 * Statically creates a room and then adds it to the global vector.
 * @param _name Name for the new room.
 * @param _desc Description for the new room.
 * @return A pointer to the newly created room.
 */
Room* Room::addRoom(const string* _name, const string *_desc) {
    auto *newRoom = new Room(_name, _desc);
    Room::rooms.push_back(newRoom);
    return newRoom;
}

/**
 * Adds an existing room to the static vector.
 * @param room Pointer to the room to add.
 * @return
 */
void Room::addRoom(Room* room) {
    Room::rooms.push_back(room);
}

/**
 * Gets the north exit of a room.
 * @return The room that is north of this one, or NULL if there is no exit.
 */
Room* Room::getNorth() const {
    return this->north;
}
Room* Room::getSouth() const {
    return this->south;
}
Room* Room::getEast() const {
    return this->east;
}
Room* Room::getWest() const {
    return this->west;
}

/**
 * Sets the north exit of a room.
 * @param _north Pointer to the room to be north of this one.
 */
void Room::setNorth(Room* _north) {
    this->north = _north;
}
void Room::setSouth(Room* _south) {
    this->south = _south;
}
void Room::setEast(Room* _east) {
    this->east = _east;
}
void Room::setWest(Room* _west) {
    this->west = _west;
}

std::list<GameObject *> Room::getObjects() const {
    return objects;
}

void Room::setObjects(std::list<GameObject *> _objects) {
    this->objects = _objects;
}

void Room::addObj(GameObject* object){
    object->setRoom(this);
    this->objects.push_back(object);
}

void Room::deleteObj(GameObject* object){
    this->objects.remove(object);
}

void Room::clearObj(){
    this->objects.clear();
}

const string* Room::getName() const {
    return this->name;
}

int Room::getIndex() const {
    return index;
}
