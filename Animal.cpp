// Animal.cpp
#include "Animal.h"
// ... other includes ...
#include "Pictures.h" // Include Pictures.h
#include <cmath> // For fabs

using namespace System::Drawing;

Animal::Animal(int frameWidth, int frameHeight, int x, int y, int size, int color)
    : Mover(frameWidth, frameHeight, x, y, size, color) {
    // Initialize speed with some randomness
    _dX = static_cast<float>(rand() % 7 - 3) / 2.0f; // Speed between -1.5 and 3.0
    _dY = static_cast<float>(rand() % 7 - 3) / 2.0f;
    // Ensure a minimum speed to avoid being stuck
    if (fabs(_dX) < 0.1f && fabs(_dY) < 0.1f) {
        if (fabs(_dX) < 0.1f) _dX = (rand() % 2 == 0) ? 0.5f : -0.5f;
        if (fabs(_dY) < 0.1f) _dY = (rand() % 2 == 0) ? 0.5f : -0.5f;
    }
}

void Animal::draw(System::Drawing::Graphics^ g) {
    // Use the loaded bitmap
    if (Pictures::AnimalBitmap != nullptr) {
        // Center the image at the object's position (_x, _y)
        float drawX = _x - Pictures::AnimalBitmap->Width / 2.0f;
        float drawY = _y - Pictures::AnimalBitmap->Height / 2.0f;
        // Use float dimensions for DrawImage
        g->DrawImage(Pictures::AnimalBitmap, drawX, drawY, static_cast<float>(Pictures::AnimalBitmap->Width), static_cast<float>(Pictures::AnimalBitmap->Height));
    }
    else {
        // Fallback to drawing a shape
        SolidBrush^ brush = gcnew SolidBrush(Color::FromArgb(_color));
        float halfSize = static_cast<float>(_size) / 2.0f;
        float floatSize = static_cast<float>(_size);
        g->FillEllipse(brush, _x - halfSize, _y - halfSize, floatSize, floatSize);
        delete brush;
    }
}

void Animal::move() {
    if (!_paused) {
        // Randomly change direction occasionally
        if (rand() % 100 < 5) { // 5% chance each tick
            _dX = static_cast<float>(rand() % 7 - 3) / 2.0f;
            _dY = static_cast<float>(rand() % 7 - 3) / 2.0f;
            // Ensure a minimum speed
            if (fabs(_dX) < 0.1f && fabs(_dY) < 0.1f) {
                if (fabs(_dX) < 0.1f) _dX = (rand() % 2 == 0) ? 0.5f : -0.5f;
                if (fabs(_dY) < 0.1f) _dY = (rand() % 2 == 0) ? 0.5f : -0.5f;
            }
        }
    }
    // Call base Mover's move to update position and check wall collision
    Mover::move();
}

#include "Ball.h" // Ensure Ball is included  
#include "Triangle.h" // Ensure Triangle is included  
#include "Rectangle.h" // Ensure Rectangle is included  
#include "Star.h" // Ensure Star is included  

bool Animal::interactable(PopObject* otherObject) const {  
   // Animals do not interact with "knishli" (Ball, Triangle, Rectangle, Star)  
   if (dynamic_cast<Ball*>(otherObject) != nullptr ||  
       dynamic_cast<Triangle*>(otherObject) != nullptr ||  
       dynamic_cast<::Rectangle*>(otherObject) != nullptr ||  
       dynamic_cast<Star*>(otherObject) != nullptr) {  
       return false;  
   }  
   // Let Mover handle interaction with other types (Hunter, Bullet, Tree - though Tree returns false too)  
   return Mover::interactable(otherObject);  
}