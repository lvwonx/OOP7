#pragma once

#include "Mover.h"
using namespace System::Drawing;

class PopObject;

class Ball : public Mover {
public:
    Ball(int frameWidth, int frameHeight, int x, int y);

    virtual ~Ball() override {}

    virtual void draw(System::Drawing::Graphics^ g) override;

    virtual void interact(PopObject* otherObject) override;

    virtual void move() override;
};