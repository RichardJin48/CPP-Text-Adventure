#include <iostream>
#include <iomanip>
#include <memory>
#include <iterator>
#include <vector>
#include <forward_list>
#include <map>
#include <fstream>
#include <sstream>
#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include "strings.h"

using std::string;
using std::list;
using std::unique_ptr;
using std::endl;
using std::ios;

State *currentState;
string commandBuffer;

/**
 * Print out the command prompt then read a command into the provided string buffer.
 * @param buffer Pointer to the string buffer to use.
 */
void inputCommand(string *buffer) {
    buffer->clear();
    std::cout << "> ";
    getline(std::cin, *buffer);
}

/**
 * Sets up the map.
 */
void initRooms() {
    auto * r1 = Room::addRoom(&r1name, &r1desc);
    auto * r2 = Room::addRoom(&r2name, &r2desc);
    auto * r3 = Room::addRoom(&r3name, &r3desc);
    auto * r4 = Room::addRoom(&r4name, &r4desc);
    auto * r5 = Room::addRoom(&r5name, &r5desc);
    r1->setNorth(r2);
    r2->setSouth(r1);
    r1->setSouth(r3);
    r3->setNorth(r1);
    r1->setEast(r4);
    r4->setWest(r1);
    r1->setWest(r5);
    r5->setEast(r1);
    auto * o1 = GameObject::addGameObject(&o1name, &o1desc, &o1keyword);
    auto * o2 = GameObject::addGameObject(&o2name, &o2desc, &o2keyword);
    auto * o3 = GameObject::addGameObject(&o3name, &o3desc, &o3keyword);
    auto * o4 = GameObject::addGameObject(&o4name, &o4desc, &o4keyword);
    auto * o5 = GameObject::addGameObject(&o5name, &o5desc, &o5keyword);
    auto * o2a = GameObject::addGameObject(&o2name, &o2desc, &o2keyword);
    auto * o3a = GameObject::addGameObject(&o3name, &o3desc, &o3keyword);
    auto * o4a = GameObject::addGameObject(&o4name, &o4desc, &o4keyword);
    auto * o5a = GameObject::addGameObject(&o5name, &o5desc, &o5keyword);
    r1->addObj(o1);
    r1->addObj(o2);
    r1->addObj(o3);
    r1->addObj(o4);
    r1->addObj(o5);
    r2->addObj(o2a);
    r3->addObj(o3a);
    r4->addObj(o4a);
    r5->addObj(o5a);
}

/**
 * Sets up the game state.
 */
void initState() {
    currentState = new State(Room::rooms[0]);
}

/**
 * Search the object in the list by keyword.
 */
GameObject* searchObject(const string& keyword, const list<GameObject*>& objects){
    for(GameObject* object: objects) {
        if (keyword == *object->getKeyword()) {
            return object;
        }
    }
    return nullptr;
}

/**
 * Validate the game file.
 */
bool validateFile(const string& fileName){
    std::ifstream checkFile(fileName + ".txt", ios::in|ios::binary);
    int oneIndex;
    int objNum = 0;

    /* Validate the index of the current room */
    if(checkFile.read((char*)&oneIndex, sizeof(int))){
        if(!(0 <= oneIndex && oneIndex < Room::rooms.size())){
            checkFile.close();
            return false;
        }
    }
    else{
        checkFile.close();
        return false;
    }

    /* Validate the index of the room to which each item belongs */
    while(checkFile.read((char*)&oneIndex, sizeof(int))){
        if(!(0 <= oneIndex && oneIndex < Room::rooms.size() || oneIndex == -1)){
            checkFile.close();
            return false;
        }
        objNum++;
    }

    /* Validate the number of game objects */
    if(objNum != GameObject::gameObjects.size()){
        checkFile.close();
        return false;
    }

    checkFile.close();
    return true;
}

/**
 * The main game loop.
 */
