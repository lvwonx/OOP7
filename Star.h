#pragma once

#include "Rotator.h"
using namespace System::Drawing;

class PopObject;

class Star : public Rotator {
private:
    int numPoints;
    float innerRadiusFactor;
public:
    Star(int frameWidth, int frameHeight, int x, int y, int points = 5, float innerFactor = 0.4f);

    virtual ~Star() override {};

    virtual void draw(System::Drawing::Graphics^ g) override;

    virtual void interact(PopObject* otherObject) override;
};