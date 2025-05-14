
#include "Animal.h"

#include "Pictures.h" 
#include <cmath> 

using namespace System::Drawing;

Animal::Animal(int frameWidth, int frameHeight, int x, int y, int size, int color)
    : Mover(frameWidth, frameHeight, x, y, size, color) {
    
    _dX = static_cast<float>(rand() % 7 - 3) / 2.0f; 
    _dY = static_cast<float>(rand() % 7 - 3) / 2.0f;
    
    if (fabs(_dX) < 0.1f && fabs(_dY) < 0.1f) {
        if (fabs(_dX) < 0.1f) _dX = (rand() % 2 == 0) ? 0.5f : -0.5f;
        if (fabs(_dY) < 0.1f) _dY = (rand() % 2 == 0) ? 0.5f : -0.5f;
    }
}

void Animal::draw(System::Drawing::Graphics^ g) {
    
    if (Pictures::AnimalBitmap != nullptr) {
        
        float drawX = _x - Pictures::AnimalBitmap->Width / 2.0f;
        float drawY = _y - Pictures::AnimalBitmap->Height / 2.0f;
        
        g->DrawImage(Pictures::AnimalBitmap, drawX, drawY, static_cast<float>(Pictures::AnimalBitmap->Width), static_cast<float>(Pictures::AnimalBitmap->Height));
    }
    else {
        
        SolidBrush^ brush = gcnew SolidBrush(Color::FromArgb(_color));
        float halfSize = static_cast<float>(_size) / 2.0f;
        float floatSize = static_cast<float>(_size);
        g->FillEllipse(brush, _x - halfSize, _y - halfSize, floatSize, floatSize);
        delete brush;
    }
}

void Animal::move() {
    if (!_paused) {
        
        if (rand() % 100 < 5) { 
            _dX = static_cast<float>(rand() % 7 - 3) / 2.0f;
            _dY = static_cast<float>(rand() % 7 - 3) / 2.0f;
            
            if (fabs(_dX) < 0.1f && fabs(_dY) < 0.1f) {
                if (fabs(_dX) < 0.1f) _dX = (rand() % 2 == 0) ? 0.5f : -0.5f;
                if (fabs(_dY) < 0.1f) _dY = (rand() % 2 == 0) ? 0.5f : -0.5f;
            }
        }
    }
    
    Mover::move();
}

#include "Ball.h" 
#include "Triangle.h" 
#include "Rectangle.h" 
#include "Star.h" 

bool Animal::interactable(PopObject* otherObject) const {  
   
   if (dynamic_cast<Ball*>(otherObject) != nullptr ||  
       dynamic_cast<Triangle*>(otherObject) != nullptr ||  
       dynamic_cast<::Rectangle*>(otherObject) != nullptr ||  
       dynamic_cast<Star*>(otherObject) != nullptr) {  
       return false;  
   }  
   
   return Mover::interactable(otherObject);  
}