#pragma once

#include "Mover.h"

class Rotator : public Mover {
protected:
    float _alpha;
    float _dAlpha;
public:
    Rotator(int frameWidth, int frameHeight, int x, int y, int size = 20, int color = System::Drawing::Color::Green.ToArgb());

    virtual ~Rotator() override {}

    virtual void move() override;

    float getAngle() { return _alpha; }

    void reverseRotationDirection() { _dAlpha = -_dAlpha; }
protected:
};