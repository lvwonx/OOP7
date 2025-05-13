#pragma once

#include "Rotator.h"
using namespace System::Drawing;

class PopObject;

class Rectangle : public Rotator {
public:
    Rectangle(int frameWidth, int frameHeight, int x, int y);

    virtual ~Rectangle() override {}

    virtual void draw(System::Drawing::Graphics^ g) override;

    virtual void interact(PopObject* otherObject) override;
};