#pragma once

#include "Mover.h"
// Forward declare other types Tree might interact with or check against
class Ball;
class Triangle;
class Rectangle;
class Star;

class Tree : public Mover {
public:
    Tree(int frameWidth, int frameHeight, int x, int y, int size = 50, int color = System::Drawing::Color::DarkGreen.ToArgb()); //
    virtual ~Tree() override {}

    virtual void draw(System::Drawing::Graphics^ g) override;
    virtual void move() override; // Trees don't move
    virtual bool interactable(PopObject* otherObject) const override; //
    // interact() will use Mover's default as trees are passive obstacles
};