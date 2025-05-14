
#define _USE_MATH_DEFINES 
#include <cmath>
#include <cstdlib> 

#include "Bullet.h"
#include "Manager.h" 
#include "Tree.h"
#include "Animal.h"
#include "Hunter.h"
#include "Explosion.h"
#include "Ball.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Star.h"

#include "MainForm.h" 


using namespace System::Drawing;
using namespace OOP5_Asorti; 

Bullet::Bullet(int frameWidth, int frameHeight, float hunterX, float hunterY, float targetX, float targetY, float hunterWeaponLength, float bulletSpeedModule, int maxRicochets)

    : Mover(frameWidth, frameHeight, 0, 0, 5, System::Drawing::Color::OrangeRed.ToArgb()),
    _ricochetsLeft(maxRicochets)
{
    
    float deltaX = targetX - hunterX;
    float deltaY = targetY - hunterY;
    float distanceToTarget = sqrt(deltaX * deltaX + deltaY * deltaY);

    
    if (distanceToTarget == 0) {
        
        _x = hunterX + hunterWeaponLength;
        _y = hunterY;
        _dX = bulletSpeedModule;
        _dY = 0;
    }
    else {
        
        _x = hunterX + (hunterWeaponLength / distanceToTarget) * deltaX;
        _y = hunterY + (hunterWeaponLength / distanceToTarget) * deltaY;
        
        _dX = (bulletSpeedModule / distanceToTarget) * deltaX;
        _dY = (bulletSpeedModule / distanceToTarget) * deltaY;
    }
    
    setPos(_x, _y);
}

void Bullet::draw(System::Drawing::Graphics^ g) {
    
    if (Pictures::BulletBitmap != nullptr) {
        
        float drawX = _x - Pictures::BulletBitmap->Width / 2.0f;
        float drawY = _y - Pictures::BulletBitmap->Height / 2.0f;
        
        g->DrawImage(Pictures::BulletBitmap, drawX, drawY, static_cast<float>(Pictures::BulletBitmap->Width), static_cast<float>(Pictures::BulletBitmap->Height));
    }
    else {
        
        SolidBrush^ brush = gcnew SolidBrush(Color::FromArgb(_color));
        float halfSize = static_cast<float>(_size) / 2.0f;
        float floatSize = static_cast<float>(_size);
        g->FillEllipse(brush, _x - halfSize, _y - halfSize, floatSize, floatSize);
        delete brush;
    }
}

void Bullet::move() {
    if (_paused) return; 

    
    _x += _dX;
    _y += _dY;

    bool ricocheted = false;
    float currentFloatSize = static_cast<float>(_size); 

    
    
    if ((_x - currentFloatSize / 2.0f < 0 && _dX < 0) || (_x + currentFloatSize / 2.0f > _frameWidth && _dX > 0)) {
        _dX = -_dX; 
        ricocheted = true;
        
        if (_x - currentFloatSize / 2.0f < 0) _x = currentFloatSize / 2.0f + 0.01f;
        else if (_x + currentFloatSize / 2.0f > _frameWidth) _x = static_cast<float>(_frameWidth) - currentFloatSize / 2.0f - 0.01f;
    }
    
    if ((_y - currentFloatSize / 2.0f < 0 && _dY < 0) || (_y + currentFloatSize / 2.0f > _frameHeight && _dY > 0)) {
        _dY = -_dY; 
        ricocheted = true;
        
        if (_y - currentFloatSize / 2.0f < 0) _y = currentFloatSize / 2.0f + 0.01f;
        else if (_y + currentFloatSize / 2.0f > _frameHeight) _y = static_cast<float>(_frameHeight) - currentFloatSize / 2.0f - 0.01f;
    }

    
    if (ricocheted) {
        _ricochetsLeft--;
        Debug::WriteLine("Bullet ricocheted. Ricochets left: " + _ricochetsLeft);
    }

    
    if (_ricochetsLeft < 0) {
        if (manager != nullptr) {
            manager->remove(this); 
            
            return;
        }
    }
    
    float screenMargin = static_cast<float>(_size) * 5.0f; 
    if (_x < -screenMargin || _x > _frameWidth + screenMargin ||
        _y < -screenMargin || _y > _frameHeight + screenMargin)
    {
        if (manager != nullptr) {
            manager->remove(this);
            return;
        }
    }
}


void Bullet::interact(PopObject* otherObject) {
    

    
    if (dynamic_cast<Bullet*>(otherObject) != nullptr || dynamic_cast<Explosion*>(otherObject) != nullptr) {
        return; 
    }

    
    bool removeSelf = true;

    
    if (manager == nullptr || MainForm::form == nullptr) {
        
        if (removeSelf && manager != nullptr) manager->remove(this);
        return;
    }


    if (dynamic_cast<Tree*>(otherObject) != nullptr) {
        
        Explosion* ex = new Explosion(_frameWidth, _frameHeight, static_cast<int>(_x), static_cast<int>(_y));
        manager->add(ex);
        Debug::WriteLine("Bullet hit Tree.");
    }
    else if (Animal* animal = dynamic_cast<Animal*>(otherObject)) {
        
        
        Explosion* ex = new Explosion(_frameWidth, _frameHeight, static_cast<int>(animal->getX()), static_cast<int>(animal->getY()));
        manager->add(ex);

        
        manager->remove(animal);

        
        MainForm::form->killAnimal(); 
        Debug::WriteLine("Bullet hit Animal. Animal killed.");
    }
    else if (Hunter* hunter = dynamic_cast<Hunter*>(otherObject)) {
        
        
        Explosion* ex = new Explosion(_frameWidth, _frameHeight, static_cast<int>(hunter->getX()), static_cast<int>(hunter->getY()));
        manager->add(ex);

        
        manager->remove(hunter);

        
        MainForm::form->endGame(0); 
        Debug::WriteLine("Bullet hit Hunter. Hunter killed.");
    }
    else if (dynamic_cast<Ball*>(otherObject) != nullptr ||
        dynamic_cast<Triangle*>(otherObject) != nullptr ||
        dynamic_cast<::Rectangle*>(otherObject) != nullptr ||
        dynamic_cast<Star*>(otherObject) != nullptr) {
        
        
        Explosion* ex = new Explosion(_frameWidth, _frameHeight, static_cast<int>(otherObject->getX()), static_cast<int>(otherObject->getY()));
        manager->add(ex);

        
        manager->remove(otherObject);
        Debug::WriteLine("Bullet hit shape (knišlis). Shape removed.");
    }
    
    
    
    


    
    if (removeSelf && manager != nullptr) {
        manager->remove(this);
        
    }
}


