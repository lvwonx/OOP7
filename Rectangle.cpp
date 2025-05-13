#define _USE_MATH_DEFINES
#include <cmath> // M_PI is defined here with _USE_MATH_DEFINES
#include <cstdlib>
#include "Rectangle.h"
#include "Manager.h" // Include Manager

using namespace System::Drawing;

#define MIN_RECT_SIZE 10
#define MAX_RECT_SIZE 40
#define MAX_RECTANGLES 10 // Define max limit for Rectangles

::Rectangle::Rectangle(int frameWidth, int frameHeight, int x, int y)
    : Rotator(frameWidth, frameHeight, x, y, 20, System::Drawing::Color::Magenta.ToArgb())
{
}

void ::Rectangle::draw(System::Drawing::Graphics^ g) {
    System::Drawing::SolidBrush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(_color));
    array<System::Drawing::Point>^ points = gcnew array<System::Drawing::Point>(4);
    const float PI_F = static_cast<float>(M_PI);

    float angles[4] = {
        _alpha + PI_F / 4.0f,
        _alpha + 3.0f * PI_F / 4.0f,
        _alpha + 5.0f * PI_F / 4.0f,
        _alpha + 7.0f * PI_F / 4.0f
    };

    for (int i = 0; i < 4; i++) {
        double angle_rad = static_cast<double>(angles[i]);
        float offsetX = _size * static_cast<float>(cos(angle_rad));
        float offsetY = _size * static_cast<float>(sin(angle_rad));
        points[i] = System::Drawing::Point(static_cast<int>(_x + offsetX), static_cast<int>(_y + offsetY));
    }

    g->FillPolygon(brush, points);
    delete brush;
}

void ::Rectangle::interact(PopObject* otherObject) {
    // Interaction logic based on otherObject type

    if (dynamic_cast<::Rectangle*>(otherObject) != nullptr) {
        // Collision with another Rectangle
        // 25% chance to create a new Rectangle

        if ((rand() % 100) < 25) { // 25% chance
            if (manager != nullptr && manager->countRectangles() < MAX_RECTANGLES) {
                int newX = static_cast<int>((_x + otherObject->getX()) / 2.0f);
                int newY = static_cast<int>((_y + otherObject->getY()) / 2.0f);
                ::Rectangle* newRectangle = new ::Rectangle(_frameWidth, _frameHeight, newX, newY);
                float speed = (static_cast<float>(rand()) / RAND_MAX * 5.0f);
                float angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * static_cast<float>(M_PI);
                newRectangle->setSpeed(speed * cos(angle), speed * sin(angle));
                manager->add(newRectangle);
            }
        }

    }
    else {
        // Collision with a different type
        // 25% chance to remove this object (the Rectangle)

        if ((rand() % 100) < 25) { // 25% chance
            if (manager != nullptr) {
                manager->remove(this); // Remove the current Rectangle
            }
        }
    }
}