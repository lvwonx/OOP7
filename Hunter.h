#pragma once

#include "Mover.h"
#include "Manager.h" 


class Ball;
class Triangle;
class Rectangle;
class Star;
class Bullet; 


#define CMD_SHOOT 0
#define CMD_START_UP 1
#define CMD_STOP_UP 2
#define CMD_START_RIGHT 3
#define CMD_STOP_RIGHT 4
#define CMD_START_DOWN 5
#define CMD_STOP_DOWN 6
#define CMD_START_LEFT 7
#define CMD_STOP_LEFT 8


class Hunter : public Mover {
private:
    
    bool _movingUp, _movingDown, _movingLeft, _movingRight;
    float _moveSpeed; 

    
    float _aimX, _aimY;

public:
    Hunter(int frameWidth, int frameHeight, int x, int y, int size = 25, int color = System::Drawing::Color::Blue.ToArgb());
    virtual ~Hunter() override {}

    virtual void draw(System::Drawing::Graphics^ g) override; 
    virtual void move() override; 
    virtual bool interactable(PopObject* otherObject) const override; 
    virtual void doCommand(int command) override; 
    
    
    

    void setAimPosition(float x, float y); 
};