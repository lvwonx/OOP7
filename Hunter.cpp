// Hunter.cpp
#define _USE_MATH_DEFINES // Needed for M_PI if used in draw/move logic
#include <cmath> // For sqrt, atan2, cos, sin
#include <cstdlib> // For rand

#include "Hunter.h"
#include "Bullet.h"
#include "Manager.h"
#include "Pictures.h"
#include "Ball.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Star.h"
// Include MainForm.h to access the static form pointer and its methods
#include "MainForm.h" // Added include

using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace OOP5_Asorti; // Use the namespace for MainForm


Hunter::Hunter(int frameWidth, int frameHeight, int x, int y, int size, int color)
// Initialize Mover part and hunter-specific members
    : Mover(frameWidth, frameHeight, x, y, size, color),
    _movingUp(false), _movingDown(false), _movingLeft(false), _movingRight(false),
    _moveSpeed(2.5f), // Base speed for hunter movement
    _aimX(static_cast<float>(x) + static_cast<float>(size)), // Initial aim direction (e.g., right)
    _aimY(static_cast<float>(y)) {
    // Hunter's speed is controlled by movement flags, not initial random value from Mover
    _dX = 0;
    _dY = 0;
}

void Hunter::setAimPosition(float x, float y) {
    // Update the position the hunter is aiming at (usually mouse cursor)
    _aimX = x;
    _aimY = y;
}

void Hunter::draw(System::Drawing::Graphics^ g) {
    // Assuming Pictures::HunterBitmap is loaded and valid
    if (Pictures::HunterBitmap != nullptr) { // Check if the bitmap loaded correctly
        // You might want to rotate the image based on aim direction.
        // Simple drawing at position (centered):
        float drawX = _x - Pictures::HunterBitmap->Width / 2.0f;
        float drawY = _y - Pictures::HunterBitmap->Height / 2.0f;
        // Use float dimensions for DrawImage
        g->DrawImage(Pictures::HunterBitmap, drawX, drawY, static_cast<float>(Pictures::HunterBitmap->Width), static_cast<float>(Pictures::HunterBitmap->Height));
    }
    else {
        // Fallback to drawing a shape if the image didn't load (your existing shape drawing)
        SolidBrush^ bodyBrush = gcnew SolidBrush(Color::FromArgb(_color));
        float floatSize = static_cast<float>(_size);
        g->FillEllipse(bodyBrush, _x - floatSize / 2.0f, _y - floatSize / 2.0f, floatSize, floatSize);
        delete bodyBrush;
    }

    // Draw Hunter's weapon (can still be a line, or also an image)
    float weaponLength = static_cast<float>(_size) * 1.5f; // Make weapon longer than size
    float angle = atan2(_aimY - _y, _aimX - _x); // Angle towards the aim position
    float weaponEndX = _x + weaponLength * cos(angle);
    float weaponEndY = _y + weaponLength * sin(angle);
    Pen^ weaponPen = gcnew Pen(Color::DarkSlateGray, 3); // Weapon color and thickness
    g->DrawLine(weaponPen, _x, _y, weaponEndX, weaponEndY);
    delete weaponPen;
}

void Hunter::move() {
    // В начале Hunter::move
    Debug::WriteLine("Hunter::move called. _movingUp=" + _movingUp + ", _movingDown=" + _movingDown +
        ", _movingLeft=" + _movingLeft + ", _movingRight=" + _movingRight +
        ", calculated dX=" + _dX + ", dY=" + _dY);

    // Calculate desired speed based on movement flags
    float targetDx = 0;
    float targetDy = 0;

    if (_movingUp) targetDy = -_moveSpeed;
    if (_movingDown) targetDy = _moveSpeed;
    if (_movingLeft) targetDx = -_moveSpeed;
    if (_movingRight) targetDx = _moveSpeed;

    // Normalize diagonal movement speed
    if (targetDx != 0 && targetDy != 0) {
        float factor = _moveSpeed / sqrt(targetDx * targetDx + targetDy * targetDy);
        targetDx *= factor;
        targetDy *= factor;
    }

    // Set the actual speed
    _dX = targetDx;
    _dY = targetDy;

    // Call base Mover's move to update position and check wall collision
    Mover::move();
}

bool Hunter::interactable(PopObject* otherObject) const {
    // Hunter does not interact with "knishli" (Ball, Triangle, Rectangle, Star)
    if (dynamic_cast<Ball*>(otherObject) != nullptr ||
        dynamic_cast<Triangle*>(otherObject) != nullptr ||
        dynamic_cast<::Rectangle*>(otherObject) != nullptr ||
        dynamic_cast<Star*>(otherObject) != nullptr) {
        return false;
    }
    // Let Mover handle interaction with other types (Bullet, Animal, Tree - though Animal/Tree return false)
    // Hunter *can* be hit by a Bullet, so Mover's default (checking for Mover type) is appropriate unless specified otherwise.
    return Mover::interactable(otherObject);
}

void Hunter::doCommand(int command) {
    // Handle commands specific to the Hunter (Section 7.5 & 7.9.9)
    switch (command) {
    case CMD_SHOOT: {
        // Before shooting, check if bullets are available via MainForm's method (Section 7.8 & 7.9.10)
        if (manager != nullptr && MainForm::form != nullptr) { // Check manager and form validity
            // MainForm::form is the static handle to the main window instance
            if (MainForm::form->takeBullet()) { // takeBullet returns true if successful, false if no bullets
                float weaponLength = static_cast<float>(_size) * 1.5f; // Bullet starts from weapon end
                float bulletSpeed = 10.0f; // Adjust bullet speed as needed

                // Create the Bullet object
                Bullet* bullet = new Bullet(_frameWidth, _frameHeight, _x, _y, _aimX, _aimY, weaponLength, bulletSpeed);
                // Add the bullet to the manager's collection
                manager->add(bullet);
                Debug::WriteLine("Hunter shot a bullet.");
            }
            // If takeBullet() returned false, endGame(1) was already called by MainForm, so no need to handle it here again.
        }
        break;
    }
                  // Movement commands (Section 7.5 & 7.9.9)
    case CMD_START_UP: _movingUp = true; break;
    case CMD_STOP_UP:   _movingUp = false; break;
    case CMD_START_DOWN:    _movingDown = true; break;
    case CMD_STOP_DOWN: _movingDown = false; break;
    case CMD_START_LEFT:    _movingLeft = true; break;
    case CMD_STOP_LEFT: _movingLeft = false; break;
    case CMD_START_RIGHT: _movingRight = true; break;
    case CMD_STOP_RIGHT:    _movingRight = false; break;
    default:
        // Pass unhandled commands to the base class (e.g., pause/resume commands)
        Mover::doCommand(command);
        break;
    }
}