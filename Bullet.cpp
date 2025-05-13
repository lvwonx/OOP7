// Bullet.cpp
#define _USE_MATH_DEFINES // Needed for M_PI etc.
#include <cmath>
#include <cstdlib> // For rand

#include "Bullet.h"
#include "Manager.h" // For manager->add/remove
#include "Tree.h"
#include "Animal.h"
#include "Hunter.h"
#include "Explosion.h"
#include "Ball.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Star.h"
// Include MainForm.h to access the static form pointer and its methods
#include "MainForm.h" // Added include


using namespace System::Drawing;
using namespace OOP5_Asorti; // Use the namespace for MainForm

Bullet::Bullet(int frameWidth, int frameHeight, float hunterX, float hunterY, float targetX, float targetY, float hunterWeaponLength, float bulletSpeedModule, int maxRicochets)
// Bullets have a size (e.g., 5) and color. Initial position is calculated.
    : Mover(frameWidth, frameHeight, 0, 0, 5, System::Drawing::Color::OrangeRed.ToArgb()),
    _ricochetsLeft(maxRicochets)
{
    // Calculate direction vector from hunter to target
    float deltaX = targetX - hunterX;
    float deltaY = targetY - hunterY;
    float distanceToTarget = sqrt(deltaX * deltaX + deltaY * deltaY);

    // Calculate bullet start position (at the end of the hunter's weapon)
    if (distanceToTarget == 0) {
        // Avoid division by zero if target is exactly at hunter's position, shoot right as default
        _x = hunterX + hunterWeaponLength;
        _y = hunterY;
        _dX = bulletSpeedModule;
        _dY = 0;
    }
    else {
        // Normalize direction vector and scale by weapon length for start position
        _x = hunterX + (hunterWeaponLength / distanceToTarget) * deltaX;
        _y = hunterY + (hunterWeaponLength / distanceToTarget) * deltaY;
        // Normalize direction vector and scale by bullet speed for velocity
        _dX = (bulletSpeedModule / distanceToTarget) * deltaX;
        _dY = (bulletSpeedModule / distanceToTarget) * deltaY;
    }
    // Set the initial position using the base class method
    setPos(_x, _y);
}

void Bullet::draw(System::Drawing::Graphics^ g) {
    // Use the loaded bitmap
    if (Pictures::BulletBitmap != nullptr) {
        // Center the image at the object's position (_x, _y)
        float drawX = _x - Pictures::BulletBitmap->Width / 2.0f;
        float drawY = _y - Pictures::BulletBitmap->Height / 2.0f;
        // Use float dimensions for DrawImage
        g->DrawImage(Pictures::BulletBitmap, drawX, drawY, static_cast<float>(Pictures::BulletBitmap->Width), static_cast<float>(Pictures::BulletBitmap->Height));
    }
    else {
        // Fallback to drawing a shape (your existing bullet drawing)
        SolidBrush^ brush = gcnew SolidBrush(Color::FromArgb(_color));
        float halfSize = static_cast<float>(_size) / 2.0f;
        float floatSize = static_cast<float>(_size);
        g->FillEllipse(brush, _x - halfSize, _y - halfSize, floatSize, floatSize);
        delete brush;
    }
}

