//
// Created by DrMark on 10/2/2017.
//


#ifndef TEXTADV_ROOM_H
#define TEXTADV_ROOM_H

#include <string>
#include <forward_list>
#include <list>
#include <vector>

#include "GameObject.h"

using std::string;

/**
 * Represents a room (accessible location in the game).
 */
class Room {
    /**
     * Short name used as a header.
     */
    const string* name;
    /**
     * Full description of the room.
     */
    const string* description;
    /**
     * Pointer to room that is north of this one.
     */
    Room* north;
    Room* south;
    Room* east;
    Room* west;
    std::list<GameObject*> objects;
    const int index;
public:
    /**
     * Constructs a new Room.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    Room(const string *_name, const string *_desc);

    /**
     * Outputs the name and description of the room
     * in standard format.
     */
    void describe() const;
    void showObjects() const;

    /**
     * Vector storing all rooms that have been registered via addRoom().
     */
    static std::vector<Room*> rooms;

    /**
     * Creates a new Room with the given parameters and register it with the static list.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    static Room* addRoom(const string* _name, const string* _desc);
    static void addRoom(Room* room);

    Room* getNorth() const;
    void setNorth(Room* _north);
    Room* getSouth() const;
    void setSouth(Room* _south);
    Room* getEast() const;
    void setEast(Room* _east);
    Room* getWest() const;
    void setWest(Room* _west);

    std::list<GameObject *> getObjects() const;
    void setObjects(std::list<GameObject *> _objects);

    void addObj(GameObject* object);
    void deleteObj(GameObject* object);
    void clearObj();

    const string* getName() const;
    int getIndex() const;
};

#endif //TEXTADV_ROOM_H
