#define _USE_MATH_DEFINES
#include <cmath> // M_PI is defined here with _USE_MATH_DEFINES
#include <cstdlib>
#include "Star.h"
#include "Manager.h" // Include Manager

using namespace System::Drawing;

#define MAX_STARS 10 // Define max limit for Stars

Star::Star(int frameWidth, int frameHeight, int x, int y, int points, float innerFactor)
    : Rotator(frameWidth, frameHeight, x, y, 30, System::Drawing::Color::Yellow.ToArgb()),
    numPoints(points >= 3 ? points : 5),
    innerRadiusFactor(innerFactor > 0.1f && innerFactor < 0.9f ? innerFactor : 0.4f)
{
}

void Star::draw(System::Drawing::Graphics^ g) {
    System::Drawing::SolidBrush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(_color));
    int totalVertices = 2 * numPoints;
    array<System::Drawing::Point>^ points = gcnew array<System::Drawing::Point>(totalVertices);
    float outerRadius = static_cast<float>(M_PI); // Should be _size here, not M_PI
    float innerRadius = outerRadius * innerRadiusFactor;
    const float PI_F = static_cast<float>(M_PI);
    float angleStep = PI_F / numPoints;

    // Fix: outerRadius should be _size
    outerRadius = static_cast<float>(_size);
    innerRadius = outerRadius * innerRadiusFactor;


    for (int i = 0; i < totalVertices; ++i) {
        float currentRadius = (i % 2 == 0) ? outerRadius : innerRadius;
        float currentAngle = _alpha + angleStep * i;
        double angle_rad = static_cast<double>(currentAngle);
        float offsetX = currentRadius * static_cast<float>(cos(angle_rad));
        float offsetY = currentRadius * static_cast<float>(sin(angle_rad));
        points[i] = System::Drawing::Point(static_cast<int>(_x + offsetX), static_cast<int>(_y + offsetY));
    }
    g->FillPolygon(brush, points);
    delete brush;
}

void Star::interact(PopObject* otherObject) {
    // Interaction logic based on otherObject type

    if (dynamic_cast<Star*>(otherObject) != nullptr) {
        // Collision with another Star
        // 25% chance to create a new Star

        if ((rand() % 100) < 25) { // 25% chance
            if (manager != nullptr && manager->countStars() < MAX_STARS) {
                int newX = static_cast<int>((_x + otherObject->getX()) / 2.0f);
                int newY = static_cast<int>((_y + otherObject->getY()) / 2.0f);
                // Use defaults for points and innerFactor, or randomize? Sticking to defaults.
                Star* newStar = new Star(_frameWidth, _frameHeight, newX, newY);
                float speed = (static_cast<float>(rand()) / RAND_MAX * 5.0f);
                float angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * static_cast<float>(M_PI);
                newStar->setSpeed(speed * cos(angle), speed * sin(angle));
                manager->add(newStar);
            }
        }

    }
    else {
        // Collision with a different type
        // 25% chance to remove this object (the Star)

        if ((rand() % 100) < 25) { // 25% chance
            if (manager != nullptr) {
                manager->remove(this); // Remove the current Star
            }
        }
    }
}