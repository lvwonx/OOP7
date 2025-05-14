#pragma once

using namespace System::Drawing;

class PopObject {
public:
    virtual ~PopObject() {}

    virtual void setPos(float x, float y) = 0;
    virtual float getX() = 0;
    virtual float getY() = 0;
    virtual int getSize() = 0;
    virtual void setSpeed(float dX, float dY) = 0;
    virtual float getDX() = 0;
    virtual float getDY() = 0;
    virtual void scaleSpeed(float factor) = 0;

    virtual void move() = 0;
    virtual void draw(System::Drawing::Graphics^ graphics) = 0;
    virtual void interact(PopObject* popObject) = 0;
    virtual bool interactable(PopObject* otherObject) const = 0;

    
    virtual void doCommand(int command) = 0;
};