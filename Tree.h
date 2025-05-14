#pragma once

#include "Mover.h"

class Ball;
class Triangle;
class Rectangle;
class Star;

class Tree : public Mover {
public:
    Tree(int frameWidth, int frameHeight, int x, int y, int size = 50, int color = System::Drawing::Color::DarkGreen.ToArgb()); 
    virtual ~Tree() override {}

    virtual void draw(System::Drawing::Graphics^ g) override;
    virtual void move() override; 
    virtual bool interactable(PopObject* otherObject) const override; 
    
};