void Bullet::move() {
    if (_paused) return; // Do not move if paused

    // Update position
    _x += _dX;
    _y += _dY;

    bool ricocheted = false;
    float currentFloatSize = static_cast<float>(_size); // Use a consistent float size for boundary checks

    // Check for wall collisions and handle ricochet (Section 7.7)
    // Check X boundaries
    if ((_x - currentFloatSize / 2.0f < 0 && _dX < 0) || (_x + currentFloatSize / 2.0f > _frameWidth && _dX > 0)) {
        _dX = -_dX; // Reverse X direction
        ricocheted = true;
        // Adjust position slightly to prevent sticking to the wall
        if (_x - currentFloatSize / 2.0f < 0) _x = currentFloatSize / 2.0f + 0.01f;
        else if (_x + currentFloatSize / 2.0f > _frameWidth) _x = static_cast<float>(_frameWidth) - currentFloatSize / 2.0f - 0.01f;
    }
    // Check Y boundaries
    if ((_y - currentFloatSize / 2.0f < 0 && _dY < 0) || (_y + currentFloatSize / 2.0f > _frameHeight && _dY > 0)) {
        _dY = -_dY; // Reverse Y direction
        ricocheted = true;
        // Adjust position slightly to prevent sticking to the wall
        if (_y - currentFloatSize / 2.0f < 0) _y = currentFloatSize / 2.0f + 0.01f;
        else if (_y + currentFloatSize / 2.0f > _frameHeight) _y = static_cast<float>(_frameHeight) - currentFloatSize / 2.0f - 0.01f;
    }

    // If ricochet occurred, decrement ricochet count
    if (ricocheted) {
        _ricochetsLeft--;
        Debug::WriteLine("Bullet ricocheted. Ricochets left: " + _ricochetsLeft);
    }

    // If ricochets are depleted, remove the bullet (Section 7.7)
    if (_ricochetsLeft < 0) {
        if (manager != nullptr) {
            manager->remove(this); // Remove the current bullet object
            // Note: 'this' object is deleted after remove, so return immediately
            return;
        }
    }
    // Bullet disappears if it goes far outside bounds without ricocheting (optional, but good practice)
    float screenMargin = static_cast<float>(_size) * 5.0f; // Disappear 5 sizes outside bounds
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
    // Bullet interaction logic (Section 7.4)

    // Bullets should not interact with themselves or explosions in a way that triggers physics collisions or actions
    if (dynamic_cast<Bullet*>(otherObject) != nullptr || dynamic_cast<Explosion*>(otherObject) != nullptr) {
        return; // Ignore interaction with other bullets or explosions
    }

    // Flag to determine if the bullet should be removed after this interaction
    bool removeSelf = true;

    // Ensure manager and form are valid before proceeding with actions that use them
    if (manager == nullptr || MainForm::form == nullptr) {
        // Cannot perform interactions requiring manager/form, just remove the bullet if needed or return
        if (removeSelf && manager != nullptr) manager->remove(this);
        return;
    }


    if (dynamic_cast<Tree*>(otherObject) != nullptr) {
        // Collision with a Tree: Create explosion
        Explosion* ex = new Explosion(_frameWidth, _frameHeight, static_cast<int>(_x), static_cast<int>(_y));
        manager->add(ex);
        Debug::WriteLine("Bullet hit Tree.");
    }
    else if (Animal* animal = dynamic_cast<Animal*>(otherObject)) {
        // Collision with an Animal: Kill animal, create explosion, notify MainForm
        // Create explosion at animal's position before removing it
        Explosion* ex = new Explosion(_frameWidth, _frameHeight, static_cast<int>(animal->getX()), static_cast<int>(animal->getY()));
        manager->add(ex);

        // Remove the animal
        manager->remove(animal);

        // Notify MainForm that an animal was killed (Section 7.8 & 7.9.10)
        MainForm::form->killAnimal(); // Calls killAnimal() on the static form instance
        Debug::WriteLine("Bullet hit Animal. Animal killed.");
    }
    else if (Hunter* hunter = dynamic_cast<Hunter*>(otherObject)) {
        // Collision with the Hunter: Kill hunter, create explosion, notify MainForm
        // Create explosion at hunter's position before removing it
        Explosion* ex = new Explosion(_frameWidth, _frameHeight, static_cast<int>(hunter->getX()), static_cast<int>(hunter->getY()));
        manager->add(ex);

        // Remove the hunter
        manager->remove(hunter);

        // Notify MainForm that the hunter was killed (Section 7.8 & 7.9.10)
        MainForm::form->endGame(0); // Reason 0: Hunter killed (Calls endGame() on the static form instance)
        Debug::WriteLine("Bullet hit Hunter. Hunter killed.");
    }
    else if (dynamic_cast<Ball*>(otherObject) != nullptr ||
        dynamic_cast<Triangle*>(otherObject) != nullptr ||
        dynamic_cast<::Rectangle*>(otherObject) != nullptr ||
        dynamic_cast<Star*>(otherObject) != nullptr) {
        // Collision with a "knišlis" (shape): Remove the shape, create explosion
        // Create explosion at shape's position before removing it
        Explosion* ex = new Explosion(_frameWidth, _frameHeight, static_cast<int>(otherObject->getX()), static_cast<int>(otherObject->getY()));
        manager->add(ex);

        // Remove the shape
        manager->remove(otherObject);
        Debug::WriteLine("Bullet hit shape (knišlis). Shape removed.");
    }
    // else if (dynamic_cast<Bullet*>(otherObject) != nullptr || dynamic_cast<Explosion*>(otherObject) != nullptr) {
    //     // This case is handled by the check at the beginning of the method
    //     removeSelf = false; // Bullet does not remove itself on collision with other bullets or explosions
    // }


    // Remove the bullet itself after interacting, UNLESS it hit something specific that says not to
    if (removeSelf && manager != nullptr) {
        manager->remove(this);
        // Note: 'this' object is deleted after remove, so do not access 'this' further
    }
}

// interactable will use Mover's default, as bullets should interact with most things
// (except other bullets or explosions, which is handled by interact and interactable on Explosion)