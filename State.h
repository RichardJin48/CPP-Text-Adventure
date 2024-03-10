//
// Created by DrMark on 10/2/2017.
//

#ifndef TEXTADV_STATE_H
#define TEXTADV_STATE_H


#include "Room.h"

class State {
    Room *currentRoom;
    std::list<GameObject*> inventory;
public:
    explicit State(Room *startRoom);
    void goTo(Room *target);
    void announceLoc() const;
    void announceInv() const;
    void announceObj() const;
    Room* getCurrentRoom() const;
    void addInv(GameObject* object);
    void deleteInv(GameObject* object);
    void clearInv();

    std::list<GameObject *> getInventory() const;
    void setInventory(std::list<GameObject *> _inventory);
};


#endif //TEXTADV_STATE_H
