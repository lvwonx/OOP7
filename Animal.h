#pragma once

#include "Mover.h"
// Forward declare other types Animal might interact with or check against
class Ball;
class Triangle;
class Rectangle;
class Star;

class Animal : public Mover {
public:
    Animal(int frameWidth, int frameHeight, int x, int y, int size = 20, int color = System::Drawing::Color::Brown.ToArgb());
    virtual ~Animal() override {}

    virtual void draw(System::Drawing::Graphics^ g) override;
    virtual void move() override; // Animals might have specific movement
    virtual bool interactable(PopObject* otherObject) const override; //
    // interact() will use Mover's default or can be overridden if needed
};