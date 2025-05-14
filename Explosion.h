#pragma once

#include "Mover.h"
using namespace System::Drawing;

class PopObject;

class Explosion : public Mover {
private:
    int _lifeTime; 
    int _initialLifeTime; 

public:
    
    Explosion(int frameWidth, int frameHeight, int x, int y, int lifeTime = 30); 

    virtual ~Explosion() override {}

    virtual void draw(System::Drawing::Graphics^ g) override;

    virtual void move() override; 

    
    virtual void interact(PopObject* otherObject) override { /* Explosions don't interact */ }

    
    virtual bool interactable(PopObject* otherObject) const override;
};