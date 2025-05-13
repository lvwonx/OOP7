// Tree.cpp
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
// Initialize Mover part with provided parameters. Trees are static, so speed is 0.
    : Mover(frameWidth, frameHeight, x, y, size, color) {
    // Trees are stationary
    _dX = 0;
    _dY = 0;
    _paused = true; // Explicitly pause movement calculation in Mover::move()
}

void Tree::draw(System::Drawing::Graphics^ g) {
    // Use the loaded bitmap
    if (Pictures::TreeBitmap != nullptr) {
        // Center the image at the object's position (_x, _y)
        float drawX = _x - Pictures::TreeBitmap->Width / 2.0f;
        float drawY = _y - Pictures::TreeBitmap->Height / 2.0f;
        // Use float dimensions for DrawImage
        g->DrawImage(Pictures::TreeBitmap, drawX, drawY, static_cast<float>(Pictures::TreeBitmap->Width), static_cast<float>(Pictures::TreeBitmap->Height));
    }
    else {
        // Fallback to drawing a shape (your existing tree drawing)
        // Trunk
        SolidBrush^ trunkBrush = gcnew SolidBrush(Color::SaddleBrown);
        float trunkWidth = static_cast<float>(_size) / 3.0f;
        float trunkHeight = static_cast<float>(_size) / 2.0f;
        g->FillRectangle(trunkBrush, _x - trunkWidth / 2, _y, trunkWidth, trunkHeight);
        delete trunkBrush;

        // Crown
        SolidBrush^ crownBrush = gcnew SolidBrush(Color::FromArgb(_color)); // Use assigned color for crown
        float crownRadius = static_cast<float>(_size) / 2.0f;
        g->FillEllipse(crownBrush, _x - crownRadius, _y - crownRadius * 1.5f, crownRadius * 2, crownRadius * 2);
        delete crownBrush;
    }
}

void Tree::move() {
    // Trees do not move, this overrides Mover::move() to do nothing or rely on _paused
    // Mover's constructor sets speed to 0, and _paused = true prevents movement.
}

bool Tree::interactable(PopObject* otherObject) const {
    // Trees do not interact with "knishli" (Ball, Triangle, Rectangle, Star) according to PDF (Section 7.9.7 implies this via 7.9.5 interaction rules)
    // Also, Tree doesn't interact with Animal or Hunter by their interactable rules.
    if (dynamic_cast<Ball*>(otherObject) != nullptr ||
        dynamic_cast<Triangle*>(otherObject) != nullptr ||
        dynamic_cast<::Rectangle*>(otherObject) != nullptr ||
        dynamic_cast<Star*>(otherObject) != nullptr ||
        dynamic_cast<Animal*>(otherObject) != nullptr ||
        dynamic_cast<Hunter*>(otherObject) != nullptr) {
        return false;
    }
    // Trees *can* be hit by bullets, and bullets interact with them.
    // The bullet's interact method handles the collision consequence.
    // Mover::interactable checks for Mover type, which Bullet inherits from.
    // Returning true here allows the collision detection in Manager::move() to find the collision,
    // and then Bullet::interact handles the result (creating explosion).
    return Mover::interactable(otherObject);
}