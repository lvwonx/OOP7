#define _USE_MATH_DEFINES
#include <cmath> // M_PI is defined here with _USE_MATH_DEFINES
#include <cstdlib>
#include "Triangle.h"
#include "Manager.h" // Include Manager for global pointer and add/remove/count

using namespace System::Drawing;

#define MAX_TRIANGLES 10 // Define max limit for Triangles

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
    // Interaction logic based on otherObject type

    if (dynamic_cast<Triangle*>(otherObject) != nullptr) {
        // Collision with another Triangle
        // 25% chance to create a new Triangle

        if ((rand() % 100) < 25) { // 25% chance
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
        // Collision with a different type
        // 25% chance to remove this object (the Triangle)

        if ((rand() % 100) < 25) { // 25% chance
            if (manager != nullptr) {
                manager->remove(this); // Remove the current Triangle
            }
        }
    }
}