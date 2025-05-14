#define _USE_MATH_DEFINES
#include <cmath> 
#include <cstdlib>
#include "Ball.h"
#include "Manager.h" 

using System::Drawing::SolidBrush;
using System::Drawing::Color;
using System::Drawing::Graphics;

#define MAX_BALLS 10 

Ball::Ball(int frameWidth, int frameHeight, int x, int y)
    : Mover(frameWidth, frameHeight, x, y, 15, Color::Orange.ToArgb())
{
}

void Ball::draw(Graphics^ g) {
    SolidBrush^ brush = gcnew SolidBrush(Color::FromArgb(_color));
    float diameter = 2.0f * _size;
    g->FillEllipse(brush, _x - _size, _y - _size, diameter, diameter);
    delete brush;
}

void Ball::interact(PopObject* otherObject) {
    
    

    if (dynamic_cast<Ball*>(otherObject) != nullptr) {
        
        

        if ((rand() % 100) < 25) { 
            if (manager != nullptr && manager->countBalls() < MAX_BALLS) {
                
                int newX = static_cast<int>((_x + otherObject->getX()) / 2.0f);
                int newY = static_cast<int>((_y + otherObject->getY()) / 2.0f);
                Ball* newBall = new Ball(_frameWidth, _frameHeight, newX, newY);
                
                float speed = (static_cast<float>(rand()) / RAND_MAX * 5.0f); 
                float angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * static_cast<float>(M_PI); 
                newBall->setSpeed(speed * cos(angle), speed * sin(angle));
                manager->add(newBall);
            }
        }

    }
    else {
        
        

        if ((rand() % 100) < 25) { 
            if (manager != nullptr) {
                manager->remove(this); 
                
                
            }
        }
    }
}


void Ball::move() {
    Mover::move();

    if (!_paused) {
        
        float brakeFactor = 0.995f;
        _dX *= brakeFactor;
        _dY *= brakeFactor;

        
        float stopThreshold = 0.05f;
        if (fabs(_dX) < stopThreshold && fabs(_dY) < stopThreshold) {
            _dX = 0.0f;
            _dY = 0.0f;
        }
    }
}