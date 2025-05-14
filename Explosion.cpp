#define _USE_MATH_DEFINES 
#include <cmath>
#include <cstdlib>

#include "Explosion.h"
#include "Manager.h" 
#include "Mover.h"   


using System::Drawing::SolidBrush;
using System::Drawing::Color;
using System::Drawing::Graphics;

Explosion::Explosion(int frameWidth, int frameHeight, int x, int y, int lifeTime)



    : Mover(frameWidth, frameHeight, x, y, 5, Color::OrangeRed.ToArgb()), 
    _lifeTime(lifeTime > 0 ? lifeTime : 30), 
    _initialLifeTime(lifeTime > 0 ? lifeTime : 30)
{
    
    _dX = 0.0f;
    _dY = 0.0f;
    _paused = false; 
}

void Explosion::draw(Graphics^ g) {
    
    float currentPhase = static_cast<float>(_lifeTime) / _initialLifeTime; 
    float progress = 1.0f - currentPhase; 

    
    int currentSize = static_cast<int>(_size + progress * (_size * 3.0f));

    
    int alpha = static_cast<int>(currentPhase * 255); 

    
    Color startColor = System::Drawing::Color::OrangeRed;
    Color endColor = System::Drawing::Color::Yellow; 

    int r = static_cast<int>(startColor.R + progress * (endColor.R - startColor.R));
    int gr = static_cast<int>(startColor.G + progress * (endColor.G - startColor.G));
    int b = static_cast<int>(startColor.B + progress * (endColor.B - startColor.B));


    Color drawColor = Color::FromArgb(alpha, r, gr, b);

    SolidBrush^ brush = gcnew SolidBrush(drawColor);

    float diameter = 2.0f * currentSize;
    
    g->FillEllipse(brush, _x - currentSize, _y - currentSize, diameter, diameter);

    delete brush;
}

void Explosion::move() {
    
    Mover::move();

    if (!_paused) {
        _lifeTime--; 

        if (_lifeTime <= 0) {
            
            
            if (manager != nullptr) {
                manager->remove(this);
            }
            
            
            
        }
    }
}



bool Explosion::interactable(PopObject* otherObject) const {
    
    return false;
}