#pragma once

#include "PopObject.h"
using namespace System::Drawing;

class Mover : public PopObject {
protected:
    float _x, _y;
    float _dX, _dY;
    int _size;
    int _color;
    int _frameWidth, _frameHeight;
    bool _paused;

    virtual void checkWallCollision();
public:
    Mover(int frameWidth, int frameHeight, int x, int y, int size = 20, int color = System::Drawing::Color::Red.ToArgb());

    virtual ~Mover() override {}

    virtual void setPos(float x, float y) override;
    virtual float getX() override { return _x; }
    virtual float getY() override { return _y; }
    virtual int getSize() override { return _size; }

    virtual void setSpeed(float dX, float dY) override;
    virtual float getDX() override { return _dX; }
    virtual float getDY() override { return _dY; }
    virtual void scaleSpeed(float factor) override;

    virtual void move() override;
    virtual void draw(System::Drawing::Graphics^ graphics) override = 0;
    virtual void interact(PopObject* popObject) override;
    virtual bool interactable(PopObject* otherObject) const override;

    // Default implementation for doCommand
    virtual void doCommand(int command) override;

    void togglePause() { _paused = !_paused; }
    int getColor() { return _color; }
    void setColor(int color) { _color = color; }
    void setSize(int size) { _size = size > 0 ? size : 1; }

    int getFrameWidth() const { return _frameWidth; }
    int getFrameHeight() const { return _frameHeight; }

    void followTo(int x, int y);
    void followAway(int x, int y);
    float getCurrentSpeedMagnitude() const;
};