#pragma once

#include "Rotator.h"
using namespace System::Drawing;

class PopObject;

class Triangle : public Rotator {
public:
    Triangle(int frameWidth, int frameHeight, int x, int y);

    virtual ~Triangle() override {}

    virtual void draw(System::Drawing::Graphics^ g) override;

    virtual void interact(PopObject* otherObject) override;
};