#pragma once

#include "Mover.h"
#include "Manager.h" 


class Tree;
class Animal;
class Hunter;
class Explosion;






class Bullet : public Mover {
private:
    int _ricochetsLeft; 

public:
    Bullet(int frameWidth, int frameHeight, float startX, float startY, float targetX, float targetY, float hunterWeaponLength, float bulletSpeedModule, int maxRicochets = 2); 
    virtual ~Bullet() override {}

    virtual void draw(System::Drawing::Graphics^ g) override;
    virtual void move() override; 
    virtual void interact(PopObject* otherObject) override; 
    
};