//
// Created by DrMark on 10/4/2017.
//

#ifndef TEXTADV_STRINGS_H
#define TEXTADV_STRINGS_H


#include <string>

const std::string r1name = "Room 1";
const std::string r1desc = "You are in room 1. It's really quite boring, but then, it's just for testing really. There are four passages.";
const std::string r2name = "Blue Room";
const std::string r2desc = "You are the blue room. You know because it's blue. That's about all though. There's a passage to the south.";
const std::string r3name = "Red Room";
const std::string r3desc = "You are the red room. You know because it's red. That's about all though. There's a passage to the north.";
const std::string r4name = "Green Room";
const std::string r4desc = "You are the green room. You know because it's green. That's about all though. There's a passage to the west.";
const std::string r5name = "Yellow Room";
const std::string r5desc = "You are the yellow room. You know because it's yellow. That's about all though. There's a passage to the east.";

const std::string badExit = "You can't go that way.";
const std::string badCommand = "I don't understand that.";

const std::string comma = ", ";
const std::string noEx = "The object does not exist!";
const std::string noOb = "The object is not in the room!";
const std::string noIn = "The object is not in the inventory!";
const std::string inOb = "The object is already in the room!";
const std::string inIn = "The object is already in the inventory!";
const std::string emIn = "The inventory is empty.";
const std::string emOb = "There is nothing in the room.";
const std::string get = "has been got.";
const std::string drop = "has been dropped.";
const std::string inv = "Objects in the inventory: ";
const std::string obj = "Objects in the room: ";

const std::string save = "Please give a name to the game file you want to save";
const std::string load = "Please enter the name of the game file you want to load";
const std::string saveFin = "The game has been saved.";
const std::string loadFin = "The game loading finished.";
const std::string noFile = "Load failed! The file does not exist!";
const std::string fileBro = "Load failed! The file is broken!";

const std::string o1name = "Knife(k)";
const std::string o1desc = "It is a tool for cutting.";
const std::string o1keyword = "k";
const std::string o2name = "Wood(w)";
const std::string o2desc = "It is a piece of wood.";
const std::string o2keyword = "w";
const std::string o3name = "Stone(s)";
const std::string o3desc = "It is a very hard stone.";
const std::string o3keyword = "s";
const std::string o4name = "Tea(t)";
const std::string o4desc = "It is a kind of drink.";
const std::string o4keyword = "t";
const std::string o5name = "Chicken(c)";
const std::string o5desc = "It is a kind of food.";
const std::string o5keyword = "c";

#endif //TEXTADV_STRINGS_H
