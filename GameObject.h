//
// Created by Jin Zichao on 2022/12/9.
//
#ifndef TEXTADV_GAMEOBJECT_H
#define TEXTADV_GAMEOBJECT_H
#include <string>
#include <list>

using std::string;
class Room;

class GameObject {
    const string* name;
    const string* desc;
    const string* keyword;
    Room *room;
public:
    GameObject(const string* _name, const string* _desc, const string* _keyword);
    virtual ~GameObject();
    const string *getName() const;
    const string *getDesc() const;
    const string *getKeyword() const;
    static std::list<GameObject*> gameObjects;
    static GameObject* addGameObject(const string* _name, const string* _desc, const string* _keyword);
    Room *getRoom() const;
    void setRoom(Room *room);
};


#endif //TEXTADV_GAMEOBJECT_H
