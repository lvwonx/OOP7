#pragma once

#include "Mover.h"
using namespace System::Drawing;

class PopObject;

class Explosion : public Mover {
private:
    int _lifeTime; // Frames remaining for the explosion
    int _initialLifeTime; // For calculating animation progress

public:
    // Constructor takes position and frame dimensions, and duration
    Explosion(int frameWidth, int frameHeight, int x, int y, int lifeTime = 30); // lifeTime in frames

    virtual ~Explosion() override {}

    virtual void draw(System::Drawing::Graphics^ g) override;

    virtual void move() override; // Handle animation state and self-removal

    // Explosions don't initiate interaction or respond to it in a way that triggers physics
    virtual void interact(PopObject* otherObject) override { /* Explosions don't interact */ }

    // Define interactability: Explosions should not collide with shapes
    virtual bool interactable(PopObject* otherObject) const override;
};