#define _USE_MATH_DEFINES
#include <cmath> 
#include <cstdlib>
#include "Triangle.h"
#include "Manager.h" 

using namespace System::Drawing;

#define MAX_TRIANGLES 10 

Triangle::Triangle(int frameWidth, int frameHeight, int x, int y)
    : Rotator(frameWidth, frameHeight, x, y, 25, System::Drawing::Color::Cyan.ToArgb())
{
}

void Triangle::draw(System::Drawing::Graphics^ g) {
    System::Drawing::SolidBrush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(_color));
    array<System::Drawing::Point>^ points = gcnew array<System::Drawing::Point>(3);
    const float PI_F = static_cast<float>(M_PI);

    for (int i = 0; i < 3; i++) {
        float currentAngle = _alpha + (2.0f * PI_F / 3.0f) * i;
        double angle_rad = static_cast<double>(currentAngle);
        float offsetX = _size * static_cast<float>(cos(angle_rad));
        float offsetY = _size * static_cast<float>(sin(angle_rad));
        points[i] = System::Drawing::Point(static_cast<int>(_x + offsetX), static_cast<int>(_y + offsetY));
    }
    g->FillPolygon(brush, points);
    delete brush;
}

void Triangle::interact(PopObject* otherObject) {
    

    if (dynamic_cast<Triangle*>(otherObject) != nullptr) {
        
        

        if ((rand() % 100) < 25) { 
            if (manager != nullptr && manager->countTriangles() < MAX_TRIANGLES) {
                int newX = static_cast<int>((_x + otherObject->getX()) / 2.0f);
                int newY = static_cast<int>((_y + otherObject->getY()) / 2.0f);
                Triangle* newTriangle = new Triangle(_frameWidth, _frameHeight, newX, newY);
                float speed = (static_cast<float>(rand()) / RAND_MAX * 5.0f);
                float angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * static_cast<float>(M_PI);
                newTriangle->setSpeed(speed * cos(angle), speed * sin(angle));
                manager->add(newTriangle);
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