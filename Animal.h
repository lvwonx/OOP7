#pragma once

#include "Mover.h"

class Ball;
class Triangle;
class Rectangle;
class Star;

class Animal : public Mover {
public:
    Animal(int frameWidth, int frameHeight, int x, int y, int size = 20, int color = System::Drawing::Color::Brown.ToArgb());
    virtual ~Animal() override {}

    virtual void draw(System::Drawing::Graphics^ g) override;
    virtual void move() override; 
    virtual bool interactable(PopObject* otherObject) const override; 
    
};