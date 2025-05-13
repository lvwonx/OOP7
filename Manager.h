#pragma once
#include "PopObject.h"

class Ball;
class Triangle;
class Rectangle;
class Star;
class Explosion;

#define MAX_OBJECTS 1000

class Manager {
    // private: // Change this to public
public: // Made public to allow iteration/access from MainForm
    PopObject* objects[MAX_OBJECTS];
private: // Other members can remain private
    int frameWidth, frameHeight;

    void resolveCollision(PopObject* obj1, PopObject* obj2);

public:
    Manager(int frameWidth, int frameHeight);
    ~Manager();

    void add(PopObject* object);
    void remove(PopObject* objectToRemove);

    void drawFrame(System::Drawing::Graphics^ graphics);
    void move();
    void doCommand(int command);

    void scaleSpeed(float factor);
    PopObject* search(int x, int y);

    int countBalls();
    int countRectangles();
    int countTriangles();
    int countStars();

    void __cdecl destroyAll();

    PopObject* nearest(PopObject* popObject);
    PopObject* nearestFriend(PopObject* popObject);
    PopObject* nearestAlien(PopObject* popObject);
    float getDistance(PopObject* obj1, PopObject* obj2) const;

    // Make MAX_OBJECTS accessible if needed from other files like MainForm
    static const int MaxObjects = MAX_OBJECTS; // Optional: Add a static const member
};

extern Manager* manager;