void gameLoop() {
    bool gameOver=false;
    while (!gameOver) {
        /* Ask for a command. */
        bool commandOk = false;
        inputCommand(&commandBuffer);

        /* The first word of a command would normally be the verb. The first word is the text before the first
         * space, or if there is no space, the whole string. */
        auto endOfVerb = static_cast<int8_t>(commandBuffer.find(' '));
        string secondWord;
        if(endOfVerb != string::npos) {
            secondWord = commandBuffer.substr(endOfVerb+1);
        }

        /* Search the object in the current room and the inventory by the second word. */
        GameObject* objectOb = searchObject(secondWord,currentState->getCurrentRoom()->getObjects());
        GameObject* objectIn = searchObject(secondWord,currentState->getInventory());

        /* Move commands */
        string directions[8] = {"north", "n", "south", "s", "east", "e", "west", "w"};
        Room *rooms[4] = {currentState->getCurrentRoom()->getNorth(),currentState->getCurrentRoom()->getSouth(),currentState->getCurrentRoom()->getEast(),currentState->getCurrentRoom()->getWest()};
        for(int i=0;i<4;i++) {
            if ((commandBuffer.compare(0,endOfVerb,directions[2*i]) == 0) || (commandBuffer.compare(0,endOfVerb,directions[2*i+1]) == 0)) {
                commandOk = true; /* Confirm command has been handled */
                /* See if there's an exit */
                if (rooms[i] == nullptr) { /* there isn't */
                    wrapOut(&badExit);      /* Output the "can't go there" message */
                    wrapEndPara();
                } else {                    /* There is */
                    currentState->goTo(rooms[i]); /* Update state to that room - this will also describe it */
                }
            }
        }

        if (commandBuffer.compare(0,endOfVerb,"get") == 0) {
            commandOk = true;
            if (objectOb != nullptr) {
                if (objectIn == nullptr) {
                    currentState->getCurrentRoom()->deleteObj(objectOb);
                    currentState->addInv(objectOb);
                    wrapOut(objectOb->getName());
                    wrapOut(&get);
                    wrapEndPara();
                    currentState->announceObj();
                    currentState->announceInv();
                }
                else {
                    wrapOut(&inIn);
                    wrapEndPara();
                }
            }
            else {
                if (objectIn == nullptr) {
                    wrapOut(&noEx);
                    wrapEndPara();
                }
                else {
                    wrapOut(&noOb);
                    wrapEndPara();
                }
            }
        }

        if (commandBuffer.compare(0,endOfVerb,"drop") == 0) {
            commandOk = true;
            if (objectIn != nullptr) {
                if (objectOb == nullptr) {
                    currentState->deleteInv(objectIn);
                    currentState->getCurrentRoom()->addObj(objectIn);
                    wrapOut(objectIn->getName());
                    wrapOut(&drop);
                    wrapEndPara();
                    currentState->announceObj();
                    currentState->announceInv();
                }
                else {
                    wrapOut(&inOb);
                    wrapEndPara();
                }
            }
            else {
                if (objectOb == nullptr) {
                    wrapOut(&noEx);
                    wrapEndPara();
                }
                else {
                    wrapOut(&noIn);
                    wrapEndPara();
                }
            }
        }

        if ((commandBuffer.compare(0,endOfVerb,"inventory") == 0) || (commandBuffer.compare(0,endOfVerb,"i") == 0)) {
            commandOk = true;
            currentState->announceInv();
        }

        if (commandBuffer.compare(0,endOfVerb,"examine") == 0) {
            commandOk = true;
            if(objectOb != nullptr){
                wrapOut(objectOb->getDesc());
            }
            else if(objectIn != nullptr){
                wrapOut(objectIn->getDesc());
            }
            else{
                wrapOut(&noEx);
            }
            wrapEndPara();
        }

        if (commandBuffer.compare(0,endOfVerb,"save") == 0) {
            commandOk = true;
            wrapOut(&save);
            inputCommand(&commandBuffer);
            std::ofstream gameFile(commandBuffer + ".txt", ios::out|ios::binary);
            int index;

            /* Store the index of current room as the first number */
            index = currentState->getCurrentRoom()->getIndex();
            gameFile.write((char*)&index, sizeof(int));

            /* Store the index of the room to which each item belongs */
            for(GameObject* object: GameObject::gameObjects){
                if(object->getRoom() != nullptr) {  //If the object in a room
                    index = object->getRoom()->getIndex();
                }
                else{  //If the object in the inventory
                    index = -1;
                }
                gameFile.write((char*)&index, sizeof(int));
            }

            gameFile.close();
            wrapOut(&saveFin);
            wrapEndPara();
        }

        if (commandBuffer.compare(0,endOfVerb,"load") == 0) {
            commandOk = true;
            wrapOut(&load);
            inputCommand(&commandBuffer);
            std::ifstream gameFile(commandBuffer + ".txt", ios::in|ios::binary);
            if(gameFile.good()){  //If the file exists
                bool fileValid = validateFile(commandBuffer);

                if(fileValid){  //If the file is valid
                    int index;

                    /* Load the current room */
                    gameFile.read((char*)&index, sizeof(int));
                    currentState = new State(Room::rooms.at(index));

                    /* Clear the objects in each room and the inventory */
                    for(Room* room: Room::rooms){
                        room->clearObj();
                    }
                    currentState->clearInv();

                    /* Load the index of the room to which each item belongs */
                    for(GameObject* object: GameObject::gameObjects){
                        gameFile.read((char*)&index, sizeof(int));
                        if (index != -1) {  //If the object in a room
                            Room::rooms.at(index)->addObj(object);
                        }
                        else{  //If the object in the inventory
                            currentState->addInv(object);
                        }
                    }

                    wrapOut(&loadFin);
                    wrapEndPara();
                }
                else{
                    wrapOut(&fileBro);
                    wrapEndPara();
                }
            }
            else{
                wrapOut(&noFile);
                wrapEndPara();
            }
            gameFile.close();
            currentState->announceLoc();
        }

//        /* My first version of the exercise 1 question 4. */
//        string directions[8] = {"north", "n", "south", "s", "east", "e", "west", "w"};
//        Room *rooms[4] = {currentState->getCurrentRoom()->getNorth(),currentState->getCurrentRoom()->getSouth(),currentState->getCurrentRoom()->getEast(),currentState->getCurrentRoom()->getWest()};
//        std::map<string, Room *> map;
//        bool compare = false;
//        for(int i=0;i<8;i++) {
//            map.insert(make_pair(directions[i],rooms[i/2]));
//            if(commandBuffer.compare(0,endOfVerb,directions[i]) == 0){
//                compare = true;
//            }
//        }
//        if (compare) {
//            commandOk = true; /* Confirm command has been handled */
//            /* See if there's an exit */
//            if (map[commandBuffer.substr(0,endOfVerb)] == nullptr) { /* there isn't */
//                wrapOut(&badExit);      /* Output the "can't go there" message */
//                wrapEndPara();
//            } else {                    /* There is */
//                currentState->goTo(map[commandBuffer.substr(0,endOfVerb)]); /* Update state to that room - this will also describe it */
//            }
//        }

        /* Quit command */
        if (commandBuffer.compare(0,endOfVerb,"quit") == 0) {
            commandOk = true;
            gameOver = true;
        }

        /* If commandOk hasn't been set, command wasn't understood, display error message */
        if (!commandOk) {
            wrapOut(&badCommand);
            wrapEndPara();
        }
    }
}

int main() {
    initWordWrap();
    initRooms();
    initState();
    currentState->announceLoc();
    gameLoop();
    return 0;
}