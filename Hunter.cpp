
#define _USE_MATH_DEFINES 
#include <cmath> 
#include <cstdlib> 

#include "Hunter.h"
#include "Bullet.h"
#include "Manager.h"
#include "Pictures.h"
#include "Ball.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Star.h"

#include "MainForm.h" 

using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace OOP5_Asorti; 


Hunter::Hunter(int frameWidth, int frameHeight, int x, int y, int size, int color)

    : Mover(frameWidth, frameHeight, x, y, size, color),
    _movingUp(false), _movingDown(false), _movingLeft(false), _movingRight(false),
    _moveSpeed(2.5f), 
    _aimX(static_cast<float>(x) + static_cast<float>(size)), 
    _aimY(static_cast<float>(y)) {
    
    _dX = 0;
    _dY = 0;
}

void Hunter::setAimPosition(float x, float y) {
    
    _aimX = x;
    _aimY = y;
}

void Hunter::draw(System::Drawing::Graphics^ g) {
    
    if (Pictures::HunterBitmap != nullptr) { 
        
        
        float drawX = _x - Pictures::HunterBitmap->Width / 2.0f;
        float drawY = _y - Pictures::HunterBitmap->Height / 2.0f;
        
        g->DrawImage(Pictures::HunterBitmap, drawX, drawY, static_cast<float>(Pictures::HunterBitmap->Width), static_cast<float>(Pictures::HunterBitmap->Height));
    }
    else {
        
        SolidBrush^ bodyBrush = gcnew SolidBrush(Color::FromArgb(_color));
        float floatSize = static_cast<float>(_size);
        g->FillEllipse(bodyBrush, _x - floatSize / 2.0f, _y - floatSize / 2.0f, floatSize, floatSize);
        delete bodyBrush;
    }

    
    float weaponLength = static_cast<float>(_size) * 1.5f; 
    float angle = atan2(_aimY - _y, _aimX - _x); 
    float weaponEndX = _x + weaponLength * cos(angle);
    float weaponEndY = _y + weaponLength * sin(angle);
    Pen^ weaponPen = gcnew Pen(Color::DarkSlateGray, 3); 
    g->DrawLine(weaponPen, _x, _y, weaponEndX, weaponEndY);
    delete weaponPen;
}

void Hunter::move() {
    
    Debug::WriteLine("Hunter::move called. _movingUp=" + _movingUp + ", _movingDown=" + _movingDown +
        ", _movingLeft=" + _movingLeft + ", _movingRight=" + _movingRight +
        ", calculated dX=" + _dX + ", dY=" + _dY);

    
    float targetDx = 0;
    float targetDy = 0;

    if (_movingUp) targetDy = -_moveSpeed;
    if (_movingDown) targetDy = _moveSpeed;
    if (_movingLeft) targetDx = -_moveSpeed;
    if (_movingRight) targetDx = _moveSpeed;

    
    if (targetDx != 0 && targetDy != 0) {
        float factor = _moveSpeed / sqrt(targetDx * targetDx + targetDy * targetDy);
        targetDx *= factor;
        targetDy *= factor;
    }

    
    _dX = targetDx;
    _dY = targetDy;

    
    Mover::move();
}

bool Hunter::interactable(PopObject* otherObject) const {
    
    if (dynamic_cast<Ball*>(otherObject) != nullptr ||
        dynamic_cast<Triangle*>(otherObject) != nullptr ||
        dynamic_cast<::Rectangle*>(otherObject) != nullptr ||
        dynamic_cast<Star*>(otherObject) != nullptr) {
        return false;
    }
    
    
    return Mover::interactable(otherObject);
}

void Hunter::doCommand(int command) {
    
    switch (command) {
    case CMD_SHOOT: {
        
        if (manager != nullptr && MainForm::form != nullptr) { 
            
            if (MainForm::form->takeBullet()) { 
                float weaponLength = static_cast<float>(_size) * 1.5f; 
                float bulletSpeed = 10.0f; 

                
                Bullet* bullet = new Bullet(_frameWidth, _frameHeight, _x, _y, _aimX, _aimY, weaponLength, bulletSpeed);
                
                manager->add(bullet);
                Debug::WriteLine("Hunter shot a bullet.");
            }
            
        }
        break;
    }
                  
    case CMD_START_UP: _movingUp = true; break;
    case CMD_STOP_UP:   _movingUp = false; break;
    case CMD_START_DOWN:    _movingDown = true; break;
    case CMD_STOP_DOWN: _movingDown = false; break;
    case CMD_START_LEFT:    _movingLeft = true; break;
    case CMD_STOP_LEFT: _movingLeft = false; break;
    case CMD_START_RIGHT: _movingRight = true; break;
    case CMD_STOP_RIGHT:    _movingRight = false; break;
    default:
        
        Mover::doCommand(command);
        break;
    }
}