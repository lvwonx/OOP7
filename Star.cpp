#define _USE_MATH_DEFINES
#include <cmath> 
#include <cstdlib>
#include "Star.h"
#include "Manager.h" 

using namespace System::Drawing;

#define MAX_STARS 10 

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
    float outerRadius = static_cast<float>(M_PI); 
    float innerRadius = outerRadius * innerRadiusFactor;
    const float PI_F = static_cast<float>(M_PI);
    float angleStep = PI_F / numPoints;

    
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
    

    if (dynamic_cast<Star*>(otherObject) != nullptr) {
        
        

        if ((rand() % 100) < 25) { 
            if (manager != nullptr && manager->countStars() < MAX_STARS) {
                int newX = static_cast<int>((_x + otherObject->getX()) / 2.0f);
                int newY = static_cast<int>((_y + otherObject->getY()) / 2.0f);
                
                Star* newStar = new Star(_frameWidth, _frameHeight, newX, newY);
                float speed = (static_cast<float>(rand()) / RAND_MAX * 5.0f);
                float angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * static_cast<float>(M_PI);
                newStar->setSpeed(speed * cos(angle), speed * sin(angle));
                manager->add(newStar);
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