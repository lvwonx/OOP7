
#include "Tree.h"
#include "Ball.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Star.h"
#include "Pictures.h"
#include "Hunter.h"
#include "Animal.h"

using namespace System::Drawing;

Tree::Tree(int frameWidth, int frameHeight, int x, int y, int size, int color)

    : Mover(frameWidth, frameHeight, x, y, size, color) {
    
    _dX = 0;
    _dY = 0;
    _paused = true; 
}

void Tree::draw(System::Drawing::Graphics^ g) {
    
    if (Pictures::TreeBitmap != nullptr) {
        
        float drawX = _x - Pictures::TreeBitmap->Width / 2.0f;
        float drawY = _y - Pictures::TreeBitmap->Height / 2.0f;
        
        g->DrawImage(Pictures::TreeBitmap, drawX, drawY, static_cast<float>(Pictures::TreeBitmap->Width), static_cast<float>(Pictures::TreeBitmap->Height));
    }
    else {
        
        
        SolidBrush^ trunkBrush = gcnew SolidBrush(Color::SaddleBrown);
        float trunkWidth = static_cast<float>(_size) / 3.0f;
        float trunkHeight = static_cast<float>(_size) / 2.0f;
        g->FillRectangle(trunkBrush, _x - trunkWidth / 2, _y, trunkWidth, trunkHeight);
        delete trunkBrush;

        
        SolidBrush^ crownBrush = gcnew SolidBrush(Color::FromArgb(_color)); 
        float crownRadius = static_cast<float>(_size) / 2.0f;
        g->FillEllipse(crownBrush, _x - crownRadius, _y - crownRadius * 1.5f, crownRadius * 2, crownRadius * 2);
        delete crownBrush;
    }
}

void Tree::move() {
    
    
}

bool Tree::interactable(PopObject* otherObject) const {
    
    
    if (dynamic_cast<Ball*>(otherObject) != nullptr ||
        dynamic_cast<Triangle*>(otherObject) != nullptr ||
        dynamic_cast<::Rectangle*>(otherObject) != nullptr ||
        dynamic_cast<Star*>(otherObject) != nullptr ||
        dynamic_cast<Animal*>(otherObject) != nullptr ||
        dynamic_cast<Hunter*>(otherObject) != nullptr) {
        return false;
    }
    
    
    
    
    
    return Mover::interactable(otherObject);
}