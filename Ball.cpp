#define _USE_MATH_DEFINES
#include <cmath> // M_PI is defined here with _USE_MATH_DEFINES
#include <cstdlib>
#include "Ball.h"
#include "Manager.h" // Include Manager for global pointer and add/remove/count

using System::Drawing::SolidBrush;
using System::Drawing::Color;
using System::Drawing::Graphics;

#define MAX_BALLS 10 // Define max limit for Balls

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
    // Interaction logic based on otherObject type
    // Use dynamic_cast to determine the real type

    if (dynamic_cast<Ball*>(otherObject) != nullptr) {
        // Collision with another Ball
        // 25% chance to create a new Ball

        if ((rand() % 100) < 25) { // 25% chance
            if (manager != nullptr && manager->countBalls() < MAX_BALLS) {
                // Create a new Ball near the collision point
                int newX = static_cast<int>((_x + otherObject->getX()) / 2.0f);
                int newY = static_cast<int>((_y + otherObject->getY()) / 2.0f);
                Ball* newBall = new Ball(_frameWidth, _frameHeight, newX, newY);
                // Add some random initial speed to the new ball
                float speed = (static_cast<float>(rand()) / RAND_MAX * 5.0f); // Random speed up to 5.0
                float angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * static_cast<float>(M_PI); // Random direction
                newBall->setSpeed(speed * cos(angle), speed * sin(angle));
                manager->add(newBall);
            }
        }

    }
    else {
        // Collision with a different type of object (Rectangle, Triangle, Star)
        // 25% chance to remove this object (the Ball)

        if ((rand() % 100) < 25) { // 25% chance
            if (manager != nullptr) {
                manager->remove(this); // Remove the current Ball
                // Note: After removal, 'this' object is invalid.
                // The Manager's move loop handles this by checking for nullptr.
            }
        }
    }
}


void Ball::move() {
    Mover::move();

    if (!_paused) {
        // Add some friction/braking effect
        float brakeFactor = 0.995f;
        _dX *= brakeFactor;
        _dY *= brakeFactor;

        // Stop if speed is very low
        float stopThreshold = 0.05f;
        if (fabs(_dX) < stopThreshold && fabs(_dY) < stopThreshold) {
            _dX = 0.0f;
            _dY = 0.0f;
        }
    }
}